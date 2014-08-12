#ifndef __STRING_HPP
#define __STRING_HPP

#include <string>
#include <cstring>
#include "Vector.hpp"

template <typename T, bool POINTER>
class VectorString : public VectorImpl<T, POINTER>
{
public:
	using VectorImpl<T, POINTER>::VectorImpl;

	operator std::string() const
	{
		std::string ret;
		for (size_t i = 0; i < this->len(); ++i)
		{
			appendString(ret, i);
		}
		return ret;
	}

protected:
	virtual void appendString(std::string&, size_t) const = 0;
};

template <typename T, bool POINTER>
std::ostream& operator<<(std::ostream& os, const VectorString<T, POINTER>& vec)
{
	os << static_cast<std::string>(vec);
    return os;
}

template <bool POINTER>
class Vector<char, POINTER> : public VectorString<char, POINTER>
{
public:
	using VectorString<char, POINTER>::VectorString;
protected:
	void appendString(std::string& ret, size_t index) const
	{
		ret.push_back((*this)[index]);
	}
};

template <bool POINTER>
class Vector<char*, POINTER> : public VectorString<char*, POINTER>
{
public:
	using VectorString<char*, POINTER>::VectorString;
protected:
	void appendString(std::string& ret, size_t index) const
	{
		if (this->_data[index] != nullptr)
		{
			for (size_t i = 0; i < strlen(this->_data[index]); ++i)
			{
				ret.push_back(this->_data[index][i]);
			}
		}
	}
};

template <bool POINTER>
class Vector<std::string, POINTER> : public VectorString<std::string, POINTER>
{
public:
	using VectorString<std::string, POINTER>::VectorString;
protected:
	void appendString(std::string& ret, size_t index) const
	{
		ret.append((*this)[index]);
	}
};

#endif // __STRING_HPP