/*
 * Antoine Carpentier
 * 000324440
 * BA2 informatique ULB 2013-2014
 * Langages de programmation 2 - INFO-F-202
 * Project C++
 */

#ifndef __VECTOR_NUM_HPP
#define __VECTOR_NUM_HPP

#include <type_traits>
#include <cmath>
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

	virtual VectorImpl<T, POINTER> operator*(double scalar) = 0;

	virtual double operator*(const VectorImpl<T, POINTER>& other) = 0;

	virtual double norm()
	{
		double ret = (*this) * (*this);
		return sqrt(ret);
	}
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
	VectorImpl<T, POINTER> operator*(double scalar)
	{
		VectorImpl<T, POINTER> ret(*this);
		for (size_t i = 0; i < this->len(); ++i)
		{
			ret[i] *= scalar;
		}
		return ret;
	}
	double operator*(const VectorImpl<T, POINTER>& other)
	{
		double ret = 0;
		if (other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				ret += other[i] * (*this)[i];
			}
		}
		return ret;
	}
};

template <typename T, bool POINTER>
VectorImpl<T, POINTER> operator*(double scalar, const VectorImpl<T, POINTER>& vec)
{
	VectorImpl<T, POINTER> ret(vec);
	for (size_t i = 0; i < vec.len(); ++i)
	{
		ret[i] *= scalar;
	}
	return ret;
}

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
	VectorImpl<T*, POINTER> operator*(double scalar)
	{
		VectorImpl<T*, POINTER> ret(*this);
		for (size_t i = 0; i < this->len(); ++i)
		{
			if (ret[i] != nullptr)
				*(ret[i]) *= scalar;
		}
		return ret;
	}

	double operator*(const VectorImpl<T*, POINTER>& other)
	{
		double ret = 0;
		if (other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				if (other[i] != nullptr and (*this)[i] != nullptr)
				{
					ret += (*(other[i])) * (*(*this)[i]);
				}
			}
		}
		return ret;
	}
};

template <typename T, bool POINTER>
VectorImpl<T*, POINTER> operator*(double scalar, VectorImpl<T*, POINTER>& vec)
{
	VectorImpl<T*, POINTER> ret(vec);
	for (size_t i = 0; i < vec.len(); ++i)
	{
		if (ret[i] != nullptr)
		{
			*(ret[i]) *= scalar;
		}
	}
	return ret;
}

#endif // __VECTOR_NUM_HPP