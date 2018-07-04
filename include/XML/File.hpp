#ifndef GALAXY_XMLFILE_HPP
#define GALAXY_XMLFILE_HPP

#include <fstream>
#include "XML/Markup.hpp"

namespace dp::XML
{
    class File final : public Markup::InnerMarkup
    {
    private:
        std::unordered_map<std::string, std::unordered_map<std::string, dt::data>> xmlAttributes;
        std::unordered_map<std::string, std::unordered_map<std::string, dt::data>> documentAttributes;

    private:
        const std::string load(const std::string &) const;
        bool treatXmlAttributes(const std::string &);
        void treatXmlInformation(const std::string &, std::string &);
        void treatAutoCloseMarkup(std::string &);
        bool treatInfo(std::string &);
        bool treatContent(std::string &) override;
        std::string treatCommentary(std::string &) const;

    public:
        File();
        File(const std::string &);
        File(const File &) = default;
        File &operator=(const File &);
        void addAttributes(const std::string &, const std::string &, const std::string &);
        void addDefaultHeader();
        void addDocAttributes(const std::string &, const std::string &, const std::string &);
        void removeDocAttributes(const std::string &);
        void removeDocAttributes();
        void clear() override;
        const std::string toString() const;
        ~File() override = default;
    };
}

std::ostream &operator<<(std::ostream &, const dp::XML::File &);

#endif