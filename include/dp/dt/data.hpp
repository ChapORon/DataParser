#ifndef DATAPARSER_DATATREE_DATA_HPP
#define DATAPARSER_DATATREE_DATA_HPP

#include <ostream>
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
        data(const char *);
        data(const std::string &);
        data(bool);
        data(char);
        data(int);
        data(float);
        data(double);
        data(long);
        data(const data &) = default;
        data &operator=(char);
        data &operator=(int);
        data &operator=(float);
        data &operator=(double);
        data &operator=(long);
        data &operator=(const std::string &);
        data &operator=(const data &) = default;
        bool operator==(const data &rhs) const;
        bool operator!=(const data &rhs) const;
        explicit operator std::string() const
        {
            return attributes;
        }
        explicit operator bool() const
        {
            return getBool();
        }
        explicit operator char()
        {
            return getChar();
        }
        explicit operator int()
        {
            return getInt();
        }
        explicit operator float()
        {
            return getFloat();
        }
        explicit operator double()
        {
            return getDouble();
        }
        explicit operator long()
        {
            return getLong();
        }
        bool empty() const;
        bool getBool() const;
        char getChar() const;
        int getInt() const;
        float getFloat() const;
        double getDouble() const;
        long getLong() const;
        std::string getString() const;
        const std::string &getCString() const;
        ~data() = default;
    };
}

std::ostream &operator<<(std::ostream &, const dp::dt::data &);

#endif //DATAPARSER_DATATREE_DATA_HPP
