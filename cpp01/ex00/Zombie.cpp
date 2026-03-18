#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string name) : name(name) {}

void Zombie::announce(void) {
  std::cout << name << ": BraiiiiiiinnnzzzZ..." << '\n';
}

Zombie::~Zombie() { std::cout << name << " is dead..." << '\n'; }
