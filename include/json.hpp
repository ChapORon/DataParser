#ifndef DATAPARSER_JSON_HPP
#define DATAPARSER_JSON_HPP

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
        template <typename T>
        static void addArray(dt::node &node, const std::string &key, const std::vector<T> &array)
        {
            std::string newKey = key + ".array";
            for (const auto &element : array)
                node.add(newKey, dp::dt::node("", dp::dt::data(element)));
        }
        static const std::string str(const dt::node &, unsigned int = 2, unsigned int = 0);
        static void write(const dt::node &, std::ostream &, unsigned int = 2);
        static dt::node loadFromFile(const std::string &);
        static dt::node loadFromStream(std::istream &);
        static dt::node loadFromContent(const std::string &);
    };
}

#endif //DATAPARSER_JSON_HPP
