#include "XML/File.hpp"

dp::XML::File::File() : InnerMarkup("xml"){}

dp::XML::File::File(const std::string &path) : InnerMarkup("xml")
{
    created = false;
    std::string content = load(path);
    if (content.empty())
        return;
    if (start_with(content, "\n"))
        content = content.substr(1, content.size());
    if (!start_with(content, "<?"))
        return;
    treatAutoCloseMarkup(content);
    treatInfo(content);
    if (xmlAttributes.find("xml") == xmlAttributes.end())
        return;
    size_t openingTag = count(content, "<") - count(content, "<?");
    size_t enclosingTag = count(content, "</");
    if (openingTag != (enclosingTag * 2) ||
        !treatContent(content) ||
        tags.size() > 1)
        return;
    created = true;
}

dp::XML::File &dp::XML::File::operator=(const dp::XML::File &other)
{
    this->attributes = other.attributes;
    this->tags = other.tags;
    return *this;
}

std::string dp::XML::File::treatCommentary(std::string &content) const
{
    size_t pos = 0, next_pos = 0;
    while ((pos = content.find("<!--", pos)) != std::string::npos)
    {
        if (content.find("--->", pos) != std::string::npos)
            return "";
        else if ((next_pos = content.find("-->", pos)) != std::string::npos)
            content = content.substr(0, pos) + content.substr((next_pos + 3), content.size());
        else
            return "";
    }
    replace_all(content, "\n\n", "\n");
    return content;
}

const std::string dp::XML::File::load(const std::string &path) const
{
    std::ifstream file(path.c_str());
    if (!file)
        return path;
    std::string content, line;
    while (std::getline(file, line))
    {
        trim(line);
        if (!line.empty())
        {
            content += line;
            content += '\n';
        }
    }
    content = treatCommentary(content);
    return content;
}

void dp::XML::File::treatXmlInformation(const std::string &info, std::string &)
{
    std::string treat = info;
    replace_all(treat, "]", "");
    replace_all(treat, ">", "");
    replace_all(treat, "\n", "");
    std::vector<std::string> tags, tmp1, tmp2 = split(treat, "[");
    for (const auto &str : tmp2)
    {
        tmp1 = split(str, "<!");
        for (const auto &str2 : tmp1)
        {
            if (!str2.empty())
                tags.emplace_back(str2);
        }
    }
}

bool dp::XML::File::treatXmlAttributes(const std::string &attributes)
{
    std::vector<int> toErase;
    std::vector<std::string> attributesList;
    std::vector<std::string> tmpList = split(attributes, " ");
    for (size_t n = 0; n < tmpList.size(); ++n)
    {
        if (tmpList[n].find('\"') == std::string::npos || end_with(tmpList[n], "\""))
            attributesList.emplace_back(tmpList[n]);
        else
        {
            std::string toPush = tmpList[n];
            ++n;
            while (n < tmpList.size() && !end_with(tmpList[n], "\""))
            {
                toPush += " " + tmpList[n];
                ++n;
            }
            toPush += " " + tmpList[n];
            attributesList.emplace_back(toPush);
        }
    }
    unsigned int i = 0;
    std::string currentName;
    for (const auto &it : attributesList)
    {
        if (it.find('=') == std::string::npos)
        {
            if (!currentName.empty())
                return false;
            currentName = it;
            toErase.emplace_back(i);
            if (xmlAttributes.find(currentName) != xmlAttributes.end())
                xmlAttributes.emplace(currentName, std::unordered_map<std::string, dt::data>());
        }
        else
        {
            std::vector<std::string> currentAttribute = split(it, "=");
            if (currentAttribute.size() > 2)
                return false;
            for (auto &attribute : currentAttribute)
            {
                if (start_with(it, "\""))
                    attribute = it.substr(1, it.size());
                if (end_with(it, "\""))
                    attribute = it.substr(0, (it.size() - 1));
            }
            xmlAttributes[currentName].emplace(currentAttribute[0], currentAttribute[1]);
        }
        ++i;
    }
    for (const auto &pos : toErase)
        attributesList.erase(attributesList.begin() + pos);
    return true;
}

void dp::XML::File::addAttributes(const std::string &name, const std::string &attribute, const std::string &value)
{
    if (xmlAttributes.find(name) != xmlAttributes.end())
        xmlAttributes.emplace(name, std::unordered_map<std::string, dt::data>());
    xmlAttributes[name].emplace(attribute, value);
}

void dp::XML::File::addDefaultHeader()
{
    addAttributes("xml", "version", "1.0");
    addAttributes("xml", "encoding", "UTF-8");
}

void dp::XML::File::addDocAttributes(const std::string &name, const std::string &attribute, const std::string &value)
{
    if (documentAttributes.find(name) != documentAttributes.end())
        documentAttributes.emplace(name, std::unordered_map<std::string, dt::data>());
    documentAttributes[name].emplace(attribute, value);
}

void dp::XML::File::removeDocAttributes()
{
    documentAttributes.clear();
}

void dp::XML::File::removeDocAttributes(const std::string &name)
{
    documentAttributes.erase(name);
}

void dp::XML::File::clear()
{
    InnerMarkup::clear();
    removeDocAttributes();
}

bool dp::XML::File::treatInfo(std::string &content)
{
    bool loop = true;
    size_t pos = 0, next_pos = 0;
    std::string info;
    while (loop)
    {
        if (start_with(content, "\n"))
            content = content.substr(1, content.size());
        if (start_with(content, "<?"))
        {
            if ((next_pos = content.find("?>", pos)) != std::string::npos)
            {
                info = content.substr(2, (next_pos - 2));
                content = content.substr((next_pos + 2), content.size());
            }
            else
                return false;
            trim(info);
            if (!treatXmlAttributes(info))
                return false;
        }
        else if (start_with(content, "<!"))
        {
            size_t tmpPos = 0;
            bool loop2 = true;
            next_pos = pos;
            while (loop2)
            {
                if ((next_pos = content.find('>', next_pos + 1)) == std::string::npos)
                    return false;
                if ((tmpPos = content.find("<!", tmpPos + 2)) == std::string::npos ||
                    tmpPos > next_pos)
                    loop2 = false;
            }
            info = content.substr(2, (next_pos - 1));
            content = content.substr((next_pos + 1), content.size());
            trim(info);
            treatXmlInformation(info, content);
        }
        else
            loop = false;
        if (start_with(content, "\n"))
            content = content.substr(1, content.size());
    }
    return true;
}

void dp::XML::File::treatAutoCloseMarkup(std::string &content)
{
    std::string autoClose, replace;
    size_t beg_pos = 0, end_pos = 0;
    while ((end_pos = content.find("/>", 0)) != std::string::npos)
    {
        if ((beg_pos = content.find_last_of('<', end_pos)) != std::string::npos)
            autoClose = content.substr(beg_pos + 1, (end_pos - (beg_pos + 1)));
        else
            autoClose = content.substr(0, end_pos);
        std::vector<std::string> vec = split(autoClose, " ");
        replace = '<';
        replace += autoClose;
        replace += "></";
        replace += vec[0];
        replace += '>';
        autoClose = "<" + autoClose + "/>";
        replace_all(content, autoClose, replace);
    }
}

bool dp::XML::File::treatContent(std::string &content)
{
    if (start_with(content, "\n"))
        content = content.substr(1, content.size());
    size_t pos = 0;
    while (content.size() > 2 && !start_with(content, "</"))
    {
        pos = content.find('>');
        std::string attributes = content.substr(1, pos - 1);
        trim(attributes);
        std::string name = split(attributes, " ")[0];
        content = content.substr((pos + 1), content.size());
        tags.emplace_back(Markup(name, attributes, content));
        if (!treatInfo(content))
            return false;
    }
    return true;
}

const std::string dp::XML::File::toString() const
{
    if (tags.size() > 1)
        return "";
    if (xmlAttributes.find("xml") == xmlAttributes.end())
        return "";
    std::string content;
    for (const auto &attribute : xmlAttributes)
    {
        content += "<?" + attribute.first;
        for (const auto &pair : attribute.second)
            content += " " + pair.first + "=\"" + pair.second.getString() + "\"";
        content += "?>\n";
    }
    for (const auto &attribute : documentAttributes)
    {
        content += "<!" + attribute.first;
        for (const auto &pair : attribute.second)
            content += " " + pair.first + "=\"" + pair.second.getString() + "\"";
        content += ">\n";
    }
    for (const auto &tag : tags)
        content += tag.toString(0);
    content = content.substr(0, content.size() - 1);
    return content;
}

std::ostream &operator<<(std::ostream &os, const dp::XML::File &file)
{
    os << file.toString();
    return os;
}