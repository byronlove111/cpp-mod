#include "ClapTrap.hpp"
#include <iostream>
#include <string>

ClapTrap::ClapTrap() : _name(""), _hitPoints(10), _energyPoints(10),
                       _attackDamage(0) {
  std::cout << "ClapTrap " << _name << " constructed!" << '\n';
}

ClapTrap::ClapTrap(const std::string &name) : _name(name),
                                              _hitPoints(10), _energyPoints(10),
                                              _attackDamage(0) {
  std::cout << "ClapTrap " << _name << " constructed!" << '\n';
}

ClapTrap::ClapTrap(const ClapTrap &other) : _name(other._name),
                                            _hitPoints(other._hitPoints), _energyPoints(other._energyPoints),
                                            _attackDamage(other._attackDamage) {
  std::cout << "ClapTrap " << _name << " copy constructed!" << '\n';
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
  if (this != &other) {
    _name = other._name;
    _hitPoints = other._hitPoints;
    _energyPoints = other._energyPoints;
    _attackDamage = other._attackDamage;
    std::cout << "ClapTrap " << _name << " assigned!" << '\n';
  }
  return *this;
}

ClapTrap::~ClapTrap() {
  std::cout << "ClapTrap " << _name << " destructed!" << '\n';
}

void ClapTrap::attack(const std::string &target) {
  if (_hitPoints == 0 || _energyPoints == 0) {
    return;
  }
  std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << '\n';
  _energyPoints--;
}

void ClapTrap::takeDamage(unsigned int amount) {
  if (_hitPoints == 0) {
    return;
  }
  std::cout << "ClapTrap " << _name << " takes " << amount << " points of damage!" << '\n';
  if (amount > _hitPoints) {
    _hitPoints = 0;
    return;
  }
  _hitPoints -= amount;
}

void ClapTrap::beRepaired(unsigned int amount) {
  if (_hitPoints == 0 || _energyPoints == 0) {
    return;
  }
  _hitPoints += amount;
  _energyPoints--;
  std::cout << "ClapTrap " << _name << " is repaired for " << amount << " points!" << '\n';
}
