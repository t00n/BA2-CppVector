#ifndef __ABSTRACT_VECTOR_HPP
#define __ABSTRACT_VECTOR_HPP

#include <cstddef>

template <typename T>
class AbstractVector
{
public:
	AbstractVector() : _values() {}
	AbstractVector(const AbstractVector<T>& other) : _values() {}
	AbstractVector& operator=(const AbstractVector<T>& other) {}
	virtual ~AbstractVector()
	{}

	template<T>
	friend std::ostream& operator<<(std::ostream& os, AbstractVector<T>& vec);

	template<T>
	friend std::istream& operator>>(std::istream& is, AbstractVector<T>& vec);

	virtual T& operator[](size_t) = 0;
	virtual size_t len() const = 0;

protected:
	T _values[10];
};

template <typename T>
std::ostream& operator<<(std::ostream& os, AbstractVector<T>& vec)
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

template <typename T>
class AbstractValueVector : public AbstractVector<T>
{
public:
	virtual T& operator[](size_t index)
	{
		return this->_values[index];
	}

	virtual size_t len() const
	{
		return sizeof(this->_values)/sizeof(T);
	}
};

template <typename T>
class AbstractPointerVector : public AbstractVector<T>
{
public:
	virtual T& operator[](size_t index)
	{
		return *(this->_values[index]);
	}

	virtual size_t len() const
	{
		return sizeof(this->_values)/sizeof(*(this->_values));
	}
};

#endif // __ABSTRACT_VECTOR_HPP