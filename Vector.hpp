#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include "AbstractVector.hpp"

template <typename T, bool pointer>
class Vector
{};

template <typename T>
class Vector<T, false> : public AbstractVector<T>
{
public:
	Vector(size_t len) : AbstractVector<T>(len), _data(new T[len])
	{}

	template <typename U>
	Vector(const AbstractVector<U>& other) : AbstractVector<T>(other.len()), _data(new T[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = other[i];
		}
	}

	template <typename U>
	Vector(const AbstractVector<U*>& other) : AbstractVector<T>(other.len()), _data(new T[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = *(other[i]);
		}
	}

	~Vector()
	{
		delete[] _data;
	}

	Vector& operator=(const AbstractVector<T>& other)
	{
		if (&other != this and other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				this->_data[i] = other[i];
			}
		}
		return *this;
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
	T* _data;

};

template <typename T>
class Vector<T, true> : public AbstractVector<T>
{
public:
	Vector(size_t len) : AbstractVector<T>(len), _data(new T*[len])
	{
		for (size_t i = 0; i < len; ++i)
		{
			this->_data[i] = new T();;
		}
	}

	template <typename U>
	Vector(const AbstractVector<U>& other) : AbstractVector<T>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(other[i]);
		}
	}

	template <typename U>
	Vector(const AbstractVector<U*>& other) : AbstractVector<T>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(*(other[i]));
		}
	}

	Vector& operator=(const AbstractVector<T>& other)
	{
		if (&other != this and other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				this->_data[i] = new T(other[i]);
			}
		}
		return *this;
	}

	~Vector()
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			delete this->_data[i];
		}
		delete[] _data;
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
	T** _data;
};

template <typename T>
class Vector<T*, false> : public AbstractVector<T*>
{
public:
	Vector(size_t len) : AbstractVector<T*>(len), _data(new T*[len])
	{
		for (size_t i = 0; i < len; ++i)
		{
			this->_data[i] = new T();;
		}
	}

	Vector(const AbstractVector<T>& other) : AbstractVector<T*>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(other[i]);
		}
	}

	Vector& operator=(const AbstractVector<T>& other)
	{
		if (&other != this and other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				this->_data[i] = new T(other[i]);
			}
		}
		return *this;
	}

	~Vector()
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			delete this->_data[i];
		}
		delete[] _data;
	}

	T*& operator[](size_t index)
	{
		return this->_data[index];
	}

	T* const & operator[](size_t index) const
	{
		return this->_data[index];
	}
protected:
	T** _data;
};

template <typename T>
class Vector<T*, true> : public Vector<T*, false>
{
public:
	using Vector<T*, false>::Vector;
};

#endif // __VECTOR_HPP