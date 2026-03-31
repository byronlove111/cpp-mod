#include "AAnimal.hpp"
#include <iostream>

AAnimal::AAnimal() : type("default animal") {
  std::cout << "Animal constructor" << std::endl;
}

AAnimal::AAnimal(std::string type) : type(type) {
  std::cout << "Animal constructor with type" << std::endl;
}

AAnimal::AAnimal(const AAnimal &animal) : type(animal.type) {
  std::cout << "Animal copy constructor" << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &other) {
  if (this != &other) {
    type = other.type;
    std::cout << "Animal assignment operator" << std::endl;
  }
  return *this;
}

AAnimal::~AAnimal() {
  std::cout << "Animal destructor" << std::endl;
}

std::string AAnimal::getType() const {
  return type;
}
