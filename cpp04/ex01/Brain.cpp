#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
  std::cout << "Brain constructor" << std::endl;
}

Brain::Brain(const Brain &brain) {
  for (int i = 0; i < 100; i++) {
    ideas[i] = brain.ideas[i];
  }
  std::cout << "Brain copy constructor" << std::endl;
}

Brain &Brain::operator=(const Brain &other) {
  if (this != &other) {
    for (int i = 0; i < 100; i++) {
      ideas[i] = other.ideas[i];
    }
    std::cout << "Brain assignment operator" << std::endl;
  }
  return *this;
}

Brain::~Brain() {
  std::cout << "Brain destructor" << std::endl;
}

std::string Brain::getIdea(unsigned int index) const {
  return ideas[index];
}

void Brain::setIdea(std::string idea, unsigned int index) {
  ideas[index] = idea;
}
