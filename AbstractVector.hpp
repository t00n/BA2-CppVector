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
	virtual size_t len() { return _LENGTH; }

protected:
	const size_t _LENGTH;
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
	AbstractValueVector(size_t N) : AbstractVector<T>(N), _values(new T[N])
	{}

	~AbstractValueVector()
	{
		delete[] this->_values;
	}

	virtual T& operator[](size_t index)
	{
		return this->_values[index];
	}

protected:
	T* _values;
};

template <typename T>
class AbstractPointerVector : public AbstractVector<T>
{
public:
	AbstractPointerVector(size_t N) : AbstractVector<T>(N), _values(new T*[N])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_values[i] = new T();
		}
	}

	~AbstractPointerVector()
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			delete this->_values[i];
		}
		delete[] this->_values;
	}

	virtual T& operator[](size_t index)
	{
		return *(this->_values[index]);
	}
	
protected:
	T** _values;
};

#endif // __ABSTRACT_VECTOR_HPP