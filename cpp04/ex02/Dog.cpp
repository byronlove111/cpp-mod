#include "Dog.hpp"
#include <iostream>

Dog::Dog() : AAnimal("Dog") {
  brain_ = new Brain();
  std::cout << "Dog constructor" << std::endl;
}

Dog::Dog(const Dog &dog) : AAnimal(dog) {
  brain_ = new Brain(*dog.brain_);
  std::cout << "Dog copy constructor" << std::endl;
}

Dog &Dog::operator=(const Dog &other) {
  if (this != &other) {
    AAnimal::operator=(other);
    *brain_ = *other.brain_;
    std::cout << "Dog assignment operator" << std::endl;
  }
  return *this;
}

Dog::~Dog() {
  delete brain_;
  std::cout << "Dog destructor" << std::endl;
}

void Dog::makeSound() const {
  std::cout << "Woof! Woof!" << std::endl;
}

Brain *Dog::getBrain() {
  return brain_;
}
