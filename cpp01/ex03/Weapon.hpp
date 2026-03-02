#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
private:
  std::string type;

public:
  Weapon(std::string type_input);
  const std::string &getType();
  void setType(std::string t);
};

#endif
