#include "srpt.hpp"

dp::parser::srpt dp::srpt::parser;

const std::string dp::srpt::str(const dp::dt::node &node, unsigned int indentFactor, unsigned int depth)
{
    return parser.str(node, indentFactor, depth);
}

void dp::srpt::write(const dp::dt::node &node, std::ostream &os, unsigned int indentFactor)
{
    parser.write(node, os, indentFactor);
}

void dp::srpt::write(const dp::dt::node &node, const std::string &filename, unsigned int indentFactor)
{
    parser.write(node, filename, indentFactor);
}

dp::dt::node dp::srpt::loadFromFile(const std::string &path)
{
    return parser.loadFromFile(path);
}

dp::dt::node dp::srpt::loadFromStream(std::istream &stream)
{
    return parser.loadFromStream(stream);
}

dp::dt::node dp::srpt::loadFromContent(const std::string &xmlContent)
{
    return parser.loadFromContent(xmlContent);
}