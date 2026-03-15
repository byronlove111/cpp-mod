#ifndef FIXED_HPP
#define FIXED_HPP

#include <ostream>
class Fixed {
private:
  int fixed_point_value;
  const static int fractional_value;

public:
  Fixed();
  Fixed(const int n);
  Fixed(const float n);
  Fixed(const Fixed &other);
  Fixed &operator=(const Fixed &other);
  bool operator>(const Fixed &other) const;
  bool operator<(const Fixed &other) const;
  bool operator>=(const Fixed &other) const;
  bool operator<=(const Fixed &other) const;
  bool operator==(const Fixed &other) const;
  bool operator!=(const Fixed &other) const;
  Fixed &operator++();
  Fixed &operator--();
  Fixed operator++(int);
  Fixed operator--(int);
  Fixed operator+(const Fixed &other) const;
  Fixed operator-(const Fixed &other) const;
  Fixed operator*(const Fixed &other) const;
  Fixed operator/(const Fixed &other) const;
  static Fixed &min(Fixed &a, Fixed &b);
  static const Fixed &min(const Fixed &a, const Fixed &b);
  static Fixed &max(Fixed &a, Fixed &b);
  static const Fixed &max(const Fixed &a, const Fixed &b);
  ~Fixed();
  int getRawBits() const;
  void setRawBits(int bits);
  float toFloat(void) const;
  int toInt(void) const;
};

std::ostream &operator<<(std::ostream &out, const Fixed &other);

#endif
