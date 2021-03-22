#ifndef DATAPARSER_PARSER_PARSER_HPP
#define DATAPARSER_PARSER_PARSER_HPP

#include <fstream>
#include <string>
#include <sys/stat.h>
#include <vector>
#include "Dp/Dt/Node.hpp"

namespace Dp
{
    namespace Parser
    {
        class Parser
        {
        protected:
            bool StartWith(const std::string &, const std::string &, size_t);
            void ByPassTrailing(const std::string &, size_t &);

        public:
            void Write(const Dt::Node &, std::ostream &, unsigned int = 2);
            void Write(const Dt::Node &, const std::string &, unsigned int = 2);
            Dt::Node LoadFromFile(const std::string &);
            Dt::Node LoadFromStream(std::istream &);
            virtual const std::string Str(const Dt::Node &, unsigned int = 2, unsigned int = 0, bool = true) = 0;
            virtual Dt::Node LoadFromContent(const std::string &) = 0;
        };
    }
}

#endif //DATAPARSER_PARSER_PARSER_HPP
