#ifndef WRONGSHAPE_HPP
#define WRONGSHAPE_HPP

#include <string>

class WrongShape {
  protected:
  std::string _type;

  public:
  WrongShape();
  WrongShape(std::string type);
  WrongShape(const WrongShape &other);
  WrongShape &operator=(const WrongShape &other);
  ~WrongShape();
  std::string getType() const;
  float getArea() const;
};
#endif
