#include "Dp/Json.hpp"

Dp::Parser::Json Dp::Json::parser;

namespace Dp
{
    const std::string Json::Str(const Dt::Node &node, unsigned int indentFactor, unsigned int depth, bool breakLine)
    {
        return parser.Str(node, indentFactor, depth, breakLine);
    }

    void Json::Write(const Dt::Node &node, std::ostream &os, unsigned int indentFactor)
    {
        parser.Write(node, os, indentFactor);
    }

    void Json::Write(const Dt::Node &node, const std::string &filename, unsigned int indentFactor)
    {
        parser.Write(node, filename, indentFactor);
    }

    Dt::Node Json::LoadFromFile(const std::string &path)
    {
        return parser.LoadFromFile(path);
    }

    Dt::Node Json::LoadFromStream(std::istream &stream)
    {
        return parser.LoadFromStream(stream);
    }

    Dt::Node Json::LoadFromContent(const std::string &xmlContent)
    {
        return parser.LoadFromContent(xmlContent);
    }
}