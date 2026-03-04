#include "Fixed.hpp"
#include <iostream>

const int Fixed::fractional_value = 8;

Fixed::Fixed() {
  bits_value = 0;
  std::cout << "Default constructor called" << '\n';
}

Fixed::Fixed(const Fixed &other) {
  bits_value = other.bits_value;
  std::cout << "Copy constructor called" << '\n';
}

Fixed &Fixed::operator=(const Fixed &other) {
  if (this != &other) {
    this->bits_value = other.bits_value;
    std::cout << "Copy assignment operator called" << '\n';
  }
  return *this;
}

Fixed::~Fixed() { std::cout << "Destructor called" << '\n'; }

int Fixed::getRawBits() const {
  std::cout << "getRawBits member function called" << '\n';
  return bits_value;
}

void Fixed::setRawBits(int bits) { bits_value = bits; }
