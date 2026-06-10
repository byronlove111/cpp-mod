#include "PmergeMe.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <sys/time.h>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

static std::vector<size_t> computeJacobsthalOrder(size_t numPairs)
{
    std::vector<size_t> insertionOrder;
    if (numPairs == 0)
        return insertionOrder;

    std::vector<size_t> jacobsthal;
    jacobsthal.push_back(1);
    if (numPairs > 1)
        jacobsthal.push_back(3);
    while (jacobsthal.back() < numPairs)
    {
        size_t last       = jacobsthal[jacobsthal.size() - 1];
        size_t secondLast = jacobsthal[jacobsthal.size() - 2];
        jacobsthal.push_back(last + 2 * secondLast);
    }

    size_t previousGroupEnd = 0;
    for (size_t groupIndex = 1; groupIndex < jacobsthal.size(); groupIndex++)
    {
        size_t rawGroupEnd     = jacobsthal[groupIndex] - 1;
        size_t currentGroupEnd;
        if (rawGroupEnd < numPairs - 1)
            currentGroupEnd = rawGroupEnd;
        else
            currentGroupEnd = numPairs - 1;

        for (size_t index = currentGroupEnd; index > previousGroupEnd; index--)
            insertionOrder.push_back(index);

        previousGroupEnd = currentGroupEnd;
        if (previousGroupEnd >= numPairs - 1)
            break;
    }
    return insertionOrder;
}

static size_t lowerBoundVec(const std::vector<int>& chain, size_t rangeStart, size_t rangeEnd, int value)
{
    while (rangeStart < rangeEnd)
    {
        size_t midpoint = rangeStart + (rangeEnd - rangeStart) / 2;
        if (chain[midpoint] < value)
            rangeStart = midpoint + 1;
        else
            rangeEnd = midpoint;
    }
    return rangeStart;
}

void PmergeMe::fordJohnsonVec(std::vector<int>& arr)
{
    size_t totalElements = arr.size();
    if (totalElements <= 1)
        return;

    bool   hasOddElement = (totalElements % 2 == 1);
    int    oddElement    = 0;
    size_t numPairs      = totalElements / 2;

    if (hasOddElement)
        oddElement = arr[totalElements - 1];

    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < numPairs; i++)
    {
        int left  = arr[2 * i];
        int right = arr[2 * i + 1];
        if (left >= right)
            pairs.push_back(std::make_pair(left, right));
        else
            pairs.push_back(std::make_pair(right, left));
    }

    std::vector<int> mainElements;
    for (size_t i = 0; i < pairs.size(); i++)
        mainElements.push_back(pairs[i].first);
    fordJohnsonVec(mainElements);
    std::sort(pairs.begin(), pairs.end());

    std::vector<int>    sortedChain(mainElements);
    std::vector<size_t> mainPositions(numPairs);
    for (size_t i = 0; i < numPairs; i++)
        mainPositions[i] = i;

    sortedChain.insert(sortedChain.begin(), pairs[0].second);
    for (size_t i = 0; i < numPairs; i++)
        mainPositions[i]++;

    std::vector<size_t> insertionOrder = computeJacobsthalOrder(numPairs);
    for (size_t step = 0; step < insertionOrder.size(); step++)
    {
        size_t pairIndex    = insertionOrder[step];
        int    pendingValue = pairs[pairIndex].second;
        size_t pos          = lowerBoundVec(sortedChain, 0, mainPositions[pairIndex], pendingValue);

        sortedChain.insert(sortedChain.begin() + static_cast<long>(pos), pendingValue);
        for (size_t i = 0; i < mainPositions.size(); i++)
        {
            if (mainPositions[i] >= pos)
                mainPositions[i]++;
        }
    }

    if (hasOddElement)
    {
        size_t pos = lowerBoundVec(sortedChain, 0, sortedChain.size(), oddElement);
        sortedChain.insert(sortedChain.begin() + static_cast<long>(pos), oddElement);
    }

    arr = sortedChain;
}

static size_t lowerBoundDeq(const std::deque<int>& chain, size_t rangeStart, size_t rangeEnd, int value)
{
    while (rangeStart < rangeEnd)
    {
        size_t midpoint = rangeStart + (rangeEnd - rangeStart) / 2;
        if (chain[midpoint] < value)
            rangeStart = midpoint + 1;
        else
            rangeEnd = midpoint;
    }
    return rangeStart;
}

void PmergeMe::fordJohnsonDeq(std::deque<int>& arr)
{
    size_t totalElements = arr.size();
    if (totalElements <= 1)
        return;

    bool   hasOddElement = (totalElements % 2 == 1);
    int    oddElement    = 0;
    size_t numPairs      = totalElements / 2;

    if (hasOddElement)
        oddElement = arr[totalElements - 1];

    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < numPairs; i++)
    {
        int left  = arr[2 * i];
        int right = arr[2 * i + 1];
        if (left >= right)
            pairs.push_back(std::make_pair(left, right));
        else
            pairs.push_back(std::make_pair(right, left));
    }

    std::deque<int> mainElements;
    for (size_t i = 0; i < pairs.size(); i++)
        mainElements.push_back(pairs[i].first);
    fordJohnsonDeq(mainElements);
    std::sort(pairs.begin(), pairs.end());

    std::deque<int>    sortedChain(mainElements);
    std::deque<size_t> mainPositions(numPairs);
    for (size_t i = 0; i < numPairs; i++)
        mainPositions[i] = i;

    sortedChain.insert(sortedChain.begin(), pairs[0].second);
    for (size_t i = 0; i < numPairs; i++)
        mainPositions[i]++;

    std::vector<size_t> insertionOrder = computeJacobsthalOrder(numPairs);
    for (size_t step = 0; step < insertionOrder.size(); step++)
    {
        size_t pairIndex    = insertionOrder[step];
        int    pendingValue = pairs[pairIndex].second;
        size_t pos          = lowerBoundDeq(sortedChain, 0, mainPositions[pairIndex], pendingValue);

        sortedChain.insert(sortedChain.begin() + static_cast<long>(pos), pendingValue);
        for (size_t i = 0; i < mainPositions.size(); i++)
        {
            if (mainPositions[i] >= pos)
                mainPositions[i]++;
        }
    }

    if (hasOddElement)
    {
        size_t pos = lowerBoundDeq(sortedChain, 0, sortedChain.size(), oddElement);
        sortedChain.insert(sortedChain.begin() + static_cast<long>(pos), oddElement);
    }

    arr = sortedChain;
}

static double getCurrentTimeMicroseconds()
{
    struct timeval timestamp;
    gettimeofday(&timestamp, NULL);
    return static_cast<double>(timestamp.tv_sec) * 1e6
         + static_cast<double>(timestamp.tv_usec);
}

static void printSequence(const std::string& label, const std::vector<int>& sequence)
{
    std::cout << label;
    for (size_t i = 0; i < sequence.size(); i++)
        std::cout << " " << sequence[i];
    std::cout << std::endl;
}

bool PmergeMe::parse(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        std::string argument = argv[i];

        if (argument.empty() || argument[0] == '-')
        {
            std::cerr << "Error" << std::endl;
            return false;
        }

        size_t digitStart = 0;
        if (argument[0] == '+')
            digitStart = 1;

        if (digitStart >= argument.size())
        {
            std::cerr << "Error" << std::endl;
            return false;
        }

        for (size_t j = digitStart; j < argument.size(); j++)
        {
            if (argument[j] < '0' || argument[j] > '9')
            {
                std::cerr << "Error" << std::endl;
                return false;
            }
        }

        errno = 0;
        long val = std::strtol(argument.c_str(), NULL, 10);
        if (errno == ERANGE || val <= 0 || val > static_cast<long>(INT_MAX))
        {
            std::cerr << "Error" << std::endl;
            return false;
        }

        _vec.push_back(static_cast<int>(val));
        _deq.push_back(static_cast<int>(val));
    }
    return true;
}

void PmergeMe::run()
{
    printSequence("Before:", _vec);

    double startVec = getCurrentTimeMicroseconds();
    fordJohnsonVec(_vec);
    double vecTime  = getCurrentTimeMicroseconds() - startVec;

    double startDeq = getCurrentTimeMicroseconds();
    fordJohnsonDeq(_deq);
    double deqTime  = getCurrentTimeMicroseconds() - startDeq;

    printSequence("After:", _vec);

    size_t elementCount = _vec.size();
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << elementCount
              << " elements with std::vector : " << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << elementCount
              << " elements with std::deque  : " << deqTime << " us" << std::endl;
}
