#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog") {
  std::cout << "Dog constructor" << std::endl;
}

Dog::Dog(const Dog &dog) : Animal(dog) {
  std::cout << "Dog copy constructor" << std::endl;
}

Dog &Dog::operator=(const Dog &other) {
  if (this != &other) {
    Animal::operator=(other);
    std::cout << "Dog assignment operator" << std::endl;
  }
  return *this;
}

Dog::~Dog() {
  std::cout << "Dog destructor" << std::endl;
}

void Dog::makeSound() const {
  std::cout << "Woof! Woof!" << std::endl;
}
