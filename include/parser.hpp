#ifndef DATAPARSER_PARSER_HPP
#define DATAPARSER_PARSER_HPP

#include <string>
#include <vector>

namespace dp
{
    class parser
    {
    protected:
        static bool start_with(const std::string &, const std::string &);
        static bool end_with(const std::string &, const std::string &);
        static void replace_all(std::string &, const std::string &, const std::string &);
        static void trim(std::string &);
        static size_t count(std::string &, const std::string &);
        static std::vector<std::string> split(const std::string &, const std::string &);
    };
}

#endif //DATAPARSER_PARSER_HPP
