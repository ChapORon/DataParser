#include "mew.hpp"

const std::string dp::mew::str(const dp::dt::node &node, unsigned int depth)
{
    if (node == dt::node::null)
        return "(null)\n";
    std::string tabs;
    for (size_t n = 0; n != depth; ++n)
        tabs += '\t';
    std::string value = node.value().getString();
    std::string content = tabs;
    content += '"' + node.name();
    if (!value.empty())
        content += '"' + node.name() + "\":\"" + value;
    content += "\"\n";
    auto tags = node.childs();
    for (const auto &tag : tags)
        content += str(tag, depth + 1);
    return content;
}

void dp::mew::write(const dp::dt::node &node, std::ostream &os)
{
    os << str(node);
}