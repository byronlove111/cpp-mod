#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    PmergeMe sorter;

    if (!sorter.parse(argc, argv))
        return 1;

    sorter.run();
    return 0;
}
