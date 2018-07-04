#ifndef DATAPARSER_DATATREE_NODE_HPP
#define DATAPARSER_DATATREE_NODE_HPP

#include <sstream>
#include <utility>
#include <vector>
#include "data.hpp"

namespace dp::dt
{
    class node
    {
    private:
        data _value;
        std::vector<std::pair<std::string, node>> _childs;

    public:
        node();
        node(const data &);
        node &operator=(const node &);
        void add(const std::string &, const data &);
        node &get(const std::string &);
        data value() const;
        const std::vector<std::pair<std::string, node>> &childs() const;
    };
}

#endif //DATAPARSER_DATATREE_NODE_HPP
