#ifndef __VECTOR_IMPL_HPP
#define __VECTOR_IMPL_HPP

template <typename T>
class VectorImpl
{
public:
	VectorImpl(size_t len) : _LENGTH(len), _data(new T[len])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = T();
		}
	}

	VectorImpl(VectorImpl<T>& other) : _LENGTH(other.len()), _data(new T[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = other[i];
		}
	}

	VectorImpl(VectorImpl<T*>& other) : _LENGTH(other.len()), _data(new T[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			if (other[i] == nullptr)
			{
				this->_data[i] = T();
			}
			else
			{
				this->_data[i] = *(other[i]);
			}
		}
	}

	~VectorImpl()
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
		return _LENGTH;
	}

private:
	const size_t _LENGTH;
	T* _data;
};

template <typename T>
class VectorImpl<T*>
{
public:
	VectorImpl(size_t len, bool init = true) : _LENGTH(len), _data(new T*[len]), _copy(init)
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			if (init)
			{
				this->_data[i] = new T();
			}
			else
			{
				this->_data[i] = nullptr;
			}
		}
	}

	VectorImpl(VectorImpl<T>& other) : _LENGTH(other.len()), _data(new T*[other.len()]), _copy(true)
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(other[i]);
		}
	}

	VectorImpl(VectorImpl<T*>& other, bool init = true) : _LENGTH(other.len()), _data(new T*[other.len()]), _copy(true)
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			if (other[i] == nullptr)
			{
				if (init)
				{
					this->_data[i] = new T();
				}
				else
				{
					this->_data[i] = nullptr;
				}
			}
			else
			{
				this->_data[i] = new T(*(other[i]));
			}
		}
	}

	~VectorImpl()
	{
		if (_copy)
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				if (this->_data[i] != nullptr)
				{
					delete this->_data[i];
				}
			}
		}
		delete[] this->_data;
	}

	T& operator[](size_t index)
	{
		return *(this->_data[index]);
	}

	const T& operator[](size_t index) const
	{
		return *(this->_data[index]);
	}

	size_t len() const
	{
		return _LENGTH;
	}

private:
	const size_t _LENGTH;
	T** _data;
	bool _copy;
};

#endif // __VECTOR_IMPL_HPP