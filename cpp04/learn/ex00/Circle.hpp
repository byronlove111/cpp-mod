#include "Shape.hpp"

class Circle : public Shape {
  protected:
  float _radius;

  public:
  Circle(float radius);
  Circle(const Circle &other);
  Circle &operator=(const Circle &other);
  ~Circle();

  float getArea() const;
};
