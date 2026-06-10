#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

# include <vector>
# include <deque>
# include <string>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::deque<int>  _deq;

    static void fordJohnsonVec(std::vector<int>& sequence);
    static void fordJohnsonDeq(std::deque<int>& sequence);

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    bool parse(int argc, char* argv[]);
    void run();
};

#endif
