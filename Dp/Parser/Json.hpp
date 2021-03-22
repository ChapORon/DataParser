#ifndef DATAPARSER_PARSER_JSON_HPP
#define DATAPARSER_PARSER_JSON_HPP

#include <regex>
#include "Dp/Parser/Parser.hpp"

namespace Dp
{
    class Json;
    namespace Parser
    {
        class Json : public Parser
        {
            friend class Dp::Json;
        private:
            enum class EJsonElementType: int
            {
                OBJECT,
                VALUE,
                ARRAY
            };
        private:
            Json() = default;
            std::string GetValue(const std::string &);
            EJsonElementType GetType(const Dt::Node &);
			const std::string StrObject(const Dt::Node &, const std::string &, unsigned int, unsigned int, bool);
            const std::string StrValue(const Dt::Node &);
            const std::string StrArray(const Dt::Node &, const std::string &, unsigned int, unsigned int, bool);

        public:
            template<typename T>
            void AddToArray(Dt::Node &node, const std::string &key, const T &element)
            {
                node.Add(key, Dt::Node("", Dt::Data(element)));
            }

            template<typename T>
            void AddArray(Dt::Node &node, const std::string &key, const std::vector<T> &array)
            {
                for (const auto &element : array)
                    node.Add(key, Dt::Node("", Dt::Data(element)));
            }
            const std::string Str(const Dt::Node &, unsigned int = 2, unsigned int = 0, bool = true) override;
            Dt::Node LoadFromContent(const std::string &) override;
        };
    }
}

#endif //DATAPARSER_PARSER_JSON_HPP
