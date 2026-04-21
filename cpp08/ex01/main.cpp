#include "Span.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

int main(void) {
  std::cout << "--- test sujet ---" << std::endl;
  Span sp(5);
  sp.addNumber(6);
  sp.addNumber(3);
  sp.addNumber(17);
  sp.addNumber(9);
  sp.addNumber(11);
  std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
  std::cout << "longestSpan:  " << sp.longestSpan() << std::endl;

  std::cout << "\n--- addNumber sur span plein ---" << std::endl;
  try {
    sp.addNumber(42);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "\n--- moins de 2 elements ---" << std::endl;
  try {
    Span sp2(5);
    sp2.addNumber(1);
    sp2.shortestSpan();
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "\n--- addRange ---" << std::endl;
  std::vector<int> v;
  v.push_back(10);
  v.push_back(5);
  v.push_back(20);
  v.push_back(1);
  Span sp3(10);
  sp3.addRange(v.begin(), v.end());
  std::cout << "shortestSpan: " << sp3.shortestSpan() << std::endl;
  std::cout << "longestSpan:  " << sp3.longestSpan() << std::endl;

  std::cout << "\n--- addRange depasse capacite ---" << std::endl;
  try {
    Span sp4(2);
    sp4.addRange(v.begin(), v.end());
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "\n--- 10 000 nombres ---" << std::endl;
  Span big(10000);
  std::vector<int> big_v;
  for (int i = 0; i < 10000; i++)
    big_v.push_back(std::rand());
  big.addRange(big_v.begin(), big_v.end());
  std::cout << "shortestSpan: " << big.shortestSpan() << std::endl;
  std::cout << "longestSpan:  " << big.longestSpan() << std::endl;

  return (0);
}
