#include "Dp/Parser/Json.hpp"

namespace Dp
{
    namespace Parser
	{
		std::string Json::GetValue(const std::string &value)
		{
			if (value == "true" ||
				value == "false" ||
				std::regex_match(value, std::regex("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$")))
				return value;
			return '"' + value + '"';
		}
		
		Json::EJsonElementType Json::GetType(const Dt::Node &node)
		{
			auto elements = node.GetChilds();
			if (elements.empty())
				return EJsonElementType::VALUE;
			else if (node.HaveNamedChild())
				return EJsonElementType::OBJECT;
			return EJsonElementType::ARRAY;
		}

		const std::string Json::StrObject(const Dt::Node &node, const std::string &tabs, unsigned int indentFactor, unsigned int depth, bool breakLine)
		{
			std::string content;
			if (!node.GetName().empty())
				content += '"' + node.GetName() + "\": ";
			auto elements = node.GetChilds();
			content += '{';
			if (breakLine)
				content += "\n";
			unsigned int n = 0;
			for (const auto &element : elements)
			{
				if (element.GetName().empty())
					return "";
				if (n != 0)
				{
					if (breakLine)
						content += ",\n";
					else
						content += ", ";
				}
				content += Str(element, indentFactor, depth + 1, breakLine);
				++n;
			}
			if (!elements.empty())
			{
				content += tabs;
				content += '}';
				if (breakLine)
					content += '\n';
			}
			return content;
		}

		const std::string Json::StrArray(const Dt::Node &node, const std::string &tabs, unsigned int indentFactor, unsigned int depth, bool breakLine)
		{
			std::string content;
			if (!node.GetName().empty())
				content += '"' + node.GetName() + "\": ";
			auto elements = node.GetChilds();
			content += '[';
			if (breakLine)
				content += "\n";
			unsigned int n = 0;
			for (const auto &element : elements)
			{
				if (!element.GetName().empty())
					return "";
				if (n != 0)
				{
					if (breakLine)
						content += ",\n";
					else
						content += ", ";
				}
				content += Str(element, indentFactor, depth + 1, breakLine);
				++n;
			}
			if (!elements.empty())
			{
				content += tabs;
				content += ']';
				if (breakLine)
					content += '\n';
			}
			return content;
		}

		const std::string Json::StrValue(const Dt::Node &node)
		{
			std::string content;
			const std::string &name = node.GetName();
			if (!name.empty())
				content += '"' + name + "\": ";
			const std::string &value = node.Get<const std::string &>();
			if (!value.empty())
				content += value;
			return content;
		}

		const std::string Json::Str(const Dt::Node &node, unsigned int indentFactor, unsigned int depth, bool breakLine)
		{
			if (node == Dt::Node::null)
			{
				if (breakLine)
					return "(null)\n";
				else
					return "(null)";
			}
			std::string tabs;
			std::string indent(indentFactor, ' ');
			for (size_t n = 0; n != (depth + 1); ++n)
				tabs += indent;
			std::string content;
			if (depth == 0)
			{
				if (breakLine)
					content += "{\n";
				else
					content += '{';
			}
			content += tabs;
			switch (GetType(node))
			{
			case EJsonElementType::ARRAY:
			{
				content += StrArray(node, tabs, indentFactor, depth, breakLine);
				break;
			}
			case EJsonElementType::OBJECT:
			{
				content += StrObject(node, tabs, indentFactor, depth, breakLine);
				break;
			}
			case EJsonElementType::VALUE:
			{
				content += StrValue(node);
				break;
			}
			}
			if (depth == 0)
			{
				if (breakLine)
					content += "}\n";
				else
					content += '}';
			}
			return content;
		}

		Dt::Node Json::LoadFromContent(const std::string &jsonContent)
		{
			size_t pos = 0;
			std::string content = jsonContent;
			if (content.empty())
				return Dt::Node::null;
			ByPassTrailing(content, pos);
			Dt::Node node;
			return node;
		}
    }
}