#include "dt/node.hpp"

const dp::dt::node dp::dt::node::null = dp::dt::node(true);

dp::dt::node::node() : _null(false) {}

dp::dt::node::node(bool null) : _null(null) {}

dp::dt::node::node(const std::string &name) : _null(false), _name(name) {}

dp::dt::node::node(const std::string &name, const data &value) : _null(false), _name(name), _value(value) {}

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

int dp::dt::node::extractPos(std::string &key) const
{
    auto pos = key.find('(');
    auto endPos = key.find(')');
    if (pos == std::string::npos)
        return -1;
    std::string number = key.substr(pos + 1, key.length() - endPos);
    key = key.substr(0, pos) + key.substr(endPos + 1);
    return std::stoi(number) - 1;
}

void dp::dt::node::add(const std::string &key, const data &value, bool replace)
{
    unsigned long pos = key.find('.');
    if (pos != std::string::npos)
    {
        std::string name = key.substr(0, pos);
        std::string newKey = key.substr(pos + 1);
        int nb = extractPos(name);
        for (auto &child : _childs)
        {
            if (child.name() == name)
            {
                if (nb >= -1)
                    --nb;
                if (nb < 0)
                {
                    child.add(newKey, value);
                    return;
                }
            }
        }
        if (nb > 0)
            return;
        _childs.emplace_back(node(name));
        _childs[_childs.size() - 1].add(newKey, value);
    }
    else
    {
        std::string name = key;
        int nb = extractPos(name);
        if (replace)
        {
            for (auto &child : _childs)
            {
                if (child.name() == name)
                {
                    if (nb <= 0)
                    {
                        child._value = value;
                        return;
                    }
                    --nb;
                }
                if (nb == 0)
                    return;
            }
        }
        _childs.emplace_back(node(name, value));
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

bool dp::dt::node::find(const std::string &key) const
{
    return get(key) != dt::node::null;
}

const dp::dt::node &dp::dt::node::get(const std::string &key) const
{
    unsigned long pos = key.find('.');
    if (pos != std::string::npos)
    {
        std::string name = key.substr(0, pos);
        std::string newKey = key.substr(pos + 1);
        int nb = extractPos(name);
        for (auto &child : _childs)
        {
            if (child.name() == name)
            {
                if (nb >= -2)
                    --nb;
                if (nb < 0)
                {
                    auto &ret = child.get(newKey);
                    if (ret != dt::node::null)
                        return ret;
                    else if (nb == -1)
                        return dt::node::null;
                }
            }
        }
        return dt::node::null;
    }
    else
    {
        std::string name = key;
        int nb = extractPos(name);
        for (auto &child : _childs)
        {
            if (child.name() == name)
            {
                if (nb >= -2)
                    --nb;
                if (nb < 0)
                    return child;
                if (nb == -1)
                    return dt::node::null;
            }
        }
        return dt::node::null;
    }
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

bool dp::dt::node::operator==(const dp::dt::node &other) const
{
    if (_null && other._null)
        return true;
    return _name == other._name &&
           _null == other._null &&
           _value == other._value &&
           _childs == other._childs;
}

bool dp::dt::node::operator!=(const dp::dt::node &other) const
{
    return !(other == *this);
}

void dp::dt::node::name(const std::string &name)
{
    _name = name;
}
