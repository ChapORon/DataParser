#ifndef DATAPARSER_DATATREE_NODE_HPP
#define DATAPARSER_DATATREE_NODE_HPP

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include "dp/dt/data.hpp"

namespace dp::dt
{
    class node
    {
    public:
        static const node null;
        typedef node *iterator;
        typedef const node *const_iterator;
    private:
        bool _null;
        std::string _name;
        data _value;
        std::vector<node> _childs;

    private:
        node(bool);
        int extractPos(std::string &) const;

    public:
        node();
        node(const char *);
        node(const std::string &);
        node(const char *, const data &);
        node(const std::string &, const data &);
        node &operator=(const node &);
        void name(const std::string &_name);
        void value(const data &);
        void add(const std::string &, const data &, bool = false);
        void add(const std::string &, const node &, bool = false);
        void add(const node &, bool = false);
        bool remove(const std::string &);
        const node &get(const std::string &) const;
        bool haveValue() const;
        template <typename T>
        T get() const {static_assert(sizeof(T) == 0, "dp::dt::node::get can only be call with template bool, char, int, float, double, long, std::string and const std::string &");}
        const std::string &name() const;
        const std::vector<node> &childs() const;
        bool find(const std::string &) const;
        bool empty() const;
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        bool operator==(const node &rhs) const;
        bool operator!=(const node &rhs) const;
        bool isNull() const;
    };
}

template <> bool dp::dt::node::get<bool>() const;
template <> char dp::dt::node::get<char>() const;
template <> int dp::dt::node::get<int>() const;
template <> float dp::dt::node::get<float>() const;
template <> double dp::dt::node::get<double>() const;
template <> long dp::dt::node::get<long>() const;
template <> std::string dp::dt::node::get<std::string>() const;
template <> const std::string &dp::dt::node::get<const std::string &>() const;

#endif //DATAPARSER_DATATREE_NODE_HPP
