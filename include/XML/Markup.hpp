#ifndef GALAXY_XML_MARKUP_HPP
#define GALAXY_XML_MARKUP_HPP

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "dt/data.hpp"

namespace dp
{
    namespace XML
    {
        class File;
        class Markup
        {
            friend class File;
        public:
            typedef Markup *iterator;
            typedef const Markup *const_iterator;

        private:
            class InnerMarkup
            {
            protected:
                std::string name;
                std::unordered_map<std::string, dt::data> attributes;
                std::vector<Markup> tags;
                std::vector<std::string> contents;
                bool created;

            protected:
                void treatMarkupContent(const std::string &);
                bool setAttributes(const std::string &);
                virtual bool treatContent(std::string &);
                bool start_with(const std::string &, const std::string &) const;
                bool end_with(const std::string &, const std::string &) const;
                void replace_all(std::string &, const std::string &, const std::string &) const;
                void trim(std::string &) const;
                size_t count(std::string &, const std::string &) const;
                std::vector<std::string> split(const std::string &, const std::string &) const;

            public:
                InnerMarkup(const std::string &);
                InnerMarkup(const std::string &, std::string &);
                InnerMarkup(const std::string &, const std::string &, std::string &);
                InnerMarkup(const InnerMarkup &) = default;
                InnerMarkup &operator=(const InnerMarkup &);
                const std::vector<Markup> &getMarkups() const;
                size_t size() const;
                const std::string &getName() const;
                void setName(const std::string &);
                const std::vector<std::string> getAttributes() const;
                const dt::data getAttribute(const std::string &) const;
                const std::vector<std::string> &getContents() const;
                void addAttributes(const std::string &, const dt::data &);
                void addContents(const std::string &);
                void setContents(const std::vector<std::string> &);
                void addMarkups(const Markup &);
                virtual void clear();
                void removeAttributes();
                void removeContents();
                void removeMarkups();
                void removeAttributes(const std::string &);
                void removeContents(const std::string &);
                void removeMarkups(const std::string &);
                const std::vector<Markup> operator[](const std::string &) const;
                const Markup &operator[](size_t) const;
                const std::string toString(size_t) const;
                Markup::iterator begin();
                Markup::const_iterator begin() const;
                Markup::iterator end();
                Markup::const_iterator end() const;
                bool operator==(const std::string &) const;
                bool operator!=(const std::string &) const;
                virtual ~InnerMarkup() = default;
                operator bool() const
                {
                    return created;
                }
            };

        private:
            std::shared_ptr<InnerMarkup> innerMarkup;

        public:
            Markup(const std::string &);
            Markup(const std::string &, std::string &);
            Markup(const std::string &, const std::string &, std::string &);
            Markup(const Markup &) = default;
            Markup &operator=(const Markup &);
            const std::vector<Markup> &getMarkups() const;
            size_t size() const;
            const std::string &getName() const;
            void setName(const std::string &);
            const std::vector<std::string> getAttributes() const;
            const dt::data getAttribute(const std::string &) const;
            const std::vector<std::string> &getContents() const;
            void addAttributes(const std::string &, const dt::data &);
            void addContents(const std::string &);
            void setContents(const std::vector<std::string> &);
            void addMarkups(const Markup &);
            virtual void clear();
            void removeAttributes();
            void removeContents();
            void removeMarkups();
            void removeAttributes(const std::string &);
            void removeContents(const std::string &);
            void removeMarkups(const std::string &);
            const std::vector<Markup> operator[](const std::string &) const;
            const Markup &operator[](size_t) const;
            const std::string toString(size_t) const;
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;
            bool operator==(const std::string &) const;
            bool operator!=(const std::string &) const;
            virtual ~Markup() = default;
            operator bool() const
            {
                return *innerMarkup;
            }
        };
    }
}
std::ostream &operator<<(std::ostream &, const dp::XML::Markup &);

#endif