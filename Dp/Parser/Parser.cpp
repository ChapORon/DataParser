#include "Dp/Parser/Parser.hpp"

namespace Dp
{
    namespace Parser
	{
		bool Parser::StartWith(const std::string &str, const std::string &search, size_t pos)
		{
			for (unsigned long n = 0; n != search.length(); ++n)
			{
				if ((n + pos) > str.length() ||
					str[n + pos] != search[n])
					return false;
			}
			return true;
		}

		void Parser::ByPassTrailing(const std::string &content, size_t &pos)
		{
			char current = content[pos];
			while (current == ' ' || current == '\t' || current == '\n')
			{
				++pos;
				current = content[pos];
			}
		}

		void Parser::Write(const Dt::Node &node, std::ostream &os, unsigned int indentFactor)
		{
			os << Str(node, indentFactor);
		}

		void Parser::Write(const Dt::Node &node, const std::string &filename, unsigned int indentFactor)
		{
			std::ofstream file(filename);
			file << Str(node, indentFactor);
		}

		Dt::Node Parser::LoadFromFile(const std::string &path)
		{
			struct stat buf;
			if (stat(path.c_str(), &buf) != 0)
				return Dt::Node::null;
			std::ifstream fileStream(path.c_str());
			long int nbChar = buf.st_size;
			auto buffer = new char[nbChar + 1];
			fileStream.read(buffer, nbChar);
			buffer[nbChar] = '\0';
			std::string content(buffer);
			return LoadFromContent(content);
		}

		Dt::Node Parser::LoadFromStream(std::istream &stream)
		{
			if (!stream.good())
				return Dt::Node::null;
			std::string content, line;
			while (std::getline(stream, line))
			{
				if (!line.empty())
				{
					content += line;
					content += '\n';
				}
			}
			return LoadFromContent(content);
		}
    }
}