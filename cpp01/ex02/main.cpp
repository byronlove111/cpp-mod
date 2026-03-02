#include <iostream>
#include <string>

int main() {

  std::string str = "HI THIS IS BRAIN";
  std::string *ptr = &str;
  std::string &ref = str;

  std::cout << "Memory address of str: " << &str << '\n';
  std::cout << "Memory address of ptr: " << ptr << '\n';
  std::cout << "Memory address of ref: " << &ref << '\n';

  std::cout << "Value of str: " << str << '\n';
  std::cout << "Value of *ptr: " << *ptr << '\n';
  std::cout << "Value of ref: " << ref << '\n';
}
