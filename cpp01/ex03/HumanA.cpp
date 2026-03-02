#include "HumanA.hpp"
#include "Weapon.hpp"
#include <iostream>

// initialize weapon reference in initializer list (references must be
// initialized at construction, cannot be assigned later)
HumanA::HumanA(Weapon &weapon_input, std::string name_input)
    : weapon(weapon_input) {
  name = name_input;
}

void HumanA::attack() {
  std::cout << name << " attacks with their " << weapon.getType() << '\n';
}
