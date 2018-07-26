#ifndef DATAPARSER_PARSER_XML_HPP
#define DATAPARSER_PARSER_XML_HPP

#include <algorithm>
#include "parser.hpp"

namespace dp
{
    class xml;
    namespace parser
    {
        class xml : public parser
        {
            friend class dp::xml;
        private:
            xml() = default;
            dp::dt::node loadAttribute(const std::string &, size_t &);
            dp::dt::node createNodeFromTag(const std::string &, bool);
            bool byPassComment(const std::string &, size_t &);
            void byPass(const std::string &, size_t &);
            std::string loadValue(const std::string &, size_t &);
            dp::dt::node loadNode(const std::string &, size_t &);
            dp::dt::node loadDeclaration(const std::string &, size_t &);
            dp::dt::node loadDeclarations(const std::string &, size_t &);

        public:
            const std::string str(const dt::node &, unsigned int = 2, unsigned int = 0) override;
            dt::node loadFromContent(const std::string &) override;
        };
    }
}

#endif //DATAPARSER_PARSER_XML_HPP
