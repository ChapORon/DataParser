#include "Dp/StringUtils.hpp"

namespace Dp
{
	bool StringUtils::Find(const std::string &str, char search, unsigned long &pos)
	{
		unsigned long n = 0;
		while (str[n] != '\0')
		{
			if (str[n] == search)
			{
				pos = n;
				return true;
			}
			++n;
		}
		return false;
	}
	bool StringUtils::Find(const std::string &str, char search)
	{
		unsigned long n = 0;
		while (str[n] != '\0')
		{
			if (str[n] == search)
				return true;
			++n;
		}
		return false;
	}
}