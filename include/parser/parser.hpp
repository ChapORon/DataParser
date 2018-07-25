#ifndef DATAPARSER_PARSER_PARSER_HPP
#define DATAPARSER_PARSER_PARSER_HPP

#include <fstream>
#include <string>
#include <vector>
#include "dt/node.hpp"

namespace dp::parser
{
    class parser
    {
    protected:
        bool start_with(const std::string &, const std::string &, size_t);
        bool end_with(const std::string &, const std::string &);
        void replace_all(std::string &, const std::string &, const std::string &);
        void trim(std::string &);
        size_t count(std::string &, const std::string &);
        std::vector<std::string> split(const std::string &, const std::string &);

    public:
        void write(const dt::node &, std::ostream &, unsigned int = 2);
        void write(const dt::node &, const std::string &, unsigned int = 2);
        dt::node loadFromFile(const std::string &);
        dt::node loadFromStream(std::istream &);
        virtual const std::string str(const dt::node &, unsigned int = 2, unsigned int = 0) = 0;
        virtual dt::node loadFromContent(const std::string &) = 0;
    };
}

#endif //DATAPARSER_PARSER_PARSER_HPP
