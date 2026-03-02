#ifndef HUMANA_HPP
#define HUMANA_HPP
#include "Weapon.hpp"
#include <string>

class HumanA {
private:
  Weapon &weapon;
  std::string name;

public:
  HumanA(Weapon &weapon_input, std::string name_input);
  void attack();
};

#endif
