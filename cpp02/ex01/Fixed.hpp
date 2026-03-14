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
  ~Fixed();
  int getRawBits() const;
  void setRawBits(int bits);
  float toFloat(void) const;
  int toInt(void) const;
};

std::ostream &operator<<(std::ostream &out, const Fixed &other);

#endif
