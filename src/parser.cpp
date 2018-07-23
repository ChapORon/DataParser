#include "parser.hpp"

bool dp::parser::start_with(const std::string &str, const std::string &search)
{
    for (unsigned long n = 0; n != search.length(); ++n)
    {
        if (str[n] != search[n])
            return false;
    }
    return true;
}

bool dp::parser::end_with(const std::string &str, const std::string &search)
{
    unsigned long strlen = str.length() - 1, searchlen = search.length() - 1;
    for (unsigned long n = search.length(); n != 0; --n)
    {
        if (str[strlen + n] != search[searchlen - n])
            return false;
    }
    return (str[strlen] == search[searchlen]);
}

void dp::parser::replace_all(std::string &str, const std::string &search, const std::string &replace)
{
    size_t pos;
    while ((pos = str.find(search, 0)) != std::string::npos)
        str.replace(pos, search.length(), replace);
}

void dp::parser::trim(std::string &str)
{
    replace_all(str, "\t", " ");
    replace_all(str, "  ", " ");
    if (str[0] == ' ')
        str = str.substr(1);
    if (str[str.length() - 1] == ' ')
        str = str.substr(0, str.length() - 1);
}

size_t dp::parser::count(std::string &str, const std::string &regex)
{
    size_t pos = 0, count = 0;
    while ((pos = str.find(regex, pos)) != std::string::npos)
    {
        ++count;
        pos += regex.length();
    }
    return count;
}

std::vector<std::string> dp::parser::split(const std::string &str, const std::string &regex)
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