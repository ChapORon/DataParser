#include "dp/dt/node.hpp"

const dp::dt::node dp::dt::node::null = dp::dt::node(true);

dp::dt::node::node() : _null(false) {}

dp::dt::node::node(bool null) : _null(null) {}

dp::dt::node::node(const char *name) : _null(false), _name(name) {}

dp::dt::node::node(const std::string &name) : _null(false), _name(name) {}

dp::dt::node::node(const char *name, const data &value) : _null(false), _name(name), _value(value) {}

dp::dt::node::node(const std::string &name, const data &value) : _null(false), _name(name), _value(value) {}

dp::dt::node &dp::dt::node::operator=(const node &other)
{
    _null = other._null;
    _value = other._value;
    _childs = other._childs;
    return *this;
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
    std::string name = key;
    unsigned long pos = name.find('.');
    if (pos == std::string::npos)
        add(key, node(key, value), replace);
    else
    {
        while (pos != std::string::npos)
        {
            name = name.substr(pos + 1);
            pos = name.find('.');
        }
        add(key, node(name, value), replace);
    }
}

void dp::dt::node::add(const std::string &key, const node &value, bool replace)
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
                        child._value = value._value;
                        return;
                    }
                    --nb;
                }
                if (nb == 0)
                    return;
            }
        }
        _childs.emplace_back(value);
    }
}

void dp::dt::node::add(const dp::dt::node &node, bool replace)
{
    if (node == null)
        return;
    if (replace)
    {
        for (auto &child : _childs)
        {
            if (child.name() == node.name())
            {
                child._value = node._value;
                return;
            }
        }
    }
    _childs.emplace_back(node);
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

bool dp::dt::node::remove(const std::string &key)
{
    unsigned long pos = key.find('.');
    unsigned int nodeToRemove = 0;
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
                    bool ret = child.remove(newKey);
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
        int nb = extractPos(name);
        for (auto &child : _childs)
        {
            if (child.name() == name)
            {
                if (nb >= -2)
                    --nb;
                if (nb < 0)
                {
                    _childs.erase(_childs.begin() + nodeToRemove);
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

void dp::dt::node::value(const dp::dt::data &value)
{
    _value = value;
}

bool dp::dt::node::haveValue() const
{
    return _value.empty();
}

template <> bool dp::dt::node::get<bool>() const {return _value.getBool();}
template <> char dp::dt::node::get<char>() const {return _value.getChar();}
template <> int dp::dt::node::get<int>() const {return _value.getInt();}
template <> float dp::dt::node::get<float>() const {return _value.getFloat();}
template <> double dp::dt::node::get<double>() const {return _value.getDouble();}
template <> long dp::dt::node::get<long>() const {return _value.getLong();}
template <> std::string dp::dt::node::get<std::string>() const {return _value.getString();}
template <> const std::string &dp::dt::node::get<const std::string &>() const {return _value.getCString();}

bool dp::dt::node::empty() const
{
    return _value.empty() && _childs.empty();
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

bool dp::dt::node::isNull() const
{
    return _null;
}
