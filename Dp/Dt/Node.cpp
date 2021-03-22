#include "Dp/Dt/Node.hpp"

#include "Dp/StringUtils.hpp"

namespace Dp
{
    namespace Dt
	{
		const Node Node::null = Node(true);

		Node::Node() : m_Null(false) {}

		Node::Node(bool null) : m_Null(null) {}

		Node::Node(const char *name) : m_Null(false), m_Name(name) {}

		Node::Node(const std::string &name) : m_Null(false), m_Name(name) {}

		Node::Node(const char *name, const Data &value) : m_Null(false), m_Name(name), m_Value(value) {}

		Node::Node(const std::string &name, const Data &value) : m_Null(false), m_Name(name), m_Value(value) {}

		Node &Node::operator=(const Node &other)
		{
			m_Null = other.m_Null;
			m_Value = other.m_Value;
			m_Childs = other.m_Childs;
			return *this;
		}

		int Node::ExtractPos(std::string &key) const
		{
			unsigned long pos;
			unsigned long endPos;
			if (!StringUtils::Find(key, '(', pos))
				return -1;
			if (!StringUtils::Find(key, ')', endPos))
				return -1;
			std::string number = key.substr(pos + 1, key.length() - endPos);
			key = key.substr(0, pos) + key.substr(endPos + 1);
			return std::stoi(number) - 1;
		}

		void Node::ReplaceAt(const std::string &name, int pos, const Dt::Data &value)
		{
			for (auto &child : m_Childs)
			{
				if (child.GetName() == name)
				{
					if (pos <= 0)
					{
						child.m_Value = value;
						return;
					}
					--pos;
				}
				if (pos == 0)
					return;
			}
		}

		bool Node::HaveChild() const
		{
			return !m_Childs.empty();
		}

		bool Node::HaveNamedChild() const
		{
			for (const auto &child : m_Childs)
			{
				if (!child.m_Name.empty())
					return true;
			}
			return false;
		}

		void Node::InsertAt(const std::string &name, int pos, const Dt::Data &value)
		{
			bool found = false;
			unsigned int firstFound = 0;
			std::vector<Node> childs;
			for (unsigned int n = 0; n != m_Childs.size(); ++n)
			{
				Node child = m_Childs[n];
				if (child.GetName() == name)
				{
					if (!found)
					{
						firstFound = n;
						found = true;
					}
					if (!childs.empty() || child.m_Childs.empty() || child.HaveNamedChild())
					{
						m_Childs.erase(m_Childs.begin() + n);
						--n;
						child.SetName("");
						childs.emplace_back(child);
					}
					else
					{
						if (child.m_Childs.size() <= pos)
							child.m_Childs.emplace_back(Node("", value));
						else
							child.m_Childs.insert(child.m_Childs.begin() + pos, Node("", value));
						return;
					}
				}
			}
			if (!childs.empty())
			{
				if (childs.size() <= pos)
					childs.emplace_back(Node("", value));
				else
					childs.insert(childs.begin() + pos, Node("", value));
				Node newNode(name);
				newNode.m_Childs = childs;
				m_Childs.insert(m_Childs.begin() + firstFound, newNode);
			}
			else
				m_Childs.emplace_back(Node(name, value));
		}

		void Node::Add(const std::string &key, const Data &value, bool replace)
		{
			unsigned long pos;
			if (StringUtils::Find(key, '.', pos))
			{
				std::string name = key.substr(0, pos);
				std::string newKey = key.substr(pos + 1);
				int nb = ExtractPos(name);
				for (auto &child : m_Childs)
				{
					if (child.GetName() == name)
					{
						if (nb >= -1)
							--nb;
						if (nb < 0)
						{
							child.Add(newKey, value, replace);
							return;
						}
					}
				}
				if (nb > 0)
					return;
				m_Childs.emplace_back(Node(name));
				m_Childs[m_Childs.size() - 1].Add(newKey, value, replace);
			}
			else
			{
				std::string name = key;
				int nb = ExtractPos(name);
				if (replace)
					ReplaceAt(name, nb, value);
				else
					InsertAt(name, nb, value);
			}
		}

		void Node::Add(const Node &node, bool replace)
		{
			if (node == null)
				return;
			if (replace)
			{
				for (auto &child : m_Childs)
				{
					if (child.GetName() == node.GetName())
					{
						child.m_Value = node.m_Value;
						return;
					}
				}
			}
			m_Childs.emplace_back(node);
		}

		const std::string &Node::GetName() const
		{
			return m_Name;
		}

		const std::vector<Node> &Node::GetChilds() const
		{
			return m_Childs;
		}

		bool Node::Find(const std::string &key) const
		{
			return GetNode(key) != Node::null;
		}

		const Node &Node::GetNode(const std::string &key) const
		{
			unsigned long pos;
			if (StringUtils::Find(key, '.', pos))
			{
				std::string name = key.substr(0, pos);
				std::string newKey = key.substr(pos + 1);
				int nb = ExtractPos(name);
				for (auto &child : m_Childs)
				{
					if (child.GetName() == name)
					{
						if (nb >= -2)
							--nb;
						if (nb < 0)
						{
							auto &ret = child.GetNode(newKey);
							if (ret != Node::null)
								return ret;
							else if (nb == -1)
								return Node::null;
						}
					}
				}
				return Node::null;
			}
			else
			{
				std::string name = key;
				int nb = ExtractPos(name);
				for (auto &child : m_Childs)
				{
					if (child.GetName() == name)
					{
						if (nb >= -2)
							--nb;
						if (nb < 0)
							return child;
						if (nb == -1)
							return Node::null;
					}
				}
				return Node::null;
			}
		}

		bool Node::Remove(const std::string &key)
		{
			unsigned long pos;
			unsigned int nodeToRemove = 0;
			if (StringUtils::Find(key, '.', pos))
			{
				std::string name = key.substr(0, pos);
				std::string newKey = key.substr(pos + 1);
				int nb = ExtractPos(name);
				for (auto &child : m_Childs)
				{
					if (child.GetName() == name)
					{
						if (nb >= -2)
							--nb;
						if (nb < 0)
						{
							bool ret = child.Remove(newKey);
							if (ret)
								return true;
							else if (nb == -1)
								return false;
						}
					}
					++nodeToRemove;
				}
				return false;
			}
			else
			{
				std::string name = key;
				int nb = ExtractPos(name);
				for (auto &child : m_Childs)
				{
					if (child.GetName() == name)
					{
						if (nb >= -2)
							--nb;
						if (nb < 0)
						{
							m_Childs.erase(m_Childs.begin() + nodeToRemove);
							return true;
						}
						if (nb == -1)
							return false;
					}
					++nodeToRemove;
				}
				return false;
			}
		}

		void Node::SetValue(const Data &value)
		{
			m_Value = value;
		}

		bool Node::HaveValue() const
		{
			return m_Value.IsEmpty();
		}

		bool Node::IsEmpty() const
		{
			return m_Value.IsEmpty() && m_Childs.empty();
		}

		Node::iterator Node::begin()
		{
			return &m_Childs[0];
		}

		Node::const_iterator Node::begin() const
		{
			return &m_Childs[0];
		}

		Node::iterator Node::end()
		{
			return &m_Childs[m_Childs.size()];
		}

		Node::const_iterator Node::end() const
		{
			return &m_Childs[m_Childs.size()];
		}

		bool Node::operator==(const Node &other) const
		{
			if (m_Null && other.m_Null)
				return true;
			return m_Name == other.m_Name &&
				m_Null == other.m_Null &&
				m_Value == other.m_Value &&
				m_Childs == other.m_Childs;
		}

		bool Node::operator!=(const Node &other) const
		{
			return !(other == *this);
		}

		void Node::SetName(const std::string &name)
		{
			m_Name = name;
		}

		bool Node::IsNull() const
		{
			return m_Null;
		}
    }
}

template <> bool Dp::Dt::Node::Get<bool>() const { return m_Value.GetBool(); }
template <> char Dp::Dt::Node::Get<char>() const { return m_Value.GetChar(); }
template <> int Dp::Dt::Node::Get<int>() const { return m_Value.GetInt(); }
template <> float Dp::Dt::Node::Get<float>() const { return m_Value.GetFloat(); }
template <> double Dp::Dt::Node::Get<double>() const { return m_Value.GetDouble(); }
template <> long Dp::Dt::Node::Get<long>() const { return m_Value.GetLong(); }
template <> std::string Dp::Dt::Node::Get<std::string>() const { return m_Value.GetString(); }
template <> const std::string &Dp::Dt::Node::Get<const std::string &>() const { return m_Value.GetCString(); }
