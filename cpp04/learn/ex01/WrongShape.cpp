#include "WrongShape.hpp"
#include <iostream>

WrongShape::WrongShape() : _type("Default") {
  std::cout << "Contructor Shape Called" << std::endl;
};

WrongShape::WrongShape(std::string type) : _type(type) {
  std::cout << "Contructor Shape Called" << std::endl;
};

WrongShape::WrongShape(const WrongShape &other) : _type(other._type) {
  std::cout << "Copy Contructor Shape Called" << std::endl;
}

WrongShape &WrongShape::operator=(const WrongShape &other) {
  if (this != &other) {
    _type = other._type;
    std::cout << "Overload opeator= Shape Called" << std::endl;
  }
  return *this;
}

WrongShape::~WrongShape() {
  std::cout << "Destructor Shape Called" << std::endl;
}

std::string WrongShape::getType() const {
  return _type;
}

float WrongShape::getArea() const {
  return 0.0;
}
