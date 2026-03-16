#include "ScavTrap.hpp"
#include "ClapTrap.hpp"
#include <iostream>
#include <string>

ScavTrap::ScavTrap() : ClapTrap() {
  _hitPoints = 100;
  _energyPoints = 50;
  _attackDamage = 20;
  std::cout << "ScavTrap constructed !" << '\n';
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
  _hitPoints = 100;
  _energyPoints = 50;
  _attackDamage = 20;
  std::cout << "ScavTrap constructed !" << '\n';
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other) {
  std::cout << "ScavTrap copy constructed !" << '\n';
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other) {
  if (this != &other) {
    ClapTrap::operator=(other);
    std::cout << "ScavTrap assigned !" << '\n';
  }
  return *this;
}

ScavTrap::~ScavTrap() {
  std::cout << "ScavTrap destructed !" << '\n';
}

void ScavTrap::attack(const std::string &target) {
  if (_hitPoints == 0) {
    std::cout << "ScavTrap " << _name << " is dead and cannot attack!\n";
    return;
  }
  if (_energyPoints == 0) {
    std::cout << "ScavTrap " << _name << " has no energy to attack!\n";
    return;
  }
  std::cout << "ScavTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << '\n';
  _energyPoints--;
}

void ScavTrap::guardGate() {
  std::cout << "ScavTrap " << _name << " is now in Gate keeper mode!" << '\n';
}
