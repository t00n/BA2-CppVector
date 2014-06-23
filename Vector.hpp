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

};

#endif // __VECTOR_HPP