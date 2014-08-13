#ifndef __ABSTRACT_VECTOR_HPP
#define __ABSTRACT_VECTOR_HPP

#include <cstddef>
#include <type_traits>
#include <iterator>

template <typename T>
class AbstractVector
{
public:
	AbstractVector(size_t N) : _LENGTH(N)
	{}

	// getters and setters
	virtual T& operator[](size_t) = 0;
	virtual T const & operator[](size_t) const = 0;
	virtual size_t len() const { return _LENGTH; }

	class iterator
	{
	public:
		iterator(T* ptr) : _ptr(ptr) { }
		iterator operator++() { iterator i = *this; _ptr++; return i; }
		iterator operator++(int) { _ptr++; return *this; }
		T& operator*() { return *_ptr; }
		T* operator->() { return _ptr; }
		bool operator==(const iterator& rhs) { return _ptr == rhs._ptr; }
		bool operator!=(const iterator& rhs) { return _ptr != rhs._ptr; }
	private:
		T* _ptr;
	};
	 
	class const_iterator
	{
	public:
		const_iterator(T* ptr) : _ptr(ptr) { }
		const_iterator operator++() { const_iterator i = *this; _ptr++; return i; }
		const_iterator operator++(int) { _ptr++; return *this; }
		const T* operator*() { return *_ptr; }
		const T* operator->() { return _ptr; }
		bool operator==(const const_iterator& rhs) { return _ptr == rhs._ptr; }
		bool operator!=(const const_iterator& rhs) { return _ptr != rhs._ptr; }
	private:
		T* _ptr;
	};

	virtual iterator begin() = 0;
	virtual iterator end() = 0;
	virtual const_iterator begin() const = 0;
	virtual const_iterator end() const = 0;

protected:
	// I/O
	virtual void print(std::ostream& os, size_t index) const = 0;
	virtual void scan(std::istream& is, size_t index) = 0;
	const size_t _LENGTH;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const AbstractVector<T>& vec)
{
	os << "[";
	for (size_t i = 0; i < vec.len(); ++i)
	{
		if (i > 0)
		{
			os << ", ";
		}
		vec.print(os, i);
	}
    os << "]" << std::endl;
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, AbstractVector<T>& vec)
{
	for (size_t i = 0; i < vec.len(); ++i)
	{
		vec.scan(is, i);
	}
	return is;
}

#endif // __ABSTRACT_VECTOR_HPP