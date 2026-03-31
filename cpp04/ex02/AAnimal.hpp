#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <string>

class AAnimal {
  protected:
  std::string type;

  public:
  AAnimal();
  AAnimal(std::string type);
  AAnimal(const AAnimal &animal);
  AAnimal &operator=(const AAnimal &other);
  virtual ~AAnimal();

  virtual std::string getType() const;
  virtual void makeSound() const = 0;
};

#endif
