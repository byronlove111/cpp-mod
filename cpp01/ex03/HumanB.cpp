#include "HumanB.hpp"
#include <iostream>
#include <string>

HumanB::HumanB(std::string name_input) { name = name_input; }

void HumanB::setWeapon(Weapon &weapon_input) { weapon = &weapon_input; }

void HumanB::attack() {
  std::cout << name << " attacks with their " << weapon->getType() << '\n';
}
