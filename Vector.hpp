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
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = T();
		}
	}

	// Constructor from Vector<T, ...> where T is any equivalent/convertible type
	template <typename U>
	Vector(const AbstractVector<U>& other) : AbstractVector<T>(other.len()), _data(new T[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = other[i];
		}
	}

	// Constructor from Vector<T*, ...> where T is any equivalent/convertible type
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

	// WRONG operator =
	// operator= from Vector<T, ...> where 'other' might be a conversion from an equivalent type
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

	virtual void print(std::ostream& os, size_t index) const
	{
		os << this->_data[index];
	}

	virtual void scan(std::istream& is, size_t index)
	{
		is >> this->_data[index];
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

	Vector(const Vector<T, true>& other) : AbstractVector<T>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(other[i]);
		}
	}

	// Constructor from Vector<T, ...>
	template <typename U>
	Vector(const AbstractVector<U>& other) : AbstractVector<T>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(other[i]);
		}
	}

	// Constructor from Vector<T*, ...>
	template <typename U>
	Vector(const AbstractVector<U*>& other) : AbstractVector<T>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(*(other[i]));
		}
	}

	// WRONG operator =	
	Vector& operator=(const AbstractVector<T>& other)
	{
		if (&other != this and other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				*(this->_data[i]) = other[i];
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

	virtual void print(std::ostream& os, size_t index) const
	{
		os << *(this->_data[index]);
	}

	virtual void scan(std::istream& is, size_t index)
	{
		is >> *(this->_data[index]);
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

	Vector(const Vector<T*, false>& other) : AbstractVector<T*>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(*(other[i]));
		}
	}

	// Constructor from Vector<T, ...>
	template <typename U>
	Vector(const AbstractVector<U>& other) : AbstractVector<T*>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(other[i]);
		}
	}

	// Constructor from Vector<T*, ...>
	template <typename U>
	Vector(const AbstractVector<U*>& other) : AbstractVector<T*>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(*(other[i]));
		}
	}

	// WRONG operator = 
	Vector& operator=(const AbstractVector<T*>& other)
	{
		if (&other != this and other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				*(this->_data[i]) = *(other[i]);
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

	virtual void print(std::ostream& os, size_t index) const
	{
		os << *(this->_data[index]);
	}

	virtual void scan(std::istream& is, size_t index)
	{
		is >> *(this->_data[index]);
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

template <typename T, bool POINTER, size_t N>
class VectorStatic : public Vector<T, POINTER>
{
public:
	using Vector<T, POINTER>::Vector;
	VectorStatic() : Vector<T, POINTER>(N)
	{}

};

#endif // __VECTOR_HPP