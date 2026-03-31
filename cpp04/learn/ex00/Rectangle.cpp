#include "Rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(float width, float height) : Shape("Rectangle"), _width(width), _height(height) {
  std::cout << "Constructor Rectangle Called" << std::endl;
};

Rectangle::Rectangle(const Rectangle &other) : Shape(other), _width(other._width), _height(other._width) {
  std::cout << "Copy Constructor Rectangle Called" << std::endl;
}

Rectangle &Rectangle::operator=(const Rectangle &other) {
  if (this != &other) {
    Shape::operator=(other);
    _width = other._width;
    _height = other._height;
    std::cout << "Overload opeator= Rectangle Called" << std::endl;
  }
  return *this;
}

Rectangle::~Rectangle() {
  std::cout << "Destructor Rectangle Called" << std::endl;
}

float Rectangle::getArea() const {
  return _width * _height;
}
