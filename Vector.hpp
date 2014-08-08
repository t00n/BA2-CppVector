#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include "AbstractVector.hpp"
#include "DataVector.hpp"

template <typename T, bool pointer>
class Vector
{};

template <typename T>
class Vector<T, false> : public AbstractVector<T>
{
public:
	Vector(size_t len) : AbstractVector<T>(len), _data(len)
	{}

	Vector(const AbstractVector<T>& other) : AbstractVector<T>(other.len()), _data(other.len())
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = other[i];
		}
	}

	T& operator[](size_t index)
	{
		return this->_data[index];
	}

	const T& operator[](size_t index) const
	{
		return this->_data[index];
	}

protected:
	DataVector<T> _data;

};

template <typename T>
class Vector<T, true> : public AbstractVector<T>
{
public:
	Vector(size_t len) : AbstractVector<T>(len), _data(len)
	{
		for (size_t i = 0; i < len; ++i)
		{
			this->_data[i] = new T();;
		}
	}

	~Vector()
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			delete this->_data[i];
		}
	}

	T& operator[](size_t index)
	{
		return *(this->_data[index]);
	}

	const T& operator[](size_t index) const
	{
		return *(this->_data[index]);
	}

protected:
	DataVector<T*> _data;
};

template <typename T>
class Vector<T*, false>
{
public:

};

template <typename T>
class Vector<T*, true>
{
public:

};

#endif // __VECTOR_HPP