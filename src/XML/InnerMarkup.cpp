#include "XML/Markup.hpp"

dp::XML::Markup::InnerMarkup::InnerMarkup(const std::string &name) : created(false)
{
    setName(name);
    created = true;
}

dp::XML::Markup::InnerMarkup::InnerMarkup(const std::string &name, std::string &content) : created(false)
{
    setName(name);
    if (!treatContent(content))
        return;
    created = true;
}

dp::XML::Markup::InnerMarkup::InnerMarkup(const std::string &name, const std::string &attributes, std::string &content) : created(false)
{
    setName(name);
    if (!setAttributes(attributes) ||
        !treatContent(content))
        return;
    created = true;
}

dp::XML::Markup::iterator dp::XML::Markup::InnerMarkup::begin()
{
    return &tags[0];
}

dp::XML::Markup::const_iterator dp::XML::Markup::InnerMarkup::begin() const
{
    return &tags[0];
}

dp::XML::Markup::iterator dp::XML::Markup::InnerMarkup::end()
{
    return &tags[tags.size()];
}

dp::XML::Markup::const_iterator dp::XML::Markup::InnerMarkup::end() const
{
    return &tags[tags.size()];
}

size_t dp::XML::Markup::InnerMarkup::size() const
{
    return tags.size();
}

dp::XML::Markup::InnerMarkup &dp::XML::Markup::InnerMarkup::operator=(const dp::XML::Markup::InnerMarkup &other)
{
    this->attributes = other.attributes;
    this->tags = other.tags;
    this->contents = other.contents;
    return *this;
}

const std::string &dp::XML::Markup::InnerMarkup::getName() const
{
    return name;
}

void dp::XML::Markup::InnerMarkup::setName(const std::string &name)
{
    this->name = name;
    std::transform(this->name.begin(), this->name.end(), this->name.begin(), ::tolower);
}

const std::vector<std::string> dp::XML::Markup::InnerMarkup::getAttributes() const
{
    std::vector<std::string> keys;
    for (const auto &pair : attributes)
        keys.emplace_back(pair.first);
    return keys;
}

const dp::dt::data dp::XML::Markup::InnerMarkup::getAttribute(const std::string &name) const
{
    if (attributes.find(name) == attributes.end())
        return dt::data();
    return attributes.at(name);
}

const std::vector<std::string> &dp::XML::Markup::InnerMarkup::getContents() const
{
    return contents;
}

void dp::XML::Markup::InnerMarkup::addAttributes(const std::string &name, const dt::data &attribute)
{
    attributes[name] = attribute;
}

void dp::XML::Markup::InnerMarkup::addContents(const std::string &content)
{
    contents.emplace_back(content);
}

void dp::XML::Markup::InnerMarkup::setContents(const std::vector<std::string> &contents)
{
    this->contents = contents;
}

void dp::XML::Markup::InnerMarkup::addMarkups(const dp::XML::Markup &tag)
{
    tags.emplace_back(tag);
}

void dp::XML::Markup::InnerMarkup::clear()
{
    removeAttributes();
    removeContents();
    removeMarkups();
}

void dp::XML::Markup::InnerMarkup::removeAttributes()
{
    attributes.clear();
}

void dp::XML::Markup::InnerMarkup::removeContents()
{
    contents.clear();
}

void dp::XML::Markup::InnerMarkup::removeMarkups()
{
    tags.clear();
}

void dp::XML::Markup::InnerMarkup::removeAttributes(const std::string &name)
{
    attributes.erase(name);
}

void dp::XML::Markup::InnerMarkup::removeContents(const std::string &content)
{
    auto it = std::find(contents.begin(), contents.end(), content);
    if (it == contents.end())
        return ;
    contents.erase(it);
}

void dp::XML::Markup::InnerMarkup::removeMarkups(const std::string &name)
{
    size_t pos = 0;
    std::vector<size_t> toErase;
    for (auto &tag : tags)
    {
        if (tag.getName() == name)
            toErase.emplace_back(pos);
        ++pos;
    }
    for (const auto &it : toErase)
        tags.erase(tags.begin() + it);
}

const dp::XML::Markup &dp::XML::Markup::InnerMarkup::operator[](size_t pos) const
{
    return tags[pos];
}

const std::vector<dp::XML::Markup> &dp::XML::Markup::InnerMarkup::getMarkups() const
{
    return tags;
}

const std::vector<dp::XML::Markup> dp::XML::Markup::InnerMarkup::operator[](const std::string &name) const
{
    std::vector<Markup> list;
    for (auto &tag : tags)
    {
        if (tag.getName() == name)
            list.emplace_back(tag);
    }
    return list;
}

const std::string dp::XML::Markup::InnerMarkup::toString(size_t nbTab) const
{
    std::string tabs;
    for (size_t n = 0; n != nbTab; ++n)
        tabs += "  ";
    std::string content = tabs + "<" + name;
    for (const auto &pair : attributes)
        content += " " + pair.first + "=\"" + pair.second.getString() + "\"";
    if (tags.empty() && contents.empty())
        content += " />\n";
    else
    {
        content += ">\n";
        for (const auto &text : contents)
        {
            content += tabs;
            content += "  ";
            content += text;
            content += '\n';
        }
        for (const auto &tag : tags)
            content += tag.toString(nbTab + 1);
        content += tabs;
        content += "</";
        content += name;
        content += ">\n";
    }
    return content;
}

bool dp::XML::Markup::InnerMarkup::setAttributes(const std::string &attributes)
{
    std::vector<unsigned int> toErase;
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
    unsigned int i = 0;
    for (const auto &it : attributesList)
    {
        if (it.find('=') == std::string::npos)
        {
            if (!currentName.empty())
                return false;
            currentName = it;
            toErase.emplace_back(i);
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
            this->attributes.emplace(currentAttribute[0], dt::data(currentAttribute[1]));
        }
        ++i;
    }
    for (const auto &pos : toErase)
        attributesList.erase(attributesList.begin() + pos);
    return true;
}

void dp::XML::Markup::InnerMarkup::treatMarkupContent(const std::string &content)
{
    std::vector<std::string> contentToAdd = split(content, "\n");
    for (const auto &it : contentToAdd)
    {
        std::string trimmed = it;
        trim(trimmed);
        if (!trimmed.empty())
            contents.emplace_back(trimmed);
    }
}

bool dp::XML::Markup::InnerMarkup::treatContent(std::string &content)
{
    if (start_with(content, "\n"))
        content = content.substr(1, content.size());
    size_t pos = 0;
    while ((pos = content.find('<')) != 0)
    {
        if (pos == std::string::npos)
        {
            treatMarkupContent(content);
            content = "";
            return true;
        }
        else
        {
            treatMarkupContent(content.substr(0, pos));
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
        addMarkups(Markup(name, attributes, content));
        if (start_with(content, "\n"))
            content = content.substr(1, content.size());
    }
    if (start_with(content, "</"))
    {
        pos = content.find('>');
        std::string closeTag = content.substr(2, pos - 2);
        trim(closeTag);
        std::transform(closeTag.begin(), closeTag.end(), closeTag.begin(), ::tolower);
        if (name != closeTag)
            return false;
        content = content.substr(pos + 1, content.size());
    }
    return true;
}

bool dp::XML::Markup::InnerMarkup::start_with(const std::string &str, const std::string &regex) const
{
    return (str.find(regex) == 0);
}

bool dp::XML::Markup::InnerMarkup::end_with(const std::string &str, const std::string &regex) const
{
    return (str.find(regex, (str.size() - regex.size())) == (str.size() - regex.size()));
}

void dp::XML::Markup::InnerMarkup::replace_all(std::string &str, const std::string &search, const std::string &replace) const
{
    size_t pos;
    while ((pos = str.find(search, 0)) != std::string::npos)
        str.replace(pos, search.length(), replace);
}

void dp::XML::Markup::InnerMarkup::trim(std::string &str) const
{
    replace_all(str, "\t", " ");
    replace_all(str, "  ", " ");
    if (str.find_first_of(' ') == 0)
        str = str.substr(1);
    if (str.find_last_of(' ') == str.length() - 1)
        str = str.substr(0, str.length() - 1);
}

size_t dp::XML::Markup::InnerMarkup::count(std::string &str, const std::string &regex) const
{
    size_t pos = 0, count = 0;
    while ((pos = str.find(regex, pos)) != std::string::npos)
    {
        ++count;
        pos += regex.length();
    }
    return count;
}

std::vector<std::string> dp::XML::Markup::InnerMarkup::split(const std::string &str, const std::string &regex) const
{
    std::vector<std::string> vec;
    size_t prev_pos = 0, pos = 0;
    while((pos = str.find(regex, pos)) != std::string::npos)
    {
        std::string substr(str.substr(prev_pos, pos - prev_pos));
        vec.emplace_back(substr);
        pos += regex.size();
        prev_pos = pos;
    }
    vec.emplace_back(str.substr(prev_pos, pos - prev_pos));
    return vec;
}

bool dp::XML::Markup::InnerMarkup::operator==(const std::string &name) const
{
    std::string tmp = name;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    return (tmp == this->name);
}

bool dp::XML::Markup::InnerMarkup::operator!=(const std::string &name) const
{
    std::string tmp = name;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    return (tmp != this->name);
}