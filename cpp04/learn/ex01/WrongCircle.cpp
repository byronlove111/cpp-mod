#include "WrongCircle.hpp"
#include <iostream>

WrongCircle::WrongCircle(float radius) : WrongShape("Circle"), _radius(radius) {
  std::cout << "Constructor Circle Called" << std::endl;
};

WrongCircle::WrongCircle(const WrongCircle &other) : WrongShape(other), _radius(other._radius) {
  std::cout << "Copy Constructor Circle Called" << std::endl;
}

WrongCircle &WrongCircle::operator=(const WrongCircle &other) {
  if (this != &other) {
    WrongShape::operator=(other);
    _radius = other._radius;
    std::cout << "Overload opeator= Circle Called" << std::endl;
  }
  return *this;
}

WrongCircle::~WrongCircle() {
  std::cout << "Destructor Circle Called" << std::endl;
}

float WrongCircle::getArea() const {
  return 3.14159f * _radius * _radius;
}
