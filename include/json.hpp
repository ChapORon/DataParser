#ifndef DATAPARSER_JSON_HPP
#define DATAPARSER_JSON_HPP

#include "parser/json.hpp"

namespace dp
{
    class json
    {
    private:
        static dp::parser::json parser;

    public:
        template <typename T>
        static void addToArray(dt::node &node, const std::string &key, const T &element)
        {
            parser.addToArray(node, key, element);
        }
        template <typename T>
        static void addArray(dt::node &node, const std::string &key, const std::vector<T> &array)
        {
            parser.addArray(node, key, array);
        }
        static const std::string str(const dt::node &, unsigned int = 2, unsigned int = 0);
        static void write(const dt::node &, std::ostream &, unsigned int = 2);
        static void write(const dt::node &, const std::string &, unsigned int = 2);
        static dt::node loadFromFile(const std::string &);
        static dt::node loadFromStream(std::istream &);
        static dt::node loadFromContent(const std::string &);
    };
}

#endif //DATAPARSER_JSON_HPP
