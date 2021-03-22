#include "Dp/Dt/Data.hpp"

namespace Dp
{
	namespace Dt
	{
		Data::Data() : m_IsEmpty(true) {}

		Data::Data(const char *attributes) : m_IsEmpty(attributes[0] == '\0'), m_Attribute(attributes) {}

		Data::Data(const std::string &attributes) : m_IsEmpty(attributes.empty()), m_Attribute(attributes) {}

		Data::Data(bool attribute) : m_IsEmpty(false), m_Attribute((attribute) ? "true" : "false") {}

		Data::Data(char attribute) : m_IsEmpty(false), m_Attribute(1, attribute) {}

		Data::Data(int attribute) : m_IsEmpty(false), m_Attribute(std::to_string(attribute)) {}

		Data::Data(float attribute) : m_IsEmpty(false), m_Attribute(std::to_string(attribute)) {}

		Data::Data(double attribute) : m_IsEmpty(false), m_Attribute(std::to_string(attribute)) {}

		Data::Data(long attribute) : m_IsEmpty(false), m_Attribute(std::to_string(attribute)) {}

		Data &Data::operator=(char attribute)
		{
			this->m_Attribute.clear();
			this->m_Attribute += attribute;
			m_IsEmpty = false;
			return *this;
		}

		Data &Data::operator=(int attribute)
		{
			this->m_Attribute = std::to_string(attribute);
			m_IsEmpty = false;
			return *this;
		}

		Data &Data::operator=(float attribute)
		{
			this->m_Attribute = std::to_string(attribute);
			m_IsEmpty = false;
			return *this;
		}

		Data &Data::operator=(double attribute)
		{
			this->m_Attribute = std::to_string(attribute);
			m_IsEmpty = false;
			return *this;
		}

		Data &Data::operator=(long attribute)
		{
			this->m_Attribute = std::to_string(attribute);
			m_IsEmpty = false;
			return *this;
		}

		Data &Data::operator=(const std::string &attributes)
		{
			this->m_Attribute = attributes;
			m_IsEmpty = attributes.empty();
			return *this;
		}

		bool Data::IsEmpty() const
		{
			return m_IsEmpty;
		}

		bool Data::GetBool() const
		{
			return (m_Attribute == "true");
		}

		char Data::GetChar() const
		{
			return m_Attribute[0];
		}

		int Data::GetInt() const
		{
			return std::stoi(m_Attribute);
		}

		float Data::GetFloat() const
		{
			return std::stof(m_Attribute);
		}

		double Data::GetDouble() const
		{
			return std::stod(m_Attribute);
		}

		long Data::GetLong() const
		{
			return std::stol(m_Attribute);
		}

		std::string Data::GetString() const
		{
			return m_Attribute;
		}

		const std::string &Data::GetCString() const
		{
			return m_Attribute;
		}

		bool Data::operator==(const Data &other) const
		{
			return m_IsEmpty == other.m_IsEmpty && m_Attribute == other.m_Attribute;
		}

		bool Data::operator!=(const Data &other) const
		{
			return !(other == *this);
		}
	}
}

std::ostream &operator<<(std::ostream &os, const Dp::Dt::Data &data)
{
    os << data.GetString();
    return os;
}
