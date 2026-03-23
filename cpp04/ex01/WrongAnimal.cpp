#include "WrongAnimal.hpp"
#include <iostream>

WrongAnimal::WrongAnimal() : type("default animal") {
  std::cout << "WrongAnimal constructor" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type) : type(type) {
  std::cout << "WrongAnimal constructor with type" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &other) : type(other.type) {
  std::cout << "WrongAnimal copy constructor" << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other) {
  if (this != &other) {
    type = other.type;
    std::cout << "WrongAnimal assignment operator" << std::endl;
  }
  return *this;
}

WrongAnimal::~WrongAnimal() {
  std::cout << "WrongAnimal destructor" << std::endl;
}

std::string WrongAnimal::getType() const {
  return type;
}

void WrongAnimal::makeSound() const {
  std::cout << "..." << std::endl;
}
