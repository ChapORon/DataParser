#ifndef DATAPARSER_XML_HPP
#define DATAPARSER_XML_HPP

#include "Dp/Parser/Xml.hpp"

namespace Dp
{
    class Xml
    {
    private:
        static Parser::Xml parser;

    public:
        static Dt::Node Create(const std::string &, const std::string & = "1.0", const std::string & = "UTF-8");
        static void AddAttribute(Dt::Node &, const std::string &, const Dt::Data &);
        static void AddDeclaration(Dt::Node &, const std::string &, const std::string &, const std::string &);
        static const std::string Str(const Dt::Node &, unsigned int = 2, unsigned int = 0, bool = true);
        static void Write(const Dt::Node &, std::ostream &, unsigned int = 2);
        static void Write(const Dt::Node &, const std::string &, unsigned int = 2);
        static Dt::Node LoadFromFile(const std::string &);
        static Dt::Node LoadFromStream(std::istream &);
        static Dt::Node LoadFromContent(const std::string &);
    };
}

#endif //DATAPARSER_XML_HPP
