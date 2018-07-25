#include "xml.hpp"

dp::parser::xml dp::xml::parser;

const std::string dp::xml::str(const dp::dt::node &node, unsigned int indentFactor, unsigned int depth)
{
    return parser.str(node, indentFactor, depth);
}

void dp::xml::write(const dp::dt::node &node, std::ostream &os, unsigned int indentFactor)
{
    parser.write(node, os, indentFactor);
}

void dp::xml::write(const dp::dt::node &node, const std::string &filename, unsigned int indentFactor)
{
    parser.write(node, filename, indentFactor);
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
    dp::dt::node node = parser.loadFromFile(path);
    if (node != dp::dt::node::null && node.get("__xmldeclarations__.xml") == dp::dt::node::null)
        return dp::dt::node::null;
    return node;
}

dp::dt::node dp::xml::loadFromStream(std::istream &stream)
{
    return parser.loadFromStream(stream);
}

dp::dt::node dp::xml::loadFromContent(const std::string &xmlContent)
{
    return parser.loadFromContent(xmlContent);
}
