#include "dt/node.hpp"

dp::dt::node::node() {}

dp::dt::node::node(const data &value) : _value(value) {}

dp::dt::node &dp::dt::node::operator=(const node &other)
{
    _value = other._value;
    _childs = other._childs;
    return *this;
}

void dp::dt::node::add(const std::string &key, const data &value)
{
    std::vector<std::string> tokens;
    std::string buf;
    std::stringstream tokenStream(key);
    while (std::getline(tokenStream, buf, '.'))
        tokens.push_back(buf);
    node tmp = *this;
    for (auto &token : tokens)
    {

    }
    _childs.emplace_back(std::pair(key, value));
}

dp::dt::data dp::dt::node::value() const
{
    return _value;
}

const std::vector<std::pair<std::string, dp::dt::node>> &dp::dt::node::childs() const
{
    return _childs;
}

dp::dt::node &dp::dt::node::get(const std::string &path)
{
    std::vector<std::string> tokens;
    std::string buf;
    std::stringstream tokenStream(path);
    while (std::getline(tokenStream, buf, '.'))
        tokens.push_back(buf);
    node ret = *this;
    for (auto &token : tokens)
    {

    }
    return ret;
}
