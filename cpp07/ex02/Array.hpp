#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <stdexcept>

template <typename T>
class Array
{
private:
	T*				_arr;
	unsigned int	_size;

public:
	Array() : _arr(NULL), _size(0) {}

	Array(unsigned int n) : _arr(new T[n]()), _size(n) {}

	Array(Array const& src) : _arr(new T[src._size]()), _size(src._size)
	{
		for (unsigned int i = 0; i < _size; i++)
			_arr[i] = src._arr[i];
	}

	~Array() { delete[] _arr; }

	Array&	operator=(Array const& rhs)
	{
		if (this != &rhs)
		{
			delete[] _arr;
			_size = rhs._size;
			_arr = new T[_size]();
			for (unsigned int i = 0; i < _size; i++)
				_arr[i] = rhs._arr[i];
		}
		return *this;
	}

	T&	operator[](int index)
	{
		if (index < 0 || static_cast<unsigned int>(index) >= _size)
			throw std::out_of_range("index out of bounds");
		return _arr[index];
	}

	T const&	operator[](int index) const
	{
		if (index < 0 || static_cast<unsigned int>(index) >= _size)
			throw std::out_of_range("index out of bounds");
		return _arr[index];
	}

	unsigned int	size() const { return _size; }
};

#endif
