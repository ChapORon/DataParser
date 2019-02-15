#ifndef DATAPARSER_PARSER_SRPT_HPP
#define DATAPARSER_PARSER_SRPT_HPP

#include <regex>
#include "dp/parser/parser.hpp"

namespace dp
{
    class srpt;
    namespace parser
    {
        class srpt : public parser
        {
            friend class dp::srpt;
        private:
            srpt() = default;
            std::string getValue(const dt::data &);

        public:
            const std::string str(const dt::node &, unsigned int = 0, unsigned int = 0);
            dt::node loadFromContent(const std::string &);
        };
    }
}

#endif //DATAPARSER_PARSER_SRPT_HPP
