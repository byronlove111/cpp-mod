#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
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
