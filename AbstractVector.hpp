#ifndef __ABSTRACT_VECTOR_HPP
#define __ABSTRACT_VECTOR_HPP

#include <cstddef>

template <typename T>
class AbstractVector
{
public:
	AbstractVector(size_t N) : _LENGTH(N)
	{}

	// getters and setters
	virtual T& operator[](size_t) = 0;
	virtual T const & operator[](size_t) const = 0;
	virtual size_t len() const { return _LENGTH; }

protected:
	size_t _LENGTH;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const AbstractVector<T>& vec)
{
	os << "[";
	for (size_t i = 0; i < vec.len(); ++i)
	{
		if (i > 0)
		{
			os << ", ";
		}
		os << vec[i];
	}
    os << "]" << std::endl;
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, AbstractVector<T>& vec)
{
	for (size_t i = 0; i < vec.len(); ++i)
	{
		is >> vec[i];
	}
	return is;
}

#endif // __ABSTRACT_VECTOR_HPP