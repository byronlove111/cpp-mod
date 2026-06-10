#include "RPN.hpp"
#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::~RPN() {}

int RPN::evaluate(const std::string& expression)
{
    _stack.clear();

    std::istringstream stream(expression);
    std::string        token;

    while (stream >> token)
    {
        if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
        {
            _stack.push_back(token[0] - '0');
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Error");

            int right = _stack.back(); _stack.pop_back();
            int left  = _stack.back(); _stack.pop_back();
            int result;

            if (token == "+")      result = left + right;
            else if (token == "-") result = left - right;
            else if (token == "*") result = left * right;
            else
            {
                if (right == 0)
                    throw std::runtime_error("Error");
                result = left / right;
            }
            _stack.push_back(result);
        }
        else
        {
            throw std::runtime_error("Error");
        }
    }

    if (_stack.size() != 1)
        throw std::runtime_error("Error");

    return _stack.back();
}
