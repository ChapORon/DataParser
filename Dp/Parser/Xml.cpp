#include "Dp/Parser/Xml.hpp"

namespace Dp
{
    namespace Parser
	{
		void Xml::AddValue(std::string &content, const std::string &value, const std::string &tab)
		{
			for (char c : value)
			{
				if (c == '<')
					content += "&lt;";
				else if (c == '>')
					content += "&gt;";
				else if (c == '&')
					content += "&amp;";
				else if (c == '\'')
					content += "&apos;";
				else if (c == '"')
					content += "&quot;";
				else if (c == '\n')
				{
					content += c;
					content += tab;
				}
				else
					content += c;
			}
		}

		const std::string Xml::Str(const Dt::Node &node, unsigned int indentFactor, unsigned int depth, bool)
		{
			if (depth == 0)
			{
				if (node == Dt::Node::null)
					return "(null)\n";
				else if (node.IsEmpty())
					return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			}
			std::string name = node.GetName();
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			std::string indent(indentFactor, ' ');
			std::string tabs;
			for (size_t n = 0; n != depth; ++n)
				tabs += indent;
			std::string content;
			if (node.HaveChild() && !node.HaveNamedChild())
			{
				for (const auto &tag : node.GetChilds())
				{
					Dt::Node newTag = tag;
					newTag.SetName(node.GetName());
					content += Str(newTag, indentFactor, depth);
				}
				return content;
			}
			unsigned int minSize = 0;
			Dt::Node elements = node.GetNode("__xmldeclarations__");
			if (depth == 0 && elements != Dt::Node::null)
			{
				for (const auto &element : elements)
				{
					content += "<?" + element.GetName();
					for (const auto &info : element)
					{
						content += " " + info.GetName() + "=\"";
						AddValue(content, info.Get<const std::string &>(), tabs);
						content += '"';
					}
					content += "?>\n";
				}
				++minSize;
			}
			content += tabs + "<" + name;
			Dt::Node attributes = node.GetNode("__xmlattributes__");
			if (attributes != Dt::Node::null)
			{
				for (const auto &attribute : attributes)
				{
					content += " " + attribute.GetName() + "=\"";
					AddValue(content, attribute.Get<const std::string &>(), tabs);
					content += '"';
				}
				++minSize;
			}
			bool nodeHaveValue = node.HaveValue();
			auto tags = node.GetChilds();
			if (nodeHaveValue && tags.size() == minSize)
				content += " />\n";
			else
			{
				content += ">\n";
				if (!nodeHaveValue)
				{
					content += tabs;
					content += indent;
					AddValue(content, node.Get<const std::string &>(), (tabs + indent));
					content += '\n';
				}
				for (const auto &tag : tags)
				{
					if (tag.GetName().find("__") != 0)
						content += Str(tag, indentFactor, depth + 1);
				}
				content += tabs;
				content += "</";
				content += name;
				content += ">\n";
			}
			return content;
		}

		bool Xml::ByPassComment(const std::string &content, size_t &pos)
		{
			if (StartWith(content, "<!--", pos))
			{
				pos += 4;
				while (!StartWith(content, "-->", pos))
					++pos;
				pos += 3;
				return true;
			}
			return false;
		}

		void Xml::ByPass(const std::string &content, size_t &pos)
		{
			ByPassTrailing(content, pos);
			if (ByPassComment(content, pos))
				ByPass(content, pos);
		}

		std::string Xml::LoadValue(const std::string &content, size_t &pos)
		{
			bool escaping = false;
			char current = content[pos];
			if (current != '<')
			{
				std::string value, escape;
				value += current;
				++pos;
				current = content[pos];
				while (current != '<' && pos != content.length())
				{
					if (escaping)
					{
						if (current != ';')
							escape += current;
						else
						{
							if (escape == "lt")
								value += '<';
							else if (escape == "gt")
								value += '>';
							else if (escape == "amp")
								value += '&';
							else if (escape == "apos")
								value += '\'';
							else if (escape == "quot")
								value += '"';
							escaping = false;
						}
						++pos;
					}
					else if (current == '\n')
					{
						value += current;
						ByPass(content, pos);
					}
					else if (current == '&')
					{
						escaping = true;
						++pos;
					}
					else
					{
						value += current;
						++pos;
					}
					current = content[pos];
				}
				if (pos == content.length())
					return "";
				value = value.substr(0, value.find_last_not_of(" \t\n") + 1);
				ByPass(content, pos);
				std::string add = LoadValue(content, pos);
				if (!add.empty())
					value += add;
				return value;
			}
			return "";
		}

		Dt::Node Xml::LoadAttribute(const std::string &content, size_t &pos)
		{
			bool escaping = false;
			std::string name, value, escape;
			while (content[pos] != '=' && pos != content.length())
			{
				name += content[pos];
				++pos;
			}
			if (pos == content.length() ||
				(pos + 1) == content.length() ||
				content[pos + 1] != '"' ||
				(pos + 2) == content.length())
				return Dt::Node::null;
			pos += 2;
			char current = content[pos];
			while (content[pos] != '"' && pos != content.length())
			{
				if (escaping)
				{
					if (current != ';')
						escape += current;
					else
					{
						if (escape == "lt")
							value += '<';
						else if (escape == "gt")
							value += '>';
						else if (escape == "amp")
							value += '&';
						else if (escape == "apos")
							value += '\'';
						else if (escape == "quot")
							value += '"';
						escaping = false;
					}
					++pos;
				}
				else if (current == '\n')
				{
					value += current;
					ByPass(content, pos);
				}
				else if (current == '&')
				{
					escaping = true;
					++pos;
				}
				else
				{
					value += current;
					++pos;
				}
				current = content[pos];
			}
			if (pos == content.length())
				return Dt::Node::null;
			value = value.substr(0, value.find_last_not_of(" \t\n") + 1);
			++pos;
			return Dt::Node(name, Dt::Data(value));
		}

		Dt::Node Xml::CreateNodeFromTag(const std::string &content, bool declarations)
		{
			size_t pos = 0;
			char current = content[pos];
			std::string name;
			name += current;
			++pos;
			current = content[pos];
			while (current != ' ' && current != '\t' && pos != content.length())
			{
				if (current == '>')
					return Dt::Node(name);
				name += current;
				++pos;
				current = content[pos];
			}
			Dt::Node node(name);
			if (pos == content.length())
				return node;
			ByPassTrailing(content, pos);
			current = content[pos];
			if (current == '>')
				return node;
			Dt::Node attributes("__xmlattributes__");
			while (current != '/' && current != '?' && current != '>' && current != '\0')
			{
				if (declarations)
					node.Add(LoadAttribute(content, pos));
				else
					attributes.Add(LoadAttribute(content, pos));
				ByPassTrailing(content, pos);
				current = content[pos];
			}
			if (!attributes.IsEmpty())
				node.Add(attributes);
			return node;
		}

		Dt::Node Xml::LoadNode(const std::string &content, size_t &pos)
		{
			++pos;
			char current = content[pos];
			if (current == '/')
				return Dt::Node::null;
			std::string nodeOpenTag;
			nodeOpenTag += current;
			++pos;
			current = content[pos];
			while (current != '>' && pos != content.length())
			{
				nodeOpenTag += current;
				++pos;
				current = content[pos];
			}
			if (pos == content.length())
				return Dt::Node::null;
			Dt::Node node = CreateNodeFromTag(nodeOpenTag, false);
			++pos;
			ByPass(content, pos);
			if (nodeOpenTag[nodeOpenTag.length() - 1] == '/')
				return node;
			std::string nodeValue, valueToAdd;
			while (!StartWith(content, "</", pos))
			{
				valueToAdd = LoadValue(content, pos);
				if (!valueToAdd.empty())
				{
					if (!nodeValue.empty())
						nodeValue += '\n';
					nodeValue += valueToAdd;
				}
				ByPass(content, pos);
				if (!StartWith(content, "</", pos))
				{
					Dt::Node child = LoadNode(content, pos);
					if (child == Dt::Node::null)
						return Dt::Node::null;
					node.Add(child);
				}
				if (pos == content.length())
					return Dt::Node::null;
			}
			node.SetValue(Dt::Data(nodeValue));
			pos += 2;
			if (!StartWith(content, node.GetName(), pos))
				return Dt::Node::null;
			pos += node.GetName().length() + 1;
			ByPass(content, pos);
			return node;
		}

		Dt::Node Xml::LoadDeclaration(const std::string &content, size_t &pos)
		{
			++pos;
			char current = content[pos];
			if (current == '/')
				return Dt::Node::null;
			std::string nodeOpenTag;
			nodeOpenTag += current;
			++pos;
			current = content[pos];
			while (current != '?' && pos != content.length())
			{
				nodeOpenTag += current;
				++pos;
				current = content[pos];
			}
			++pos;
			if (pos == content.length())
				return Dt::Node::null;
			++pos;
			return CreateNodeFromTag(nodeOpenTag, true);
		}

		Dt::Node Xml::LoadDeclarations(const std::string &content, size_t &pos)
		{
			Dt::Node declarations("__xmldeclarations__");
			while (StartWith(content, "<?", pos))
			{
				++pos;
				Dt::Node declaration = LoadDeclaration(content, pos);
				if (declaration == Dt::Node::null)
					return Dt::Node::null;
				declarations.Add(declaration);
				ByPass(content, pos);
			}
			return declarations;
		}

		Dt::Node Xml::LoadFromContent(const std::string &content)
		{
			size_t pos = 0;
			ByPass(content, pos);
			Dt::Node declarations = LoadDeclarations(content, pos);
			if (declarations == Dt::Node::null)
				return Dt::Node::null;
			ByPass(content, pos);
			if (content[pos] != '<')
				return Dt::Node::null;
			Dt::Node node = LoadNode(content, pos);
			if (node == Dt::Node::null)
				return Dt::Node::null;
			if (!declarations.IsEmpty())
				node.Add(declarations);
			return node;
		}
    }
}
