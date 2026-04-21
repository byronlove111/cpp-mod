#include "Span.hpp"

Span::Span() : _n(0) {
}

Span::Span(unsigned int n) : _n(n) {
}

Span::Span(const Span &other) : _n(other._n), _numbers(other._numbers) {
}

Span &Span::operator=(const Span &other) {
  if (this != &other) {
    this->_n = other._n;
    this->_numbers = other._numbers;
  }
  return *this;
}

Span::~Span() {
}

void Span::addNumber(int n) {
  if (_numbers.size() >= _n)
    throw Span::MaxCapacityException();
  _numbers.push_back(n);
}

void Span::addRange(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
  if (_numbers.size() + static_cast<size_t>(std::distance(begin, end)) > _n) {
    throw Span::MaxCapacityException();
  }
  _numbers.insert(_numbers.end(), begin, end);
}

int Span::shortestSpan() const {
  if (_numbers.size() < 2)
    throw Span::NotEnoughNumbersException();
  std::vector<int> sorted(_numbers);
  std::sort(sorted.begin(), sorted.end());
  int shortest = sorted[1] - sorted[0];
  for (size_t i = 1; i < sorted.size() - 1; i++)
    shortest = std::min(shortest, sorted[i + 1] - sorted[i]);
  return shortest;
}

int Span::longestSpan() const {
  if (_numbers.size() < 2)
    throw Span::NotEnoughNumbersException();
  std::vector<int> sorted(_numbers);
  std::sort(sorted.begin(), sorted.end());
  return sorted.back() - sorted.front();
}

const char *Span::MaxCapacityException::what() const throw() {
  return "Span: max capacity reached";
}

const char *Span::NotEnoughNumbersException::what() const throw() {
  return "Span: not enough numbers to compute a span";
}
