#ifndef DATAPARSER_DATATREE_NODE_HPP
#define DATAPARSER_DATATREE_NODE_HPP

#include <algorithm>
#include <sstream>
#include <utility>
#include <vector>
#include "data.hpp"

namespace dp::dt
{
    class node
    {
    public:
        typedef node *iterator;
        typedef const node *const_iterator;
    private:
        std::string _name;
        data _value;
        std::vector<node> _childs;

    public:
        node();
        node(const std::string &);
        node(const std::string &, const data &);
        node &operator=(const node &);
        void name(const std::string &_name);
        void value(const data &);
        void add(const node &);
        void add(const std::string &, const data &);
        node &get(const std::string &);
        const node &get(const std::string &) const;
        const data &value() const;
        const std::string &name() const;
        const std::vector<node> &childs() const;
        bool find(const std::string &) const;
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        bool operator==(const node &rhs) const;
        bool operator!=(const node &rhs) const;
    };
}

#endif //DATAPARSER_DATATREE_NODE_HPP
