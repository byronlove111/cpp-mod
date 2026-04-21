#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void	print(T const& x)
{
	std::cout << x << std::endl;
}

template <typename T>
void	increment(T& x)
{
	x++;
}

int	main(void)
{
	// int array — print
	int	arr[] = {0, 1, 2, 3, 4};
	std::size_t	len = sizeof(arr) / sizeof(arr[0]);

	std::cout << "--- int array (print) ---" << std::endl;
	iter(arr, len, print<int>);

	// int array — increment then print
	iter(arr, len, increment<int>);
	std::cout << "--- int array after increment ---" << std::endl;
	iter(arr, len, print<int>);

	// const int array — print only
	const int	carr[] = {42, 42, 42, 42, 42};
	std::size_t	clen = sizeof(carr) / sizeof(carr[0]);

	std::cout << "--- const int array (print) ---" << std::endl;
	iter(carr, clen, print<int>);

	// string array
	std::string	words[] = {"hello", "world", "cpp07"};
	std::size_t	wlen = sizeof(words) / sizeof(words[0]);

	std::cout << "--- string array (print) ---" << std::endl;
	iter(words, wlen, print<std::string>);

	return 0;
}
