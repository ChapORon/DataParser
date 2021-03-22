#ifndef DATAPARSER_DATATREE_NODE_HPP
#define DATAPARSER_DATATREE_NODE_HPP

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include "Dp/Dt/Data.hpp"

namespace Dp
{
    namespace Dt
    {
        class Node
        {
        public:
            static const Node null;
            typedef Node *iterator;
            typedef const Node *const_iterator;
        private:
            bool m_Null;
            std::string m_Name;
            Data m_Value;
            std::vector<Node> m_Childs;

        private:
            Node(bool);
            int ExtractPos(std::string &) const;
			void ReplaceAt(const std::string &, int, const Dt::Data &);
			void InsertAt(const std::string &, int, const Dt::Data &);

        public:
            Node();
            Node(const char *);
            Node(const std::string &);
            Node(const char *, const Data &);
            Node(const std::string &, const Data &);
            Node &operator=(const Node &);
            void SetName(const std::string &_name);
            void SetValue(const Data &);
            template <typename T>
            void Add(const std::string &key, const T &value, bool replace = false)
            {
                Add(key, Dt::Data(value), replace);
            }
            void Add(const std::string &, const Data &, bool = false);
            void Add(const Node &, bool = false);
            bool Remove(const std::string &);
            const Node &GetNode(const std::string &) const;
            bool HaveValue() const;
            template <typename T>
            T Get(const std::string &key) const { return GetNode(key).Get<T>(); }
            template <typename T>
            T Get() const { static_assert(sizeof(T) == 0, "Dp::Dt::node::get can only be call with template bool, char, int, float, double, long, std::string and const std::string &"); }
            const std::string &GetName() const;
            const std::vector<Node> &GetChilds() const;
            bool Find(const std::string &) const;
            bool IsEmpty() const;
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;
            bool operator==(const Node &rhs) const;
            bool operator!=(const Node &rhs) const;
			bool IsNull() const;
			bool HaveChild() const;
			bool HaveNamedChild() const;
        };
    }
}

template <> bool Dp::Dt::Node::Get<bool>() const;
template <> char Dp::Dt::Node::Get<char>() const;
template <> int Dp::Dt::Node::Get<int>() const;
template <> float Dp::Dt::Node::Get<float>() const;
template <> double Dp::Dt::Node::Get<double>() const;
template <> long Dp::Dt::Node::Get<long>() const;
template <> std::string Dp::Dt::Node::Get<std::string>() const;
template <> const std::string &Dp::Dt::Node::Get<const std::string &>() const;

#endif //DATAPARSER_DATATREE_NODE_HPP
