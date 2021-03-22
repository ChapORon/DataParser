#ifndef DATAPARSER_JSON_HPP
#define DATAPARSER_JSON_HPP

#include "Dp/Parser/Json.hpp"

namespace Dp
{
    class Json
    {
    private:
        static Parser::Json parser;

    public:
        template <typename T>
        static void AddToArray(Dt::Node &node, const std::string &key, const T &element)
        {
            parser.AddToArray(node, key, element);
        }
        template <typename T>
        static void AddArray(Dt::Node &node, const std::string &key, const std::vector<T> &array)
        {
            parser.AddArray(node, key, array);
        }
        static const std::string Str(const Dt::Node &, unsigned int = 2, unsigned int = 0, bool = true);
        static void Write(const Dt::Node &, std::ostream &, unsigned int = 2);
        static void Write(const Dt::Node &, const std::string &, unsigned int = 2);
        static Dt::Node LoadFromFile(const std::string &);
        static Dt::Node LoadFromStream(std::istream &);
        static Dt::Node LoadFromContent(const std::string &);
    };
}

#endif //DATAPARSER_JSON_HPP
