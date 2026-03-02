#include "HumanB.hpp"
#include <iostream>
#include <string>

HumanB::HumanB(std::string name_input) : weapon(NULL) { name = name_input; }

void HumanB::setWeapon(Weapon &weapon_input) { weapon = &weapon_input; }

void HumanB::attack() {
  if (weapon) {
    std::cout << name << " attacks with their " << weapon->getType() << '\n';
  } else {
    std::cout << name << " don't have weapons" << '\n';
  }
}
