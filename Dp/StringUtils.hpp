#ifndef DATAPARSER_STRINGUTILS_HPP
#define DATAPARSER_STRINGUTILS_HPP

#include <string>

namespace Dp
{
	class StringUtils
	{
	public:
		static bool Find(const std::string &, char, unsigned long &);
		static bool Find(const std::string &, char);
	};
}

#endif //DATAPARSER_STRINGUTILS_HPP