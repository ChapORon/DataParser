#ifndef DATAPARSER_MEW_HPP
#define DATAPARSER_MEW_HPP

#include <fstream>
#include <regex>
#include "dt/node.hpp"
#include "parser.hpp"

namespace dp
{
    class json : public parser
    {
    private:
        static std::string getValue(const dt::data &);
    public:
        static void addToArray(dt::node &, const std::string &, const std::string &);
        static void addArray(dt::node &, const std::string &, const std::vector<std::string> &);
        static const std::string str(const dt::node &, unsigned int = 2, unsigned int = 0);
        static void write(const dt::node &, std::ostream &, unsigned int = 2);
    };
}

#endif //DATAPARSER_MEW_HPP
