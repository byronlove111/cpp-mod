#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

class ScalarConverter {
  public:
  static void convert(const std::string &str);

  private:
  ScalarConverter();
  ScalarConverter(const ScalarConverter &other);
  ScalarConverter &operator=(const ScalarConverter &other);
  ~ScalarConverter();

  static bool isChar(const std::string &str);
  static bool isInt(const std::string &str);
  static bool isFloat(const std::string &str);
  static bool isDouble(const std::string &str);
  static bool isPseudoLiteral(const std::string &str);

  static void convertFromChar(const std::string &str);
  static void convertFromInt(const std::string &str);
  static void convertFromFloat(const std::string &str);
  static void convertFromDouble(const std::string &str);
  static void convertFromPseudo(const std::string &str);

  static void printChar(double val);
  static void printInt(double val);
  static void printFloat(double val);
  static void printDouble(double val);
};

#endif
