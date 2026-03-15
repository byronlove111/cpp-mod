#include "ClapTrap.hpp"
#include <iostream>

int main(void) {
  std::cout << "--- Construction ---" << '\n';
  ClapTrap a("Alpha");

  std::cout << "\n--- Attack ---" << '\n';
  a.attack("enemy");

  std::cout << "\n--- TakeDamage (normal) ---" << '\n';
  a.takeDamage(5);

  std::cout << "\n--- BeRepaired ---" << '\n';
  a.beRepaired(3);

  std::cout << "\n--- TakeDamage (overkill) ---" << '\n';
  a.takeDamage(9999);

  std::cout << "\n--- Actions with 0 HP (nothing should happen) ---" << '\n';
  a.attack("enemy");
  a.beRepaired(10);

  std::cout << "\n--- Energy drain ---" << '\n';
  ClapTrap b("Beta");
  for (int i = 0; i < 11; i++)
    b.attack("target");

  std::cout << "\n--- Destruction ---" << '\n';
  return 0;
}
