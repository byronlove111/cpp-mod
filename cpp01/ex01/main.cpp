#include "Zombie.hpp"
int main(void) {
  int number_of_zombies = 10;
  Zombie *z = zombieHorde(number_of_zombies, "Malik");
  for (int i = 0; i < number_of_zombies; i++) {
    z[i].announce();
  }
  delete[] z;
}
