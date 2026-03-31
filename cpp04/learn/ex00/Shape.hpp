#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>

class Shape {
  protected:
  std::string _type;

  public:
  Shape();
  Shape(std::string type);
  Shape(const Shape &other);
  Shape &operator=(const Shape &other);
  ~Shape();
  std::string getType() const;
  float getArea() const; // retourne 0.0
};
#endif
