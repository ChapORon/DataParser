#include "parser/xml.hpp"

const std::string dp::parser::xml::str(const dp::dt::node &node, unsigned int indentFactor, unsigned int depth)
{
    if (depth == 0 && node.empty())
        return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    if (node == dt::node::null)
        return "(null)\n";
    std::string name = node.name();
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    std::string indent(indentFactor, ' ');
    std::string tabs;
    for (size_t n = 0; n != depth; ++n)
        tabs += indent;
    std::string content;
    unsigned int minSize = 0;
    dt::node elements = node.get("__xmldeclarations__");
    if (depth == 0 && elements != dt::node::null)
    {
        for (const auto &element : elements)
        {
            content += "<?" + element.name();
            for (const auto &info : element)
                content += " " + info.name() + "=\"" + info.value().getString() + "\"";
            content += "?>\n";
        }
        ++minSize;
    }
    content += tabs + "<" + name;
    dt::node attributes = node.get("__xmlattributes__");
    if (attributes != dt::node::null)
    {
        for (const auto &attribute : attributes)
            content += " " + attribute.name() + "=\"" + attribute.value().getString() + "\"";
        ++minSize;
    }
    if (node.value().empty() && node.childs().size() == minSize)
        content += " />\n";
    else
    {
        content += ">\n";
        if (!node.value().empty())
        {
            content += tabs;
            content += indent;
            content += node.value().getString();
            content += '\n';
        }
        auto tags = node.childs();
        for (const auto &tag : tags)
        {
            if (tag.name().find("__") != 0)
                content += str(tag, indentFactor, depth + 1);
        }
        content += tabs;
        content += "</";
        content += name;
        content += ">\n";
    }
    return content;
}

bool dp::parser::xml::byPassComment(const std::string &content, size_t &pos)
{
    if (start_with(content, "<!-- ", pos))
    {
        pos += 5;
        while (!start_with(content, " -->", pos))
            ++pos;
        pos += 4;
        return true;
    }
    else if (start_with(content, "!-- ", (pos - 1)))
    {
        pos += 4;
        while (!start_with(content, " -->", pos))
            ++pos;
        pos += 4;
        return true;
    }
    return false;
}

void dp::parser::xml::byPass(const std::string &content, size_t &pos)
{
    byPassTrailing(content, pos);
    if (byPassComment(content, pos))
        byPass(content, pos);
}

std::string dp::parser::xml::loadValue(const std::string &content, size_t &pos)
{
    char current = content[pos];
    if (current != '<')
    {
        std::string value;
        value += current;
        ++pos;
        current = content[pos];
        while (current != '<' && pos != content.length())
        {
            if (current == '\n')
                byPass(content, pos);
            else
            {
                value += current;
                ++pos;
            }
            current = content[pos];
        }
        if (pos == content.length())
            return "";
        value = value.substr(0, value.find_last_not_of(" \t") + 1);
        std::string add = loadValue(content, pos);
        if (!add.empty())
            value += add;
        return value;
    }
    return "";
}

dp::dt::node dp::parser::xml::loadAttribute(const std::string &content, size_t &pos)
{
    std::string name, value;
    while (content[pos] != '=' && pos != content.length())
    {
        name += content[pos];
        ++pos;
    }
    if (pos == content.length() ||
        (pos + 1) == content.length() ||
        content[pos + 1] != '"' ||
        (pos + 2) == content.length())
        return dp::dt::node::null;
    pos += 2;
    while (content[pos] != '"' && pos != content.length())
    {
        value += content[pos];
        ++pos;
    }
    if (pos == content.length())
        return dp::dt::node::null;
    ++pos;
    return dp::dt::node(name, dp::dt::data(value));
}

dp::dt::node dp::parser::xml::createNodeFromTag(const std::string &content, bool declarations)
{
    size_t pos = 0;
    char current = content[pos];
    std::string name;
    name += current;
    ++pos;
    current = content[pos];
    while (current != ' ' && current != '\t' && pos != content.length())
    {
        if (current == '>')
            return dp::dt::node(name);
        name += current;
        ++pos;
        current = content[pos];
    }
    dp::dt::node node(name);
    if (pos == content.length())
        return node;
    byPassTrailing(content, pos);
    current = content[pos];
    if (current == '>')
        return node;
    dp::dt::node attributes("__xmlattributes__");
    while (current != '/' && current != '?' && current != '>' && current != '\0')
    {
        if (declarations)
            node.add(loadAttribute(content, pos));
        else
            attributes.add(loadAttribute(content, pos));
        byPassTrailing(content, pos);
        current = content[pos];
    }
    if (!attributes.empty())
        node.add(attributes);
    return node;
}

dp::dt::node dp::parser::xml::loadNode(const std::string &content, size_t &pos)
{
    ++pos;
    char current = content[pos];
    if (current == '/')
        return dp::dt::node::null;
    std::string nodeOpenTag;
    nodeOpenTag += current;
    ++pos;
    current = content[pos];
    while (current != '>' && pos != content.length())
    {
        nodeOpenTag += current;
        ++pos;
        current = content[pos];
    }
    if (pos == content.length())
        return dp::dt::node::null;
    dp::dt::node node = createNodeFromTag(nodeOpenTag, false);
    ++pos;
    byPass(content, pos);
    if (end_with(nodeOpenTag, "/"))
        return node;
    std::string nodeValue = loadValue(content, pos);
    while (!start_with(content, "</", pos))
    {
        nodeValue += loadValue(content, pos);
        byPass(content, pos);
        if (!start_with(content, "</", pos))
        {
            dp::dt::node child = loadNode(content, pos);
            if (child == dp::dt::node::null)
                return dp::dt::node::null;
            node.add(child);
        }
        if (pos == content.length())
            return dp::dt::node::null;
    }
    node.value(dp::dt::data(nodeValue));
    pos += 2;
    if (!start_with(content, node.name(), pos))
        return dp::dt::node::null;
    pos += node.name().length() + 1;
    byPass(content, pos);
    return node;
}

dp::dt::node dp::parser::xml::loadDeclaration(const std::string &content, size_t &pos)
{
    ++pos;
    char current = content[pos];
    if (current == '/')
        return dp::dt::node::null;
    std::string nodeOpenTag;
    nodeOpenTag += current;
    ++pos;
    current = content[pos];
    while (current != '?' && pos != content.length())
    {
        nodeOpenTag += current;
        ++pos;
        current = content[pos];
    }
    ++pos;
    if (pos == content.length())
        return dp::dt::node::null;
    ++pos;
    return createNodeFromTag(nodeOpenTag, true);
}

dp::dt::node dp::parser::xml::loadDeclarations(const std::string &content, size_t &pos)
{
    dp::dt::node declarations("__xmldeclarations__");
    while (start_with(content, "<?", pos))
    {
        ++pos;
        dp::dt::node declaration = loadDeclaration(content, pos);
        if (declaration == dp::dt::node::null)
            return dp::dt::node::null;
        declarations.add(declaration);
        byPass(content, pos);
    }
    return declarations;
}

dp::dt::node dp::parser::xml::loadFromContent(const std::string &content)
{
    size_t pos = 0;
    byPass(content, pos);
    dp::dt::node declarations = loadDeclarations(content, pos);
    if (declarations == dp::dt::node::null)
        return dp::dt::node::null;
    byPass(content, pos);
    if (content[pos] != '<')
        return dp::dt::node::null;
    dp::dt::node node = loadNode(content, pos);
    if (node == dp::dt::node::null)
        return dp::dt::node::null;
    if (!declarations.empty())
        node.add(declarations);
    return node;
}
