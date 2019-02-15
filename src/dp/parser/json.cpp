#include "dp/parser/json.hpp"

std::string dp::parser::json::getValue(const std::string &value)
{
    if (value == "true" ||
        value == "false" ||
        std::regex_match(value, std::regex("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$")))
        return value;
    return '"' + value + '"';
}

const std::string dp::parser::json::str(const dp::dt::node &node, unsigned int indentFactor, unsigned int depth)
{
    if (node == dt::node::null)
        return "(null)\n";
    std::string tabs;
    std::string indent(indentFactor, ' ');
    for (size_t n = 0; n != (depth + 1); ++n)
        tabs += indent;
    std::string value = node.get<const std::string &>();
    std::string content;
    if (depth == 0)
        content = "{\n";
    content += tabs;
    if (!node.name().empty())
        content += '"' + node.name() + "\": ";
    if (!value.empty())
        content += getValue(node.get<const std::string &>());
    auto tags = node.childs();
    bool array = false;
    if (!tags.empty())
    {
        if (tags[0].name().empty())
        {
            content += '[';
            array = true;
        }
        else
            content += '{';
    }
    content += "\n";
    unsigned int n = 0;
    for (const auto &tag : tags)
    {
        if ((array && !tag.name().empty()) || (!array && tag.name().empty()))
            return "";
        content += str(tag, indentFactor, depth + 1);
        if (n < (tags.size() - 1))
        {
            content = content.substr(0, content.length() - 1);
            content += ",\n";
        }
        ++n;
    }
    if (!tags.empty())
    {
        content += tabs;
        if (array)
            content += ']';
        else
            content += '}';
        content += '\n';
    }
    if (depth == 0)
        content += "}\n";
    return content;
}

dp::dt::node dp::parser::json::loadFromContent(const std::string &jsonContent)
{
    std::string content = jsonContent;
    if (content.empty())
        return dt::node::null;
    dp::dt::node node;
    return node;
}