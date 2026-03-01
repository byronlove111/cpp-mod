#include "Zombie.hpp"
#include <iostream>

void Zombie::announce(void) {
  std::cout << getName() << ": BraiiiiiiinnnzzzZ..." << '\n';
}

std::string Zombie::getName() { return name; }
void Zombie::setName(std::string new_name) { name = new_name; }
