#ifndef DATAPARSER_MEW_HPP
#define DATAPARSER_MEW_HPP

#include <fstream>
#include "dt/node.hpp"
#include "parser.hpp"

namespace dp
{
    class mew : public parser
    {
    public:
        static const std::string str(const dt::node &, unsigned int = 0);
        static void write(const dt::node &, std::ostream &);
    };
}

#endif //DATAPARSER_MEW_HPP
