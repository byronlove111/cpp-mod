#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

static void printSeparator(const std::string &title) {
  std::cout << "\n=== " << title << " ===" << std::endl;
}

int main() {
  printSeparator("AAnimal est abstraite — ne compile pas");
  {
    // const AAnimal *a = new AAnimal(); // ERREUR: AAnimal est abstraite
    const AAnimal *j = new Dog();
    const AAnimal *i = new Cat();

    std::cout << "Type de j: " << j->getType() << std::endl;
    std::cout << "Type de i: " << i->getType() << std::endl;
    i->makeSound();
    j->makeSound();

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
    wc->makeSound();

    delete wa;
    delete wc;
  }

  printSeparator("Tableau d'animaux");
  {
    AAnimal *table[10];
    for (int i = 0; i < 5; i++)
      table[i] = new Dog();
    for (int i = 5; i < 10; i++)
      table[i] = new Cat();
    for (int i = 0; i < 10; i++)
      delete table[i];
  }

  printSeparator("Deep copy");
  {
    Dog myDog;
    myDog.getBrain()->setIdea("Je veux manger", 0);
    Dog secondDog(myDog);
    secondDog.getBrain()->setIdea("Je veux boire", 0);
    std::cout << "First dog idea : " << myDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "Second dog idea : " << secondDog.getBrain()->getIdea(0) << std::endl;
  }

  return 0;
}
