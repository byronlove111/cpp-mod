#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
private:
  int bits_value;
  const static int fractional_value;

public:
  Fixed();
  Fixed(const Fixed &other);
  Fixed &operator=(const Fixed &other);
  ~Fixed();
  int getRawBits() const;
  void setRawBits(int bits);
};

#endif
