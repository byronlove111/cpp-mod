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
  std::vector<int> diffs(sorted.size());
  std::adjacent_difference(sorted.begin(), sorted.end(), diffs.begin());
  int shortest = *std::min_element(diffs.begin() + 1, diffs.end());
  return shortest;
}

int Span::longestSpan() const {
  if (_numbers.size() < 2)
    throw Span::NotEnoughNumbersException();
  int max = *std::max_element(_numbers.begin(), _numbers.end());
  int min = *std::min_element(_numbers.begin(), _numbers.end());
  return max - min;
}

const char *Span::MaxCapacityException::what() const throw() {
  return "Span: max capacity reached";
}

const char *Span::NotEnoughNumbersException::what() const throw() {
  return "Span: not enough numbers to compute a span";
}
