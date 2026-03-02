#include "Weapon.hpp"
#include <string>

Weapon::Weapon(std::string type_input) { type = type_input; }
const std::string &Weapon::getType() { return type; }
void Weapon::setType(std::string t) { type = t; }
