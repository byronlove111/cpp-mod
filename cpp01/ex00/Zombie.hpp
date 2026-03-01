#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
private:
  std::string name;

public:
  void announce(void);
  std::string getName();
  void setName(std::string new_name);
  ~Zombie();
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);

#endif
