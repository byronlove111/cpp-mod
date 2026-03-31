#include "Shape.hpp"
#include <iostream>

Shape::Shape() : _type("Default") {
  std::cout << "Contructor Shape Called" << std::endl;
};

Shape::Shape(std::string type) : _type(type) {
  std::cout << "Contructor Shape Called" << std::endl;
};

Shape::Shape(const Shape &other) : _type(other._type) {
  std::cout << "Copy Contructor Shape Called" << std::endl;
}

Shape &Shape::operator=(const Shape &other) {
  if (this != &other) {
    _type = other._type;
    std::cout << "Overload opeator= Shape Called" << std::endl;
  }
  return *this;
}

Shape::~Shape() {
  std::cout << "Destructor Shape Called" << std::endl;
}

std::string Shape::getType() const {
  return _type;
}

float Shape::getArea() const {
  return 0.0;
}
