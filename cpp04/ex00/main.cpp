#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

static void printSeparator(const std::string &title) {
  std::cout << "\n=== " << title << " ===" << std::endl;
}

int main() {
  printSeparator("Test du sujet (polymorphisme via pointeur Animal*)");
  {
    const Animal *meta = new Animal();
    const Animal *j = new Dog();
    const Animal *i = new Cat();

    std::cout << "Type de j: " << j->getType() << std::endl;
    std::cout << "Type de i: " << i->getType() << std::endl;
    i->makeSound();
    j->makeSound();
    meta->makeSound();

    delete meta;
    delete j;
    delete i;
  }

  printSeparator("Constructeur de copie");
  {
    Dog dog1;
    Dog dog2(dog1);
    dog2.makeSound();

    Cat cat1;
    Cat cat2(cat1);
    cat2.makeSound();
  }

  printSeparator("Operateur d'assignation");
  {
    Dog dog1;
    Dog dog2;
    dog2 = dog1;
    dog2.makeSound();

    Cat cat1;
    Cat cat2;
    cat2 = cat1;
    cat2.makeSound();
  }

  printSeparator("Appel direct (pas via pointeur de base)");
  {
    Dog dog;
    Cat cat;
    dog.makeSound();
    cat.makeSound();
    std::cout << "Type dog: " << dog.getType() << std::endl;
    std::cout << "Type cat: " << cat.getType() << std::endl;
  }

  printSeparator("WrongAnimal/WrongCat — SANS virtual (mauvais comportement)");
  {
    const WrongAnimal *wa = new WrongAnimal();
    const WrongAnimal *wc = new WrongCat();

    std::cout << "Type wa: " << wa->getType() << std::endl;
    std::cout << "Type wc: " << wc->getType() << std::endl;
    wa->makeSound();
    wc->makeSound(); // affiche le son de WrongAnimal, pas de WrongCat !

    delete wa;
    delete wc;
  }

  printSeparator("Destructeurs (verification ordre)");
  {
    Animal *animals[4];
    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Dog();
    animals[3] = new Cat();
    for (int i = 0; i < 4; i++)
      delete animals[i];
  }

  return 0;
}
