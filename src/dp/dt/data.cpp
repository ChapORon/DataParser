#include "dp/dt/data.hpp"

dp::dt::data::data() : isEmpty(true) {}

dp::dt::data::data(const char *attributes) : isEmpty(attributes[0] == '\0'), attributes(attributes) {}

dp::dt::data::data(const std::string &attributes) : isEmpty(attributes.empty()), attributes(attributes) {}

dp::dt::data::data(bool attribute) : isEmpty(false), attributes((attribute) ? "true" : "false") {}

dp::dt::data::data(char attribute) : isEmpty(false), attributes(1, attribute) {}

dp::dt::data::data(int attribute) : isEmpty(false), attributes(std::to_string(attribute)) {}

dp::dt::data::data(float attribute) : isEmpty(false), attributes(std::to_string(attribute)) {}

dp::dt::data::data(double attribute) : isEmpty(false), attributes(std::to_string(attribute)) {}

dp::dt::data::data(long attribute) : isEmpty(false), attributes(std::to_string(attribute)) {}

dp::dt::data &dp::dt::data::operator=(char attribute)
{
    this->attributes.clear();
    this->attributes += attribute;
    isEmpty = false;
    return *this;
}

dp::dt::data &dp::dt::data::operator=(int attribute)
{
    this->attributes = std::to_string(attribute);
    isEmpty = false;
    return *this;
}

dp::dt::data &dp::dt::data::operator=(float attribute)
{
    this->attributes = std::to_string(attribute);
    isEmpty = false;
    return *this;
}

dp::dt::data &dp::dt::data::operator=(double attribute)
{
    this->attributes = std::to_string(attribute);
    isEmpty = false;
    return *this;
}

dp::dt::data &dp::dt::data::operator=(long attribute)
{
    this->attributes = std::to_string(attribute);
    isEmpty = false;
    return *this;
}

dp::dt::data &dp::dt::data::operator=(const std::string &attributes)
{
    this->attributes = attributes;
    isEmpty = attributes.empty();
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

char dp::dt::data::getChar() const
{
    return attributes[0];
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

std::string dp::dt::data::getString() const
{
    return attributes;
}

const std::string &dp::dt::data::getCString() const
{
    return attributes;
}

bool dp::dt::data::operator==(const dp::dt::data &other) const
{
    return isEmpty == other.isEmpty && attributes == other.attributes;
}

bool dp::dt::data::operator!=(const dp::dt::data &other) const
{
    return !(other == *this);
}

std::ostream &operator<<(std::ostream &os, const dp::dt::data &data)
{
    os << data.getString();
    return os;
}
