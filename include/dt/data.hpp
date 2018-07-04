#ifndef GALAXY_XML_ATTRIBUTES_HPP
#define GALAXY_XML_ATTRIBUTES_HPP

#include <string>

namespace dp::dt
{
    class data final
    {
    private:
        bool isEmpty;
        std::string attributes;

    public:
        data();
        data(const std::string &);
        data(const data &);
        data &operator=(const std::string &);
        data &operator=(const data &);
        operator std::string() const
        {
            return attributes;
        }
        operator bool() const
        {
            return !isEmpty;
        }
        bool empty() const;
        bool getBool() const;
        int getInt() const;
        float getFloat() const;
        double getDouble() const;
        long getLong() const;
        const std::string &getString() const;
        ~data() = default;
    };
}

#endif
