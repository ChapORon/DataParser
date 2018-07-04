#include "dt/data.hpp"

dp::dt::data::data() : isEmpty(true) {}

dp::dt::data::data(const std::string &attributes) : isEmpty(attributes.empty()), attributes(attributes) {}

dp::dt::data::data(const data &other) : isEmpty(other.attributes.empty()), attributes(other.attributes) {}

dp::dt::data &dp::dt::data::operator=(const std::string &attributes)
{
    this->attributes = attributes;
    isEmpty = attributes.empty();
    return *this;
}

dp::dt::data &dp::dt::data::operator=(const data &other)
{
    attributes = other.attributes;
    isEmpty = other.isEmpty;
    return *this;
}

bool dp::dt::data::empty() const
{
    return isEmpty;
}

bool dp::dt::data::getBool() const
{
    return (attributes == "true");
}

int dp::dt::data::getInt() const
{
    return std::stoi(attributes);
}

float dp::dt::data::getFloat() const
{
    return std::stof(attributes);
}

double dp::dt::data::getDouble() const
{
    return std::stod(attributes);
}

long dp::dt::data::getLong() const
{
    return std::stol(attributes);
}

const std::string &dp::dt::data::getString() const
{
    return attributes;
}

std::ostream &operator<<(std::ostream &os, const dp::dt::data &attribute)
{
    os << attribute.getString();
    return os;
}