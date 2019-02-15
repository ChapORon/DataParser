#include "dp/parser/parser.hpp"

bool dp::parser::parser::start_with(const std::string &str, const std::string &search, size_t pos)
{
    for (unsigned long n = 0; n != search.length(); ++n)
    {
        if ((n + pos) > str.length() ||
            str[n + pos] != search[n])
            return false;
    }
    return true;
}

bool dp::parser::parser::end_with(const std::string &str, const std::string &search)
{
    long strlen = str.length() - 1, searchlen = search.length() - 1;
    for (unsigned long n = search.length(); n != 0; --n)
    {
        if ((strlen + n) < 0 ||
                str[strlen + n] != search[searchlen - n])
            return false;
    }
    return (str[strlen] == search[searchlen]);
}

void dp::parser::parser::replace_all(std::string &str, const std::string &search, const std::string &replace)
{
    size_t pos;
    while ((pos = str.find(search, 0)) != std::string::npos)
        str.replace(pos, search.length(), replace);
}

void dp::parser::parser::trim(std::string &str)
{
    replace_all(str, "\t", " ");
    replace_all(str, "  ", " ");
    if (str[0] == ' ')
        str = str.substr(1);
    if (str[str.length() - 1] == ' ')
        str = str.substr(0, str.length() - 1);
}

size_t dp::parser::parser::count(std::string &str, const std::string &regex)
{
    size_t pos = 0, count = 0;
    while ((pos = str.find(regex, pos)) != std::string::npos)
    {
        ++count;
        pos += regex.length();
    }
    return count;
}

std::vector<std::string> dp::parser::parser::split(const std::string &str, const std::string &regex)
{
    std::vector<std::string> vec;
    size_t prev_pos = 0, pos = 0;
    while((pos = str.find(regex, pos)) != std::string::npos)
    {
        std::string substr(str.substr(prev_pos, pos - prev_pos));
        vec.emplace_back(substr);
        pos += regex.size();
        prev_pos = pos;
    }
    vec.emplace_back(str.substr(prev_pos, pos - prev_pos));
    return vec;
}

void dp::parser::parser::byPassTrailing(const std::string &content, size_t &pos)
{
    char current = content[pos];
    while (current == ' ' || current == '\t' || current == '\n')
    {
        ++pos;
        current = content[pos];
    }
}

void dp::parser::parser::write(const dp::dt::node &node, std::ostream &os, unsigned int indentFactor)
{
    os << str(node, indentFactor);
}

void dp::parser::parser::write(const dp::dt::node &node, const std::string &filename, unsigned int indentFactor)
{
    std::ofstream file(filename);
    file << str(node, indentFactor);
}

dp::dt::node dp::parser::parser::loadFromFile(const std::string &path)
{
    struct stat buf;
    if (stat(path.c_str(), &buf) != 0)
        return dp::dt::node::null;
    std::ifstream fileStream(path.c_str());
    long int nbChar = buf.st_size;
    auto buffer = new char[nbChar];
    fileStream.read(buffer, nbChar);
    std::string content(buffer);
    return loadFromContent(content);
}

dp::dt::node dp::parser::parser::loadFromStream(std::istream &stream)
{
    if (!stream.good())
        return dp::dt::node::null;
    std::string content, line;
    while (std::getline(stream, line))
    {
        if (!line.empty())
        {
            content += line;
            content += '\n';
        }
    }
    return loadFromContent(content);
}