#include "WrongShape.hpp"

class WrongCircle : public WrongShape {
  protected:
  float _radius;

  public:
  WrongCircle(float radius);
  WrongCircle(const WrongCircle &other);
  WrongCircle &operator=(const WrongCircle &other);
  ~WrongCircle();

  float getArea() const;
};
