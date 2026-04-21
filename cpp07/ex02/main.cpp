#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Array.hpp"

#define MAX_VAL 750

int	main(int, char**)
{
	Array<int>	numbers(MAX_VAL);
	int*		mirror = new int[MAX_VAL];

	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}

	// deep copy test: tmp and test are destroyed at scope exit
	{
		Array<int>	tmp = numbers;
		Array<int>	test(tmp);
	}

	// original must be untouched after copies are destroyed
	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "didn't save the same value!!" << std::endl;
			return 1;
		}
	}

	// out-of-bounds: negative index
	try
	{
		numbers[-2] = 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	// out-of-bounds: index == size
	try
	{
		numbers[MAX_VAL] = 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	// writing new values through operator[]
	for (int i = 0; i < MAX_VAL; i++)
		numbers[i] = rand();

	delete[] mirror;

	// --- additional tests ---

	// empty array
	Array<int>	empty;
	std::cout << "empty array size: " << empty.size() << std::endl;
	try
	{
		empty[0] = 1;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	// string array
	Array<std::string>	words(3);
	words[0] = "hello";
	words[1] = "cpp";
	words[2] = "07";
	for (unsigned int i = 0; i < words.size(); i++)
		std::cout << words[i] << std::endl;

	// const array access
	const Array<std::string>	cwords(words);
	std::cout << "const access: " << cwords[1] << std::endl;

	// assignment operator — deep copy check
	Array<int>	a(3);
	a[0] = 10; a[1] = 20; a[2] = 30;
	Array<int>	b = a;
	b[0] = 99;
	std::cout << "a[0] after modifying b[0]: " << a[0] << " (should be 10)" << std::endl;

	return 0;
}
