#include "Shape.hpp"

class Rectangle : public Shape {
  protected:
  float _width;
  float _height;

  public:
  Rectangle(float width, float height);
  Rectangle(const Rectangle &other);
  Rectangle &operator=(const Rectangle &other);
  ~Rectangle();

  float getArea() const;
};
