#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>

Cat::Cat() : AAnimal("Cat") {
  brain_ = new Brain();
  std::cout << "Cat constructor" << std::endl;
}

Cat::Cat(const Cat &cat) : AAnimal(cat) {
  brain_ = new Brain(*cat.brain_);
  std::cout << "Cat copy constructor" << std::endl;
}

Cat &Cat::operator=(const Cat &other) {
  if (this != &other) {
    AAnimal::operator=(other);
    *brain_ = *other.brain_;
    std::cout << "Cat assignment operator" << std::endl;
  }
  return *this;
}

Cat::~Cat() {
  delete brain_;
  std::cout << "Cat destructor" << std::endl;
}

void Cat::makeSound() const {
  std::cout << "Meow!" << std::endl;
}

Brain *Cat::getBrain() {
  return brain_;
}
