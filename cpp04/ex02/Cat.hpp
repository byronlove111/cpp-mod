#ifndef CAT_HPP
#define CAT_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal {
  private:
  Brain *brain_;

  public:
  Cat();
  Cat(const Cat &cat);
  Cat &operator=(const Cat &other);
  ~Cat();

  void makeSound() const;
  Brain *getBrain();
};

#endif
