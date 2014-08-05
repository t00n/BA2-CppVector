#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include "AbstractVector.hpp"

template <typename T, bool pointer>
class Vector
{
public:

private:

};

template <typename T>
class Vector<T, false> : public AbstractValueVector<T>
{
public:
	using AbstractValueVector<T>::AbstractValueVector;
};

template <typename T>
class Vector<T, true> : public AbstractPointerVector<T>
{
public:
	using AbstractPointerVector<T>::AbstractPointerVector;
};

template <typename T>
class Vector<T*, false> : public Vector<T, true>
{
public:
	using Vector<T, true>::Vector;
};

template <typename T>
class Vector<T*, true> : public Vector<T, true>
{
public:
	using Vector<T, true>::Vector;
};

#endif // __VECTOR_HPP