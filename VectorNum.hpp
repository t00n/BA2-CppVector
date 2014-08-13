#ifndef __VECTOR_NUM_HPP
#define __VECTOR_NUM_HPP

#include <type_traits>
#include "Vector.hpp"

template <typename T, bool POINTER>
class VectorNum : public VectorImpl<T, POINTER>
{
public:
	using VectorImpl<T, POINTER>::VectorImpl;
	virtual VectorImpl<T, POINTER> operator+(const VectorImpl<T, POINTER>& other) = 0;

	virtual VectorImpl<T, POINTER> operator-(const VectorImpl<T, POINTER>& other) = 0;

	virtual VectorImpl<T, POINTER> operator+() = 0;

	virtual VectorImpl<T, POINTER> operator-() = 0;

	virtual VectorImpl<T, POINTER> operator*(T scalar) = 0;

	virtual T operator*(const VectorImpl<T, POINTER>& other) = 0;
};

template <typename T, bool POINTER>
class Vector<T, POINTER, typename std::enable_if<std::is_arithmetic<T>::value>::type>
 : public VectorNum<T, POINTER>
{
public:
	using VectorNum<T, POINTER>::VectorNum;
	VectorImpl<T, POINTER> operator+(const VectorImpl<T, POINTER>& other)
	{
		VectorImpl<T, POINTER> ret(*this);
		if (other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				ret[i] += other[i];
			}
		}
		return ret;
	}
	VectorImpl<T, POINTER> operator-(const VectorImpl<T, POINTER>& other)
	{
		VectorImpl<T, POINTER> ret(*this);
		if (other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				ret[i] -= other[i];
			}
		}
		return ret;		
	}
	VectorImpl<T, POINTER> operator+()
	{
		VectorImpl<T, POINTER> ret(this->len());
		for (size_t i = 0; i < this->len(); ++i)
		{
			ret[i] = +(*this)[i];
		}
		return ret;
	}
	VectorImpl<T, POINTER> operator-()
	{
		VectorImpl<T, POINTER> ret(this->len());
		for (size_t i = 0; i < this->len(); ++i)
		{
			ret[i] = -(*this)[i];
		}
		return ret;
	}
	VectorImpl<T, POINTER> operator*(T scalar)
	{
		VectorImpl<T, POINTER> ret(*this);
		for (size_t i = 0; i < this->len(); ++i)
		{
			ret[i] *= scalar;
		}
		return ret;
	}
	T operator*(const VectorImpl<T, POINTER>& other)
	{
		// ????
	}
};

template <typename T, bool POINTER>
class Vector<T*, POINTER, typename std::enable_if<std::is_arithmetic<T>::value>::type>
 : public VectorNum<T*, POINTER>
{
public:
	using VectorNum<T*, POINTER>::VectorNum;
	VectorImpl<T*, POINTER> operator+(const VectorImpl<T*, POINTER>& other)
	{
		VectorImpl<T*, POINTER> ret(*this);
		if (other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				if (ret[i] == nullptr)
					ret[i] = new T();
				if (other[i] != nullptr)
					*(ret[i]) += *(other[i]);
			}
		}
		return ret;
	}
	VectorImpl<T*, POINTER> operator-(const VectorImpl<T*, POINTER>& other)
	{
		VectorImpl<T*, POINTER> ret(*this);
		if (other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				if (ret[i] == nullptr)
					ret[i] = new T();
				if (other[i] != nullptr)
					*(ret[i]) -= *(other[i]);
			}
		}
		return ret;		
	}
	VectorImpl<T*, POINTER> operator+()
	{
		VectorImpl<T*, POINTER> ret(this->len());
		for (size_t i = 0; i < this->len(); ++i)
		{
			if ((*this)[i] != nullptr)
			{
				ret[i] = new T(+(*((*this)[i])));
			}
		}
		return ret;
	}
	VectorImpl<T*, POINTER> operator-()
	{
		VectorImpl<T*, POINTER> ret(*this);
		for (size_t i = 0; i < this->len(); ++i)
		{
			if ((*this)[i] != nullptr)
			{
				ret[i] = new T(-(*((*this)[i])));
			}
		}
		return ret;
	}
	VectorImpl<T*, POINTER> operator*(T* scalar)
	{
		VectorImpl<T*, POINTER> ret(*this);
		for (size_t i = 0; i < this->len(); ++i)
		{
			if (ret[i] != nullptr)
				*(ret[i]) *= *(scalar);
		}
		return ret;
	}

	T* operator*(const VectorImpl<T*, POINTER>& other)
	{
		// ????
	}
};

#endif // __VECTOR_NUM_HPP