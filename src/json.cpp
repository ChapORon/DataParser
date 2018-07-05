#include "json.hpp"

const std::string dp::json::str(const dp::dt::node &node, unsigned int indentFactor, unsigned int depth)
{
    if (node == dt::node::null)
        return "(null)\n";
    std::string tabs;
    std::string indent;
    for (unsigned int i = 0; i != indentFactor; ++i)
        indent += ' ';
    for (size_t n = 0; n != depth; ++n)
        tabs += indent;
    std::string value = node.value().getString();
    std::string content = tabs;
    content += '"' + node.name();
    if (!value.empty())
        content += "\":\"" + value;
    content += "\"\n";
    auto tags = node.childs();
    if (!tags.empty())
        content += tabs +"{\n";
    unsigned int n = 0;
    for (const auto &tag : tags)
    {
        content += str(tag, depth + 1);
        if (n < (tags.size() - 1))
        {
            content = content.substr(0, content.length() - 1);
            content += ",\n";
        }
        ++n;
    }
    if (!tags.empty())
        content += tabs +"}\n";
    return content;
}

void dp::json::write(const dp::dt::node &node, std::ostream &os, unsigned int indentFactor)
{
    os << str(node, indentFactor);
}