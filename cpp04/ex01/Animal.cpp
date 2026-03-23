#include "Animal.hpp"
#include <iostream>

Animal::Animal() : type("default animal") {
  std::cout << "Animal constructor" << std::endl;
}

Animal::Animal(std::string type) : type(type) {
  std::cout << "Animal constructor with type" << std::endl;
}

Animal::Animal(const Animal &animal) : type(animal.type) {
  std::cout << "Animal copy constructor" << std::endl;
}

Animal &Animal::operator=(const Animal &other) {
  if (this != &other) {
    type = other.type;
    std::cout << "Animal assignment operator" << std::endl;
  }
  return *this;
}

Animal::~Animal() {
  std::cout << "Animal destructor" << std::endl;
}

std::string Animal::getType() const {
  return type;
}

void Animal::makeSound() const {
  std::cout << "..." << std::endl;
}
