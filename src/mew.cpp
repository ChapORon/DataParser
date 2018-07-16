#include "mew.hpp"

std::string dp::mew::getValue(const dp::dt::data &data)
{
    std::string value = data.getString();
    if (value == "true")
        return "t";
    else if (value == "false")
        return "f";
    else if(std::regex_match(value, std::regex("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$")))
        return value;
    return '"' + value + '"';
}

const std::string dp::mew::str(const dp::dt::node &node, unsigned int depth)
{
    if (node == dt::node::null)
        return "(null)\n";
    std::string tabs;
    for (size_t n = 0; n != depth; ++n)
        tabs += '\t';
    std::string value = node.value().getString();
    std::string content = tabs;
    if (value.empty())
        content += node.name();
    else
        content += '"' + node.name() + "\":" + getValue(value);
    content += '\n';
    auto tags = node.childs();
    for (const auto &tag : tags)
        content += str(tag, depth + 1);
    return content;
}

void dp::mew::write(const dp::dt::node &node, std::ostream &os)
{
    os << str(node);
}