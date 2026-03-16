#include "FragTrap.hpp"
#include <iostream>

static void printSeparator(const std::string &title) {
  std::cout << "\n--- " << title << " ---\n";
}

int main(void) {

  printSeparator("Construction chain: ClapTrap first, FragTrap second");
  FragTrap frag("Frag-1");

  printSeparator("FragTrap attack (overridden)");
  frag.attack("Target-A");

  printSeparator("highFivesGuys special ability");
  frag.highFivesGuys();

  printSeparator("takeDamage and beRepaired");
  frag.takeDamage(50);
  frag.beRepaired(20);

  printSeparator("Edge case: FragTrap runs out of HP");
  {
    FragTrap dying("Dying");
    dying.takeDamage(200);
    dying.attack("Ghost");
    dying.beRepaired(50);
    dying.highFivesGuys();
  }

  printSeparator("Edge case: FragTrap drains all energy (100 points)");
  {
    FragTrap exhausted("Tired");
    for (int i = 0; i < 102; i++)
      exhausted.attack("Dummy");
    exhausted.beRepaired(5);
  }

  printSeparator("Copy constructor");
  FragTrap original("Original");
  FragTrap copy(original);
  copy.attack("Target-B");

  printSeparator("Assignment operator");
  FragTrap assigned("Assigned");
  assigned = original;
  assigned.attack("Target-C");

  printSeparator("Destruction chain: FragTrap first, ClapTrap last");
  return 0;
}
