#include "Dp/Xml.hpp"

#include "Dp/StringUtils.hpp"

Dp::Parser::Xml Dp::Xml::parser;

namespace Dp
{
    const std::string Xml::Str(const Dt::Node &node, unsigned int indentFactor, unsigned int depth, bool breakLine)
    {
        return parser.Str(node, indentFactor, depth, breakLine);
    }

    void Xml::Write(const Dt::Node &node, std::ostream &os, unsigned int indentFactor)
    {
        parser.Write(node, os, indentFactor);
    }

    void Xml::Write(const Dt::Node &node, const std::string &filename, unsigned int indentFactor)
    {
        parser.Write(node, filename, indentFactor);
    }

    Dt::Node Xml::Create(const std::string &name, const std::string &version, const std::string &encoding)
    {
        Dt::Node node(name);
        node.Add("__xmldeclarations__.xml.version", Dt::Data(version));
        node.Add("__xmldeclarations__.xml.encoding", Dt::Data(encoding));
        return node;
    }

    void Xml::AddAttribute(Dt::Node &node, const std::string &key, const Dt::Data &value)
    {
        if (StringUtils::Find(key, '.'))
            return;
        std::string attributeKey = "__xmlattributes__.";
        attributeKey += key;
        node.Add(attributeKey, value);
    }

    void Xml::AddDeclaration(Dt::Node &node, const std::string &key, const std::string &attribute, const std::string &value)
    {
        if (StringUtils::Find(key, '.') || StringUtils::Find(attribute, '.'))
            return;
        std::string attributeKey = "__xmldeclarations__.";
        attributeKey += key + '.' + attribute;
        node.Add(attributeKey, Dt::Data(value));
    }

    Dt::Node Xml::LoadFromFile(const std::string &path)
    {
        Dt::Node node = parser.LoadFromFile(path);
        if (node != Dt::Node::null && node.GetNode("__xmldeclarations__.xml") == Dt::Node::null)
            return Dt::Node::null;
        return node;
    }

    Dt::Node Xml::LoadFromStream(std::istream &stream)
    {
        return parser.LoadFromStream(stream);
    }

    Dt::Node Xml::LoadFromContent(const std::string &xmlContent)
    {
        return parser.LoadFromContent(xmlContent);
    }
}