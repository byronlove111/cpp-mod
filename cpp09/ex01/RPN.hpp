#ifndef RPN_HPP
# define RPN_HPP

# include <list>
# include <string>

class RPN
{
private:
    std::list<int> _stack;

public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    int evaluate(const std::string& expression);
};

#endif
