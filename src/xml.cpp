#include "xml.hpp"

const std::string dp::xml::str(const dp::dt::node &node, unsigned int indentFactor, unsigned int depth)
{
    if (node == dt::node::null)
        return "(null)\n";
    std::string name = node.name();
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    std::string tabs;
    std::string indent;
    for (unsigned int i = 0; i != indentFactor; ++i)
        indent += ' ';
    for (size_t n = 0; n != depth; ++n)
        tabs += indent;
    std::string content;
    unsigned int minSize = 0;
    dt::node elements = node.get("__xmldeclarations__");
    if (depth == 0 && elements != dt::node::null)
    {
        for (const auto &element : elements)
        {
            content += "<?" + element.name();
            for (const auto &info : element)
                content += " " + info.name() + "=\"" + info.value().getString() + "\"";
            content += "?>\n";
        }
        ++minSize;
    }
    content += tabs + "<" + name;
    dt::node attributes = node.get("__xmlattributes__");
    if (attributes != dt::node::null)
    {
        for (const auto &attribute : attributes)
            content += " " + attribute.name() + "=\"" + attribute.value().getString() + "\"";
        ++minSize;
    }
    if (!node.value() && node.childs().size() == minSize)
        content += " />\n";
    else
    {
        content += ">\n";
        if (node.value())
        {
            content += tabs;
            content += indent;
            content += node.value().getString();
            content += '\n';
        }
        auto tags = node.childs();
        for (const auto &tag : tags)
        {
            if (tag.name().find("__") != 0)
                content += str(tag, indentFactor, depth + 1);
        }
        content += tabs;
        content += "</";
        content += name;
        content += ">\n";
    }
    return content;
}

void dp::xml::write(const dp::dt::node &node, std::ostream &os, unsigned int indentFactor)
{
    os << str(node, indentFactor);
}

dp::dt::node dp::xml::create(const std::string &name, const std::string &version, const std::string &encoding)
{
    dt::node node(name);
    node.add("__xmldeclarations__.xml.version", dt::data(version));
    node.add("__xmldeclarations__.xml.encoding", dt::data(encoding));
    return node;
}

void dp::xml::addAttribute(dp::dt::node &node, const std::string &key, const dp::dt::data &value)
{
    if (key.find('.') != std::string::npos)
        return;
    std::string attributeKey = "__xmlattributes__.";
    attributeKey += key;
    node.add(attributeKey, value);
}

void dp::xml::addDeclaration(dp::dt::node &node, const std::string &key, const std::string &attribute, const std::string &value)
{
    if (key.find('.') != std::string::npos || attribute.find('.') != std::string::npos)
        return;
    std::string attributeKey = "__xmldeclarations__.";
    attributeKey += key + '.' + attribute;
    node.add(attributeKey, dt::data(value));
}

dp::dt::node dp::xml::loadFromFile(const std::string &path)
{
    std::ifstream fileStream(path.c_str());
    auto node = loadFromStream(fileStream);
    if (!node.get("__xmldeclarations__").find("xml"))
        return dt::node::null;
    return node;
}

std::string dp::xml::treatCommentary(std::string &content)
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

dp::dt::node dp::xml::loadFromStream(std::istream &stream)
{
    std::string content, line;
    while (std::getline(stream, line))
    {
        trim(line);
        if (!line.empty())
        {
            content += line;
            content += '\n';
        }
    }
    return loadFromContent(content);
}

void dp::xml::treatAutoCloseMarkup(std::string &content)
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

bool dp::xml::treatXmlDeclarations(dt::node &node, const std::string &attributes)
{
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
    std::string currentName;
    for (const auto &it : attributesList)
    {
        if (it.find('=') == std::string::npos)
        {
            if (!currentName.empty())
                return false;
            currentName = it;
        }
        else
        {
            std::vector<std::string> currentAttribute = split(it, "=");
            if (currentAttribute.size() > 2)
                return false;
            for (auto &attribute : currentAttribute)
            {
                if (start_with(attribute, "\""))
                    attribute = attribute.substr(1, attribute.size());
                if (end_with(attribute, "\""))
                    attribute = attribute.substr(0, (attribute.size() - 1));
            }
            addDeclaration(node, currentName, currentAttribute[0], currentAttribute[1]);
        }
    }
    return true;
}

void dp::xml::treatXmlInformation(dt::node &, const std::string &info)
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

bool dp::xml::treatDeclarations(dt::node &node, std::string &content)
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
            if (!treatXmlDeclarations(node, info))
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
            treatXmlInformation(node, info);
        }
        else
            loop = false;
        if (start_with(content, "\n"))
            content = content.substr(1, content.size());
    }
    return true;
}

void dp::xml::treatMarkupContent(dt::node &node, const std::string &content)
{
    std::string value;
    std::vector<std::string> contentToAdd = split(content, "\n");
    for (const auto &it : contentToAdd)
    {
        std::string trimmed = it;
        trim(trimmed);
        if (!trimmed.empty())
            value += trimmed;
    }
    if (!content.empty())
        node.value(dt::data(value));
}

bool dp::xml::setAttributes(dt::node &node, const std::string &attributes)
{
    std::vector<std::string> attributesList;
    std::string tmp = attributes;
    trim(tmp);
    std::vector<std::string> tmpList = split(tmp, " ");
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
    std::string currentName;
    for (const auto &it : attributesList)
    {
        if (it.find('=') == std::string::npos)
        {
            if (!currentName.empty())
                return false;
            currentName = it;
        }
        else
        {
            std::vector<std::string> currentAttribute = split(it, "=");
            if (currentAttribute.size() > 2)
                return false;
            for (auto &attr : currentAttribute)
            {
                if (start_with(attr, "\""))
                    attr = attr.substr(1, attr.size());
                if (end_with(attr, "\""))
                    attr = attr.substr(0, (attr.size() - 1));
            }
            addAttribute(node, currentAttribute[0], dt::data(currentAttribute[1]));
        }
    }
    return true;
}

bool dp::xml::treatContent(dt::node &node, std::string &content)
{
    if (start_with(content, "\n"))
        content = content.substr(1, content.size());
    size_t pos = 0;
    while ((pos = content.find('<')) != 0)
    {
        if (pos == std::string::npos)
        {
            treatMarkupContent(node, content);
            content = "";
            return true;
        }
        else
        {
            treatMarkupContent(node, content.substr(0, pos));
            content = content.substr(pos, content.size());
        }
    }
    if (start_with(content, "\n"))
        content = content.substr(1, content.size());
    while (content.size() > 2 && !start_with(content, "</"))
    {
        if (start_with(content, "<?"))
            return false;
        pos = content.find('>');
        std::string attributes = content.substr(1, pos - 1);
        trim(attributes);
        std::string name = split(attributes, " ")[0];
        content = content.substr((pos + 1), content.size());
        dt::node child(name);
        setAttributes(child, attributes);
        if (!treatContent(child, content))
            return false;
        node.add(child);
        if (start_with(content, "\n"))
            content = content.substr(1, content.size());
    }
    if (start_with(content, "</"))
    {
        pos = content.find('>');
        std::string closeTag = content.substr(2, pos - 2);
        trim(closeTag);
        if (node.name() != closeTag)
            return false;
        content = content.substr(pos + 1, content.size());
    }
    return true;
}

std::string dp::xml::extractName(std::string &content)
{
    std::string tmp = content;
    if (start_with(tmp, "\n"))
        tmp = tmp.substr(1, tmp.size());
    if (tmp.find('<') != 0)
        return "";
    size_t pos = content.find('>');
    std::string attributes = content.substr(1, pos - 1);
    trim(attributes);
    std::string name = split(attributes, " ")[0];
    content = content.substr((pos + 1), content.size());
    return name;
}

dp::dt::node dp::xml::loadFromContent(const std::string &xmlContent)
{
    std::string content = xmlContent;
    content = treatCommentary(content);
    if (content.empty())
        return dt::node::null;
    if (start_with(content, "\n"))
        content = content.substr(1, content.size());
    treatAutoCloseMarkup(content);
    dp::dt::node node;
    if (!treatDeclarations(node, content))
        return dt::node::null;
    size_t openingTag = count(content, "<") - count(content, "<?");
    size_t enclosingTag = count(content, "</");
    if (openingTag != (enclosingTag * 2))
        return dt::node::null;
    node.name(extractName(content));
    if (!treatContent(node, content))
        return dt::node::null;
    if (start_with(content, "</"))
    {
        std::string closeTag = content.substr(2, content.find('>') - 2);
        trim(closeTag);
        if (node.name() != closeTag)
            return dt::node::null;
    }
    return node;
}
