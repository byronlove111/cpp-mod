#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

static void printSeparator(const std::string &title) {
  std::cout << "\n--- " << title << " ---\n";
}

int main(void) {

  printSeparator("Construction chain: ScavTrap builds ClapTrap first");
  ScavTrap scav("Scav-1");

  printSeparator("ScavTrap attack (overridden)");
  scav.attack("Target-A");

  printSeparator("guardGate special ability");
  scav.guardGate();

  printSeparator("takeDamage and beRepaired");
  scav.takeDamage(30);
  scav.beRepaired(10);

  printSeparator("ClapTrap alone (base stats: 10 HP, 10 EP, 0 dmg)");
  ClapTrap clap("Clap-1");
  clap.attack("Target-B");
  clap.takeDamage(5);
  clap.beRepaired(3);

  printSeparator("Edge case: ScavTrap runs out of HP");
  {
    ScavTrap dying("Dying");
    dying.takeDamage(200);
    dying.attack("Ghost");
    dying.beRepaired(50);
    dying.guardGate();
  }

  printSeparator("Edge case: ClapTrap drains all energy (10 points)");
  {
    ClapTrap exhausted("Tired");
    for (int i = 0; i < 12; i++)
      exhausted.attack("Dummy");
    exhausted.beRepaired(5);
  }

  printSeparator("Copy constructor");
  ScavTrap original("Original");
  ScavTrap copy(original);
  copy.attack("Target-C");

  printSeparator("Assignment operator");
  ScavTrap assigned("Assigned");
  assigned = original;
  assigned.attack("Target-D");

  printSeparator("Destruction chain: ScavTrap destructs first, then ClapTrap");
  return 0;
}
