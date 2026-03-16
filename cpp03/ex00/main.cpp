#include "ClapTrap.hpp"
#include <iostream>

static void printSeparator(const std::string &title) {
  std::cout << "\n--- " << title << " ---\n";
}

int main(void) {

  printSeparator("Construction");
  ClapTrap a("Alpha");

  printSeparator("Attack and takeDamage");
  a.attack("Beta");
  a.takeDamage(5);

  printSeparator("beRepaired");
  a.beRepaired(3);

  printSeparator("Edge case: runs out of HP");
  a.takeDamage(9999);
  a.attack("Beta");
  a.beRepaired(10);

  printSeparator("Edge case: drains all energy (10 points)");
  {
    ClapTrap b("Beta");
    for (int i = 0; i < 12; i++)
      b.attack("target");
    b.beRepaired(5);
  }

  printSeparator("Copy constructor");
  ClapTrap original("Original");
  ClapTrap copy(original);
  copy.attack("Target-C");

  printSeparator("Assignment operator");
  ClapTrap assigned("Assigned");
  assigned = original;
  assigned.attack("Target-D");

  printSeparator("Destruction");
  return 0;
}
