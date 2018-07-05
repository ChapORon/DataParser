#ifndef DATAPARSER_XML_HPP
#define DATAPARSER_XML_HPP

#include <algorithm>
#include <fstream>
#include "dt/node.hpp"
#include "parser.hpp"

namespace dp
{
    class xml : public parser
    {
    private:
        static std::string treatCommentary(std::string &);
        static void treatAutoCloseMarkup(std::string &);
        static bool treatDeclarations(dt::node &, std::string &);
        static bool treatXmlDeclarations(dt::node &, const std::string &);
        static void treatXmlInformation(dt::node &, const std::string &);
        static void treatMarkupContent(dt::node &, const std::string &);
        static bool setAttributes(dt::node &, const std::string &);
        static bool treatContent(dt::node &, std::string &);
        static std::string extractName(std::string &content);

    public:
        static dt::node create(const std::string &, const std::string & = "1.0", const std::string & = "UTF-8");
        static void addAttribute(dt::node &, const std::string &, const dt::data &);
        static void addDeclaration(dt::node &, const std::string &, const std::string &, const std::string &);
        static const std::string str(const dt::node &, unsigned int = 2, unsigned int = 0);
        static void write(const dt::node &, std::ostream &, unsigned int = 2);
        static dt::node loadFromFile(const std::string &);
        static dt::node loadFromStream(std::istream &);
        static dt::node loadFromContent(const std::string &);
    };
}

#endif //DATAPARSER_XML_HPP
