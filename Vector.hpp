#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include "AbstractVector.hpp"

template <typename T, bool pointer>
class VectorImpl
{};

template <typename T>
class VectorImpl<T, false> : public AbstractVector<T>
{
public:
	VectorImpl(size_t len) : AbstractVector<T>(len), _data(new T[len])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = T();
		}
	}

	VectorImpl(const VectorImpl<T, false>& other) : AbstractVector<T>(other.len()), _data(new T[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = other[i];
		}
	}


	VectorImpl(typename AbstractVector<T>::iterator beg, typename AbstractVector<T>::iterator end) : AbstractVector<T>(static_cast<size_t>(end-beg)), _data(new T[this->len()])
	{
		for (size_t i = 0; beg != end; ++i, ++beg)
		{
			(*this)[i] = *beg;
		}
	}

	VectorImpl(typename AbstractVector<T*>::iterator beg, typename AbstractVector<T*>::iterator end) : AbstractVector<T>(static_cast<size_t>(end-beg)), _data(new T[this->len()])
	{
		for (size_t i = 0; beg != end; ++i, ++beg)
		{
			if (*beg != nullptr)
			{
				(*this)[i] = **beg;
			}
			else
			{
				(*this)[i] = T();
			}
		}
	}

	// Constructor from VectorImpl<T, ...> where T is any equivalent/convertible type
	template <typename U>
	VectorImpl(const AbstractVector<U>& other) : AbstractVector<T>(other.len()), _data(new T[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = other[i];
		}
	}

	// Constructor from VectorImpl<T*, ...> where T is any equivalent/convertible type
	template <typename U>
	VectorImpl(const AbstractVector<U*>& other) : AbstractVector<T>(other.len()), _data(new T[other.len()])
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
		delete[] _data;
	}

	VectorImpl& operator=(const VectorImpl<T, false>& other)
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

	typename AbstractVector<T>::iterator begin()
	{
		return typename AbstractVector<T>::iterator(this->_data);
	}

	typename AbstractVector<T>::iterator end()
	{
		return typename AbstractVector<T>::iterator(this->_data + this->len());
	}

	typename AbstractVector<T>::const_iterator begin() const
	{
		return typename AbstractVector<T>::const_iterator(this->_data);
	}

	typename AbstractVector<T>::const_iterator end() const
	{
		return typename AbstractVector<T>::const_iterator(this->_data + this->len());
	}

protected:
	virtual void print(std::ostream& os, size_t index) const
	{
		os << this->_data[index];
	}

	virtual void scan(std::istream& is, size_t index)
	{
		is >> this->_data[index];
	}

	T* _data;

};

template <typename T>
class VectorImpl<T, true> : public AbstractVector<T>
{
public:
	VectorImpl(size_t len) : AbstractVector<T>(len), _data(new T*[len])
	{
		for (size_t i = 0; i < len; ++i)
		{
			this->_data[i] = new T();
		}
	}

	VectorImpl(const VectorImpl<T, true>& other) : AbstractVector<T>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(other[i]);
		}
	}

	VectorImpl(typename AbstractVector<T>::iterator beg, typename AbstractVector<T>::iterator end) : AbstractVector<T>(static_cast<size_t>(end-beg)), _data(new T*[this->len()])
	{
		for (size_t i = 0; beg != end; ++i, ++beg)
		{
			this->_data[i] = new T(*beg);
		}
	}

	VectorImpl(typename AbstractVector<T*>::iterator beg, typename AbstractVector<T*>::iterator end) : AbstractVector<T>(static_cast<size_t>(end-beg)), _data(new T*[this->len()])
	{
		for (size_t i = 0; beg != end; ++i, ++beg)
		{
			if (*beg != nullptr)
			{
				this->_data[i] = new T(**beg);
			}
			else
			{
				this->_data[i] = new T();
			}
		}
	}

	// Constructor from VectorImpl<T, ...>
	template <typename U>
	VectorImpl(const AbstractVector<U>& other) : AbstractVector<T>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(other[i]);
		}
	}

	// Constructor from VectorImpl<T*, ...>
	template <typename U>
	VectorImpl(const AbstractVector<U*>& other) : AbstractVector<T>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			if (other[i] == nullptr)
			{
				this->_data[i] = new T();
			}
			else
			{
				this->_data[i] = new T(*(other[i]));
			}
		}
	}

	VectorImpl& operator=(const VectorImpl<T, true>& other)
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

	~VectorImpl()
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

	typename AbstractVector<T>::iterator begin()
	{
		return typename AbstractVector<T>::iterator(this->_data[0]);
	}

	typename AbstractVector<T>::iterator end()
	{
		return typename AbstractVector<T>::iterator(this->_data[0] + this->len());
	}

	typename AbstractVector<T>::const_iterator begin() const
	{
		return typename AbstractVector<T>::const_iterator(this->_data[0]);
	}

	typename AbstractVector<T>::const_iterator end() const
	{
		return typename AbstractVector<T>::const_iterator(this->_data[0] + this->len());
	}

protected:
	virtual void print(std::ostream& os, size_t index) const
	{
		os << *(this->_data[index]);
	}

	virtual void scan(std::istream& is, size_t index)
	{
		is >> *(this->_data[index]);
	}

	T** _data;
};

template <typename T>
class VectorImpl<T*, false> : public AbstractVector<T*>
{
public:
	VectorImpl(size_t len) : AbstractVector<T*>(len), _data(new T*[len])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = nullptr;
		}
	}

	VectorImpl(const VectorImpl<T*, false>& other) : AbstractVector<T*>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			if (other[i] == nullptr)
			{
				this->_data[i] = nullptr;
			}
			else
			{
				this->_data[i] = new T(*(other[i]));
			}
		}
	}

	VectorImpl(typename AbstractVector<T>::iterator beg, typename AbstractVector<T>::iterator end) : AbstractVector<T*>(static_cast<size_t>(end-beg)), _data(new T*[this->len()])
	{
		for (size_t i = 0; beg != end; ++i, ++beg)
		{
			this->_data[i] = new T(*beg);
		}
	}

	VectorImpl(typename AbstractVector<T*>::iterator beg, typename AbstractVector<T*>::iterator end) : AbstractVector<T*>(static_cast<size_t>(end-beg)), _data(new T*[this->len()])
	{
		for (size_t i = 0; beg != end; ++i, ++beg)
		{
			if (*beg != nullptr)
			{
				this->_data[i] = new T(**beg);
			}
			else
			{
				this->_data[i] = nullptr;
			}
		}
	}

	// Constructor from VectorImpl<T, ...>
	template <typename U>
	VectorImpl(const AbstractVector<U>& other) : AbstractVector<T*>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			this->_data[i] = new T(other[i]);
		}
	}

	// Constructor from VectorImpl<T*, ...>
	template <typename U>
	VectorImpl(const AbstractVector<U*>& other) : AbstractVector<T*>(other.len()), _data(new T*[other.len()])
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			if (other[i] == nullptr)
			{
				this->_data[i] = nullptr;
			}
			else
			{
				this->_data[i] = new T(*(other[i]));
			}
		}
	}

	VectorImpl& operator=(const VectorImpl<T*, false>& other)
	{
		if (&other != this and other.len() == this->len())
		{
			for (size_t i = 0; i < this->len(); ++i)
			{
				if (other[i] == nullptr)
				{
					if (this->_data[i] != nullptr)
					{
						delete this->_data[i];
						this->_data[i] = nullptr;
					}
				}
				else
				{
					if (this->_data[i] != nullptr)
					{
						*(this->_data[i]) = *(other[i]);
					}
					else
					{
						this->_data[i] = new T(*(other[i]));
					}
				}
			}
		}
		return *this;
	}

	~VectorImpl()
	{
		for (size_t i = 0; i < this->len(); ++i)
		{
			if (this->_data[i] != nullptr)
			{
				delete this->_data[i];				
			}
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

	typename AbstractVector<T*>::iterator begin()
	{
		return typename AbstractVector<T*>::iterator(this->_data);
	}

	typename AbstractVector<T*>::iterator end()
	{
		return typename AbstractVector<T*>::iterator(this->_data + this->len());
	}

	typename AbstractVector<T*>::const_iterator begin() const
	{
		return typename AbstractVector<T*>::const_iterator(this->_data);
	}

	typename AbstractVector<T*>::const_iterator end() const
	{
		return typename AbstractVector<T*>::const_iterator(this->_data + this->len());
	}

protected:
	virtual void print(std::ostream& os, size_t index) const
	{
		if (this->_data[index] != nullptr)
		{
			os << *(this->_data[index]);
		}
	}

	virtual void scan(std::istream& is, size_t index)
	{
		if (this->_data[index] != nullptr)
		{
			is >> *(this->_data[index]);
		}
	}

	T** _data;
};

template <typename T>
class VectorImpl<T*, true> : public VectorImpl<T*, false>
{
public:
	using VectorImpl<T*, false>::VectorImpl;
};

template <typename T, bool POINTER, typename Enable = void>
class Vector : public VectorImpl<T, POINTER>
{
public:
	using VectorImpl<T, POINTER>::VectorImpl;
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