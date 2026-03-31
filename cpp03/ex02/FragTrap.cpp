#include "FragTrap.hpp"
#include <iostream>
#include <string>

FragTrap::FragTrap() : ClapTrap() {
  _hitPoints = 100;
  _energyPoints = 100;
  _attackDamage = 30;
  std::cout << "FragTrap " << _name << " constructed!" << '\n';
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
  _hitPoints = 100;
  _energyPoints = 100;
  _attackDamage = 30;
  std::cout << "FragTrap " << _name << " constructed!" << '\n';
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other) {
  std::cout << "FragTrap " << _name << " copy constructed!" << '\n';
}

FragTrap &FragTrap::operator=(const FragTrap &other) {
  if (this != &other) {
    ClapTrap::operator=(other);
    std::cout << "FragTrap " << _name << " assigned!" << '\n';
  }
  return *this;
}

FragTrap::~FragTrap() {
  std::cout << "FragTrap " << _name << " destructed!" << '\n';
}

void FragTrap::attack(const std::string &target) {
  if (_hitPoints == 0) {
    std::cout << "FragTrap " << _name << " is dead and cannot attack!\n";
    return;
  }
  if (_energyPoints == 0) {
    std::cout << "FragTrap " << _name << " has no energy to attack!\n";
    return;
  }
  std::cout << "FragTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << '\n';
  _energyPoints--;
}

void FragTrap::highFivesGuys(void) {
  std::cout << "FragTrap " << _name << " wants to high five everyone!" << '\n';
}
