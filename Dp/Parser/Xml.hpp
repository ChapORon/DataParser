#ifndef DATAPARSER_PARSER_XML_HPP
#define DATAPARSER_PARSER_XML_HPP

#include <algorithm>
#include "Dp/Parser/Parser.hpp"

namespace Dp
{
    class Xml;
    namespace Parser
    {
        class Xml : public Parser
        {
            friend class Dp::Xml;
        private:
            Xml() = default;
            void AddValue(std::string &, const std::string &, const std::string &);
            Dt::Node LoadAttribute(const std::string &, size_t &);
            Dt::Node CreateNodeFromTag(const std::string &, bool);
            bool ByPassComment(const std::string &, size_t &);
            void ByPass(const std::string &, size_t &);
            std::string LoadValue(const std::string &, size_t &);
            Dt::Node LoadNode(const std::string &, size_t &);
            Dt::Node LoadDeclaration(const std::string &, size_t &);
            Dt::Node LoadDeclarations(const std::string &, size_t &);

        public:
            const std::string Str(const Dt::Node &, unsigned int = 2, unsigned int = 0, bool = true) override;
            Dt::Node LoadFromContent(const std::string &) override;
        };
    }
}

#endif //DATAPARSER_PARSER_XML_HPP
