#include "WrongCat.hpp"
#include <iostream>

WrongCat::WrongCat() : WrongAnimal("WrongCat") {
  std::cout << "WrongCat constructor" << std::endl;
}

WrongCat::WrongCat(const WrongCat &cat) : WrongAnimal(cat) {
  std::cout << "WrongCat copy constructor" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &other) {
  if (this != &other) {
    WrongAnimal::operator=(other);
    std::cout << "WrongCat assignment operator" << std::endl;
  }
  return *this;
}

WrongCat::~WrongCat() {
  std::cout << "WrongCat destructor" << std::endl;
}

void WrongCat::makeSound() const {
  std::cout << "Meow!" << std::endl;
}
