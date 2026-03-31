#include "Circle.hpp"
#include <iostream>

Circle::Circle(float radius) : Shape("Circle"), _radius(radius) {
  std::cout << "Constructor Circle Called" << std::endl;
};

Circle::Circle(const Circle &other) : Shape(other), _radius(other._radius) {
  std::cout << "Copy Constructor Circle Called" << std::endl;
}

Circle &Circle::operator=(const Circle &other) {
  if (this != &other) {
    Shape::operator=(other);
    _radius = other._radius;
    std::cout << "Overload opeator= Circle Called" << std::endl;
  }
  return *this;
}

Circle::~Circle() {
  std::cout << "Destructor Circle Called" << std::endl;
}

float Circle::getArea() const {
  return 3.14159f * _radius * _radius;
}
