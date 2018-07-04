#include "XML/Markup.hpp"

dp::XML::Markup::Markup(const std::string &name) :
        innerMarkup(std::make_shared<InnerMarkup>(name)) {}

dp::XML::Markup::Markup(const std::string &name, std::string &content) :
        innerMarkup(std::make_shared<InnerMarkup>(name, content)) {}

dp::XML::Markup::Markup(const std::string &name, const std::string &attributes, std::string &content) :
        innerMarkup(std::make_shared<InnerMarkup>(name, attributes, content)) {}

dp::XML::Markup &dp::XML::Markup::operator=(const dp::XML::Markup &other)
{
    innerMarkup = other.innerMarkup;
    return *this;
}

const std::vector<dp::XML::Markup> &dp::XML::Markup::getMarkups() const
{
    return innerMarkup->getMarkups();
}

size_t dp::XML::Markup::size() const
{
    return innerMarkup->size();
}

const std::string &dp::XML::Markup::getName() const
{
    return innerMarkup->getName();
}

void dp::XML::Markup::setName(const std::string &name)
{
    innerMarkup->setName(name);
}

const std::vector<std::string> dp::XML::Markup::getAttributes() const
{
    return innerMarkup->getAttributes();
}

const dp::dt::data dp::XML::Markup::getAttribute(const std::string &name) const
{
    return innerMarkup->getAttribute(name);
}

const std::vector<std::string> &dp::XML::Markup::getContents() const
{
    return innerMarkup->getContents();
}

void dp::XML::Markup::addAttributes(const std::string &name, const dp::dt::data &attr)
{
    innerMarkup->addAttributes(name, attr);
}

void dp::XML::Markup::addContents(const std::string &content)
{
    innerMarkup->addContents(content);
}

void dp::XML::Markup::setContents(const std::vector<std::string> &content)
{
    innerMarkup->setContents(content);
}

void dp::XML::Markup::addMarkups(const dp::XML::Markup &tag)
{
    innerMarkup->addMarkups(tag);
}

void dp::XML::Markup::clear()
{
    innerMarkup->clear();
}

void dp::XML::Markup::removeAttributes()
{
    innerMarkup->removeAttributes();
}

void dp::XML::Markup::removeContents()
{
    innerMarkup->removeContents();
}

void dp::XML::Markup::removeMarkups()
{
    innerMarkup->removeMarkups();
}

void dp::XML::Markup::removeAttributes(const std::string &name)
{
    innerMarkup->removeAttributes(name);
}

void dp::XML::Markup::removeContents(const std::string &name)
{
    innerMarkup->removeContents(name);
}

void dp::XML::Markup::removeMarkups(const std::string &name)
{
    innerMarkup->removeMarkups(name);
}

const std::vector<dp::XML::Markup> dp::XML::Markup::operator[](const std::string &name) const
{
    return (*innerMarkup)[name];
}

const dp::XML::Markup &dp::XML::Markup::operator[](size_t pos) const
{
    return (*innerMarkup)[pos];
}

const std::string dp::XML::Markup::toString(size_t indent) const
{
    return innerMarkup->toString(indent);
}

dp::XML::Markup::iterator dp::XML::Markup::begin()
{
    return innerMarkup->begin();
}

dp::XML::Markup::const_iterator dp::XML::Markup::begin() const
{
    return innerMarkup->begin();
}

dp::XML::Markup::iterator dp::XML::Markup::end()
{
    return innerMarkup->end();
}

dp::XML::Markup::const_iterator dp::XML::Markup::end() const
{
    return innerMarkup->end();
}

bool dp::XML::Markup::operator==(const std::string &name) const
{
    return (*innerMarkup) == name;
}

bool dp::XML::Markup::operator!=(const std::string &name) const
{
    return (*innerMarkup) != name;
}

std::ostream &operator<<(std::ostream &os, const dp::XML::Markup &tag)
{
    os << tag.toString(0);
    return os;
}