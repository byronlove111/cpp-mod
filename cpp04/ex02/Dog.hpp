#ifndef DOG_HPP
#define DOG_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal {
  private:
  Brain *brain_;

  public:
  Dog();
  Dog(const Dog &dog);
  Dog &operator=(const Dog &other);
  ~Dog();

  void makeSound() const;
  Brain *getBrain();
};

#endif
