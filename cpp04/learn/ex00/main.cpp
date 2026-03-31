#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Shape.hpp"
#include <iostream>

int main(void) {
  Circle a(0.4);
  Shape b;
  Rectangle c(0.4, 1.7);

  std::cout << "Circle Area : " << a.getArea() << std::endl;
  std::cout << "Shape Area: " << b.getArea() << std::endl;
  std::cout << "Rectangle Area: " << c.getArea() << std::endl;
  std::cout << "Circle Type: " << a.getType() << std::endl;
  std::cout << "Shape Type: " << b.getType() << std::endl;
  std::cout << "Rectangle Area: " << c.getType() << std::endl;
}
