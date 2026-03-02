#include "Weapon.hpp"
#include <string>

const std::string &Weapon::getType() { return type; }
void Weapon::setType(std::string t) { type = t; }
