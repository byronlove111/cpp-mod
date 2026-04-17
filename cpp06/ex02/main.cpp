#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  std::srand(std::time(NULL));

  for (int i = 0; i < 10; i++) {
    Base *p = generate();
    std::cout << "pointer : ";
    identify(p);
    std::cout << "reference: ";
    identify(*p);
    delete p;
    std::cout << std::endl;
  }
  return 0;
}
