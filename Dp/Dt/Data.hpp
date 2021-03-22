#ifndef DATAPARSER_DATATREE_DATA_HPP
#define DATAPARSER_DATATREE_DATA_HPP

#include <ostream>
#include <string>

namespace Dp
{
    namespace Dt
    {
        class Data final
        {
        private:
            bool m_IsEmpty;
            std::string m_Attribute;

        public:
            Data();
            Data(const char *);
            Data(const std::string &);
            Data(bool);
            Data(char);
            Data(int);
            Data(float);
            Data(double);
            Data(long);
            Data(const Data &) = default;
            Data &operator=(char);
            Data &operator=(int);
            Data &operator=(float);
            Data &operator=(double);
            Data &operator=(long);
            Data &operator=(const std::string &);
            Data &operator=(const Data &) = default;
            bool operator==(const Data &) const;
            bool operator!=(const Data &) const;
            explicit operator std::string() const
            {
                return m_Attribute;
            }
            explicit operator bool() const
            {
                return GetBool();
            }
            explicit operator char()
            {
                return GetChar();
            }
            explicit operator int()
            {
                return GetInt();
            }
            explicit operator float()
            {
                return GetFloat();
            }
            explicit operator double()
            {
                return GetDouble();
            }
            explicit operator long()
            {
                return GetLong();
            }
            bool IsEmpty() const;
            bool GetBool() const;
            char GetChar() const;
            int GetInt() const;
            float GetFloat() const;
            double GetDouble() const;
            long GetLong() const;
            std::string GetString() const;
            const std::string &GetCString() const;
            ~Data() = default;
        };
    }
}

std::ostream &operator<<(std::ostream &, const Dp::Dt::Data &);

#endif //DATAPARSER_DATATREE_DATA_HPP
