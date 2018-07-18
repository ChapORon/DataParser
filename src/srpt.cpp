#include "srpt.hpp"

std::string dp::srpt::getValue(const dp::dt::data &data)
{
    std::string value = data.getString();
    if (value == "true")
        return "tr";
    else if (value == "false")
        return "fa";
    else if(std::regex_match(value, std::regex("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$")) ||
            value.length() == 1)
        return value;
    return '"' + value + '"';
}

const std::string dp::srpt::str(const dp::dt::node &node, unsigned int indentFactor, unsigned int depth)
{
    if (node == dt::node::null)
        return "(null)\n";
    std::string tabs;
    if (depth > 0)
    {
        if (depth > 1)
            tabs = std::to_string(depth);
        if (indentFactor == 0)
            tabs += '\t';
        else
            tabs += std::string(indentFactor, ' ');
    }
    std::string value = node.value().getString();
    std::string content = tabs;
    if (value.empty())
        content += node.name();
    else
        content += '"' + node.name() + "\":" + getValue(value);
    content += '\n';
    auto tags = node.childs();
    for (const auto &tag : tags)
        content += str(tag, indentFactor, depth + 1);
    return content;
}

void dp::srpt::write(const dp::dt::node &node, std::ostream &os, unsigned int indentFactor)
{
    os << str(node, indentFactor);
}

dp::dt::node dp::srpt::loadFromFile(const std::string &path)
{
    std::ifstream fileStream(path.c_str());
    return loadFromStream(fileStream);
}

dp::dt::node dp::srpt::loadFromStream(std::istream &stream)
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

dp::dt::node dp::srpt::loadFromContent(const std::string &srptContent)
{
    std::string content = srptContent;
    if (content.empty())
        return dt::node::null;
    dp::dt::node node;
    return node;
}