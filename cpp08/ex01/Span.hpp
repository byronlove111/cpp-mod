#ifndef SPAN_HPP
#define SPAN_HPP

#include <algorithm>
#include <stdexcept>
#include <vector>

class Span {
  private:
  unsigned int _n;
  std::vector<int> _numbers;

  public:
  Span();
  Span(unsigned int n);
  Span(const Span &other);
  Span &operator=(const Span &other);
  ~Span();

  void addNumber(int n);
  void addRange(std::vector<int>::iterator begin, std::vector<int>::iterator end);
  int shortestSpan() const;
  int longestSpan() const;

  class MaxCapacityException : public std::exception {
    public:
    const char *what() const throw();
  };

  class NotEnoughNumbersException : public std::exception {
    public:
    const char *what() const throw();
  };
};

#endif
