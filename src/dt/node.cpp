#include "dt/node.hpp"

dp::dt::node::node() {}

dp::dt::node::node(const std::string &name) : _name(name) {}

dp::dt::node::node(const std::string &name, const data &value) : _name(name), _value(value) {}

dp::dt::node &dp::dt::node::operator=(const node &other)
{
    _value = other._value;
    _childs = other._childs;
    return *this;
}

void dp::dt::node::add(const node &node)
{
    _childs.emplace_back(node);
}

#include <iostream>

void dp::dt::node::add(const std::string &key, const data &value)
{
    unsigned long pos = key.find('.');
    if (pos != std::string::npos)
    {
        std::string name = key.substr(0, pos);
        std::string newKey = key.substr(pos + 1);
        for (auto &child : _childs)
        {
            if (child.name() == name)
            {
                child.add(newKey, value);
                return;
            }
        }
        _childs.emplace_back(node(name));
        _childs[_childs.size() - 1].add(newKey, value);
    }
    else
    {
        for (auto &pair : _childs)
        {
            if (pair.name() == key)
                pair._value = value;
        }
        _childs.emplace_back(node(key, value));
    }
}
const dp::dt::data &dp::dt::node::value() const
{
    return _value;
}

const std::string &dp::dt::node::name() const
{
    return _name;
}

const std::vector<dp::dt::node> &dp::dt::node::childs() const
{
    return _childs;
}

dp::dt::node &dp::dt::node::get(const std::string &path)
{
    for (auto &child : _childs)
    {
        if (child.name() == path)
            return child;
    }
    _childs.emplace_back(node(path));
    return _childs[_childs.size() - 1];
}

bool dp::dt::node::find(const std::string &key) const
{
    for (const auto &child : _childs)
    {
        if (child.name() == key)
            return true;
    }
    return false;
}

const dp::dt::node &dp::dt::node::get(const std::string &path) const
{
    for (auto &child : _childs)
    {
        if (child.name() == path)
            return child;
    }
    throw std::exception();
}

void dp::dt::node::value(const dp::dt::data &value)
{
    _value = value;
}

dp::dt::node::iterator dp::dt::node::begin()
{
    return &_childs[0];
}

dp::dt::node::const_iterator dp::dt::node::begin() const
{
    return &_childs[0];
}

dp::dt::node::iterator dp::dt::node::end()
{
    return &_childs[_childs.size()];
}

dp::dt::node::const_iterator dp::dt::node::end() const
{
    return &_childs[_childs.size()];
}

bool dp::dt::node::operator==(const dp::dt::node &rhs) const
{
    return _name == rhs._name &&
           _value == rhs._value &&
           _childs == rhs._childs;
}

bool dp::dt::node::operator!=(const dp::dt::node &rhs) const
{
    return !(rhs == *this);
}

void dp::dt::node::name(const std::string &name)
{
    _name = name;
}
