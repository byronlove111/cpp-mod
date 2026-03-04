#include "Fixed.hpp"
#include <iostream>

const int Fixed::fractional_value = 8;

Fixed::Fixed() {
  fixed_point_value = 0;
  std::cout << "Default constructor called" << '\n';
}

Fixed::Fixed(const Fixed &other) {
  fixed_point_value = other.fixed_point_value;
  std::cout << "Copy constructor called" << '\n';
}

Fixed &Fixed::operator=(const Fixed &other) {
  if (this != &other) {
    this->fixed_point_value = other.fixed_point_value;
    std::cout << "Copy assignment operator called" << '\n';
  }
  return *this;
}

Fixed::~Fixed() { std::cout << "Destructor called" << '\n'; }

int Fixed::getRawBits() const {
  std::cout << "getRawBits member function called" << '\n';
  return fixed_point_value;
}

void Fixed::setRawBits(int bits) { fixed_point_value = bits; }
