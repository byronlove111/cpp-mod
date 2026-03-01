#include "Zombie.hpp"

int main() {
  Zombie *zombie = newZombie("Malik");
  zombie->announce();
  randomChump("Noah");
  delete zombie;
}
