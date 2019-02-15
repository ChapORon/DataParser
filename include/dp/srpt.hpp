#ifndef DATAPARSER_SRPT_HPP
#define DATAPARSER_SRPT_HPP

#include "dp/parser/srpt.hpp"

namespace dp
{
    class srpt
    {
    private:
        static dp::parser::srpt parser;
    public:
        static const std::string str(const dt::node &, unsigned int = 0, unsigned int = 0);
        static void write(const dt::node &, std::ostream &, unsigned int = 0);
        static void write(const dt::node &, const std::string &, unsigned int = 0);
        static dt::node loadFromFile(const std::string &);
        static dt::node loadFromStream(std::istream &);
        static dt::node loadFromContent(const std::string &);
    };
}

#endif //DATAPARSER_SRPT_HPP
