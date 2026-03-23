#include "Cat.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat") {
  std::cout << "Cat constructor" << std::endl;
}

Cat::Cat(const Cat &cat) : Animal(cat) {
  std::cout << "Cat copy constructor" << std::endl;
}

Cat &Cat::operator=(const Cat &other) {
  if (this != &other) {
    Animal::operator=(other);
    std::cout << "Cat assignment operator" << std::endl;
  }
  return *this;
}

Cat::~Cat() {
  std::cout << "Cat destructor" << std::endl;
}

void Cat::makeSound() const {
  std::cout << "Meow!" << std::endl;
}
