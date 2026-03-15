#include "Fixed.hpp"
#include <cmath>
#include <iostream>

const int Fixed::fractional_value = 8;

Fixed::Fixed() {
  fixed_point_value = 0;
  std::cout << "Default constructor called" << '\n';
}

Fixed::Fixed(const int n) {
  fixed_point_value = n << fractional_value;
  std::cout << "Int constructor called" << '\n';
}

Fixed::Fixed(const float n) {
  fixed_point_value = roundf(n * (1 << fractional_value));
  std::cout << "Float constructor called" << '\n';
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

bool Fixed::operator>(const Fixed &other) const {
  return fixed_point_value > other.fixed_point_value;
}
bool Fixed::operator<(const Fixed &other) const {
  return fixed_point_value < other.fixed_point_value;
}
bool Fixed::operator>=(const Fixed &other) const {
  return fixed_point_value >= other.fixed_point_value;
}
bool Fixed::operator<=(const Fixed &other) const {
  return fixed_point_value <= other.fixed_point_value;
}
bool Fixed::operator==(const Fixed &other) const {
  return fixed_point_value == other.fixed_point_value;
}
bool Fixed::operator!=(const Fixed &other) const {
  return fixed_point_value != other.fixed_point_value;
}

Fixed &Fixed::operator++() {
  ++fixed_point_value;
  return *this;
}

Fixed Fixed::operator++(int) {
  Fixed tmp(*this);
  ++fixed_point_value;
  return tmp;
}

Fixed &Fixed::operator--() {
  --fixed_point_value;
  return *this;
}

Fixed Fixed::operator--(int) {
  Fixed tmp(*this);
  --fixed_point_value;
  return tmp;
}

Fixed Fixed::operator+(const Fixed &other) const {
  Fixed result;
  result.fixed_point_value = fixed_point_value + other.fixed_point_value;
  return result;
}
Fixed Fixed::operator-(const Fixed &other) const {
  Fixed result;
  result.fixed_point_value = fixed_point_value - other.fixed_point_value;
  return result;
}

// la multiplication de deux fixed-point ne peut pas etre faite directement sur
// les raw car chaque raw contien deja le facteur 2^8, donc le produit aurait
// 2^16 bits fractinonaires on cast en long pour eviter l'overflow puis on
// redecale de 8 bits pour revnir a 2^8
Fixed Fixed::operator*(const Fixed &other) const {
  Fixed result;
  result.fixed_point_value =
      ((long)fixed_point_value * other.fixed_point_value) >> fractional_value;
  return result;
}

// a l'inverse de la multipication, la division necessite de decaler a gauche
// AVANT de diviser sinon on perd les bits fractinonaires (la division de deux
// raw donnerai un entier sans partie decimale)
Fixed Fixed::operator/(const Fixed &other) const {
  Fixed result;
  result.fixed_point_value =
      ((long)fixed_point_value << fractional_value) / other.fixed_point_value;
  return result;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
  return a < b ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
  return a < b ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
  return a > b ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
  return a > b ? a : b;
}

Fixed::~Fixed() { std::cout << "Destructor called" << '\n'; }

int Fixed::getRawBits() const {
  std::cout << "getRawBits member function called" << '\n';
  return fixed_point_value;
}

void Fixed::setRawBits(int bits) { fixed_point_value = bits; }

float Fixed::toFloat(void) const {
  return (float)fixed_point_value / (1 << fractional_value);
}

int Fixed::toInt(void) const { return fixed_point_value >> fractional_value; }

std::ostream &operator<<(std::ostream &out, const Fixed &other) {
  out << other.toFloat();
  return out;
}
