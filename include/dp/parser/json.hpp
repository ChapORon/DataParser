#ifndef DATAPARSER_PARSER_JSON_HPP
#define DATAPARSER_PARSER_JSON_HPP

#include <regex>
#include "dp/parser/parser.hpp"

namespace dp
{
    class json;
    namespace parser
    {
        class json : public parser
        {
            friend class dp::json;
        private:
            json() = default;
            std::string getValue(const std::string &);

        public:
            template<typename T>
            void addToArray(dt::node &node, const std::string &key, const T &element)
            {
                std::string newKey = key + ".array";
                node.add(newKey, dp::dt::node("", dp::dt::data(element)));
            }

            template<typename T>
            void addArray(dt::node &node, const std::string &key, const std::vector<T> &array)
            {
                std::string newKey = key + ".array";
                for (const auto &element : array)
                    node.add(newKey, dp::dt::node("", dp::dt::data(element)));
            }
            const std::string str(const dt::node &, unsigned int = 2, unsigned int = 0) override;
            dt::node loadFromContent(const std::string &) override;
        };
    }
}

#endif //DATAPARSER_PARSER_JSON_HPP
