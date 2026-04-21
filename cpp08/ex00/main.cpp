#include "easyfind.hpp"
#include <iostream>
#include <list>
#include <vector>

template <typename T>
void test(const T &container, int value) {
  try {
    std::cout << "find(" << value << ") -> " << easyfind(container, value) << std::endl;
  } catch (std::exception &e) {
    std::cout << "find(" << value << ") -> " << e.what() << std::endl;
  }
}

int main(void) {
  std::cout << "--- vector ---" << std::endl;
  std::vector<int> v;
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);
  test(v, 10);
  test(v, 20);
  test(v, 30);
  test(v, 99);

  std::cout << "\n--- list ---" << std::endl;
  std::list<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  test(l, 1);
  test(l, 3);
  test(l, 99);

  std::cout << "\n--- container avec un seul element ---" << std::endl;
  std::vector<int> single;
  single.push_back(42);
  test(single, 42);
  test(single, 0);

  std::cout << "\n--- container vide ---" << std::endl;
  std::vector<int> empty;
  test(empty, 1);

  std::cout << "\n--- container const ---" << std::endl;
  const std::vector<int> cv(v.begin(), v.end());
  test(cv, 10);
  test(cv, 99);

  return (0);
}
