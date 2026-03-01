#include <iostream>
#include <string>

class Zombie {
private:
  std::string name;

public:
  void announce(void);
  std::string getName();
  void setName(std::string new_name);
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);
