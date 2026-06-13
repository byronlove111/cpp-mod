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

// implementation de la formule jacobshtal en code
static std::vector<size_t> computeJacobsthalOrder(size_t numPairs)
{
    std::vector<size_t> insertionOrder;
    if (numPairs == 0)
        return insertionOrder;

    // vector qui calcule les delimitations entre les paires
    std::vector<size_t> jacobsthal;
    jacobsthal.push_back(1);
    if (numPairs > 1)
        jacobsthal.push_back(3);
    while (jacobsthal.back() < numPairs)
    {
        // la formule == chaque nombre = nombre precedent + 2 * nombre avant le precedent
        // ex : on a deja [1, 3], on calcule 3 + 2*1 = 5, puis 5 + 2*3 = 11 ect
        // on continue jusqu'a ce que le dernier nombre depasse le nombre de paires
        size_t last       = jacobsthal[jacobsthal.size() - 1];
        size_t secondLast = jacobsthal[jacobsthal.size() - 2];
        jacobsthal.push_back(last + 2 * secondLast);
    }

    // on parcourt chaque groupe defini par les bornes de jacobsthal.
    // dans chaque groupe, on ajoute les indices de paires de droite a gauche
    // (du plus grand index vers le plus petit) car c'est l'ordre optimal de jacobsthal
    // previousGroupEnd marque la frontiere gauche du groupe courant
    // la paire 0 etant deja inseree gratuitement on part de 0
    size_t previousGroupEnd = 0;
    for (size_t groupIndex = 1; groupIndex < jacobsthal.size(); groupIndex++)
    {
        // jacobsthal stocke des valeurs comme 3, 5, 11
        // on soustrait 1 pour convertir en indice de paire (les paires sont numerotees a partir de 0)
        // si ce groupe theorique depasse les paires qu'on a vraiment, on s'arrete a la derniere paire disponible
        size_t rawGroupEnd     = jacobsthal[groupIndex] - 1;
        size_t currentGroupEnd;
        if (rawGroupEnd < numPairs - 1)
            currentGroupEnd = rawGroupEnd;
        else
            currentGroupEnd = numPairs - 1;

        // on insere les indices du groupe de droite a gauche dans insertionOrder
        for (size_t index = currentGroupEnd; index > previousGroupEnd; index--)
            insertionOrder.push_back(index);

        previousGroupEnd = currentGroupEnd;
        if (previousGroupEnd >= numPairs - 1)
            break;
    }
    // ex : 5 paires  = [2, 1, 4, 3] pour l'ordre d'insertion
    return insertionOrder;
}

static size_t lowerBoundVec(const std::vector<int>& chain, size_t rangeStart, size_t rangeEnd, int value)
{
    while (rangeStart < rangeEnd)
    {
        // on calcule le milieu ainsi pour eviter un overflow si rangeStart + rangeEnd depasse SIZE_MAX
        size_t midpoint = rangeStart + (rangeEnd - rangeStart) / 2;
        if (chain[midpoint] < value)
            rangeStart = midpoint + 1; // la valeur est dans la moitie droite
        else
            rangeEnd = midpoint;       // la valeur est dans la moitie gauche
    }
    // quand rangeStart == rangeEnd, la zone est vide : rangeStart est la position exacte d'insertion
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

    // on extrait les grands de chaque paire et on les trie recursivement
    std::vector<int> mainElements;
    for (size_t i = 0; i < pairs.size(); i++)
        mainElements.push_back(pairs[i].first);
    fordJohnsonVec(mainElements);
    // apres la recursion, mainElements est trie - on retrie pairs par leur grand
    // pour que pairs[i] corresponde a mainElements[i] et que le lien grand/petit soit conserve
    std::sort(pairs.begin(), pairs.end());

    // sortedChain est la chaine dans laquelle on va inserer les petits un par un
    // mainPositions suit la position actuelle de chaque grand dans sortedChain
    // (les grands se decalent a droite a chaque insertion d'un petit)
    std::vector<int>    sortedChain(mainElements);
    std::vector<size_t> mainPositions(numPairs);
    for (size_t i = 0; i < numPairs; i++)
        mainPositions[i] = i;

    // le petit de la paire 0 est insere gratuitement au debut : il est forcement
    // plus petit que tous les grands car son grand est le plus petit de tous
    sortedChain.insert(sortedChain.begin(), pairs[0].second);
    // tous les grands se sont decales d'une position vers la droite
    for (size_t i = 0; i < numPairs; i++)
        mainPositions[i]++;

    std::vector<size_t> insertionOrder = computeJacobsthalOrder(numPairs);
    for (size_t step = 0; step < insertionOrder.size(); step++)
    {
        size_t pairIndex    = insertionOrder[step];
        int    pendingValue = pairs[pairIndex].second;
        // on cherche la position d'insertion uniquement avant le grand de cette paire
        // car le petit est forcement plus petit que son grand (etabli lors du pairing)
        size_t pos          = lowerBoundVec(sortedChain, 0, mainPositions[pairIndex], pendingValue);

        sortedChain.insert(sortedChain.begin() + static_cast<long>(pos), pendingValue);
        // tous les grands a partir de la position d'insertion se sont decales d'une position
        for (size_t i = 0; i < mainPositions.size(); i++)
        {
            if (mainPositions[i] >= pos)
                mainPositions[i]++;
        }
    }

    // le retardataire n'a pas de grand associe : on cherche dans toute la chaine
    if (hasOddElement)
    {
        size_t pos = lowerBoundVec(sortedChain, 0, sortedChain.size(), oddElement);
        sortedChain.insert(sortedChain.begin() + static_cast<long>(pos), oddElement);
    }

    // on ecrase arr avec le resultat trie (arr est passe par reference, le niveau appelant recupere le tri)
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
