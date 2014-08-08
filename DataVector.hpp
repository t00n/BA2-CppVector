#ifndef __DATA_VECTOR_HPP
#define __DATA_VECTOR_HPP

#include <cstddef>

template <typename T>
class DataVector
{
public:
	DataVector(size_t len) : _LENGTH(len), _data(new T[len])
	{}

	~DataVector()
	{
		delete[] this->_data;
	}

	T& operator[](size_t index)
	{
		return this->_data[index];
	}

	const T& operator[](size_t index) const
	{
		return this->_data[index];
	}

	size_t len() const
	{
		return this->_LENGTH;
	}

private:
	size_t _LENGTH;
	T* _data;
};

#endif // __DATA_VECTOR_HPP