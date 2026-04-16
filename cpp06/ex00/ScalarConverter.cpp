#include "ScalarConverter.hpp"
#include <cfloat>
#include <cstdlib>
#include <iostream>
#include <iomanip>

ScalarConverter::ScalarConverter() {
}
ScalarConverter::ScalarConverter(const ScalarConverter &) {
}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) {
  return *this;
}
ScalarConverter::~ScalarConverter() {
}

bool ScalarConverter::isChar(const std::string &str) {
  return (str.size() == 1 && std::isprint(str[0]) && !std::isdigit(str[0]));
}

bool ScalarConverter::isInt(const std::string &str) {
  size_t start = 0;
  if (str[0] == '+' || str[0] == '-')
    start = 1;
  if (str.size() == start)
    return false;
  return (str.find_first_not_of("0123456789", start) == std::string::npos);
}

bool ScalarConverter::isFloat(const std::string &str) {
  if (str[str.size() - 1] != 'f')
    return false;

  // cherche le point
  size_t dot = str.find('.');
  if (dot == std::string::npos)
    return false;

  size_t start = 0;
  if (str[0] == '+' || str[0] == '-')
    start = 1;

  // si le point est direct apres le signe (ou en pos 0) ya rien avant → ".2f"
  if (dot == start)
    return false;

  // tout ce qu'il y a entre start et le point doit etre des chiffres
  // si find_first_not_of trouve autre chose que des chiffres avant le point → invalide
  if (str.find_first_not_of("0123456789", start) != dot)
    return false;

  // extrait ce qu'il y a entre le point et le 'f' → la partie decimale
  // dot+1 = apres le point, str.size()-dot-2 = longueur sans compter le point et le f
  const std::string frac = str.substr(dot + 1, str.size() - dot - 2);

  // la partie decimale doit exister et contenir que des chiffres
  return (!frac.empty() && frac.find_first_not_of("0123456789") == std::string::npos);
}

bool ScalarConverter::isDouble(const std::string &str) {
  size_t dot = str.find('.');
  if (dot == std::string::npos)
    return false;
  size_t start = 0;
  if (str[0] == '+' || str[0] == '-')
    start = 1;

  // rien avant le point → invalide
  if (dot == start)
    return false;

  // tout avant le point doit etre des chiffres
  if (str.find_first_not_of("0123456789", start) != dot)
    return false;

  // prend tout apres le point (pas de 'f' a exclure contrairement a isFloat)
  const std::string frac = str.substr(dot + 1);
  return (!frac.empty() && frac.find_first_not_of("0123456789") == std::string::npos);
}

bool ScalarConverter::isPseudoLiteral(const std::string &str) {
  return (str == "-inff" || str == "+inff" || str == "nanf" || str == "-inf" || str == "+inf" || str == "nan");
}

void ScalarConverter::printChar(double val) {
  if (val < 0 || val > 127)
    std::cout << "char: impossible" << std::endl;
  else if (!std::isprint(static_cast<char>(val)))
    std::cout << "char: Non displayable" << std::endl;
  else
    std::cout << "char: '" << static_cast<char>(val) << "'" << std::endl;
}

void ScalarConverter::printInt(double val) {
  if (val < std::numeric_limits<int>::min() || val > std::numeric_limits<int>::max())
    std::cout << "int: impossible" << std::endl;
  else
    std::cout << "int: " << static_cast<int>(val) << std::endl;
}

void ScalarConverter::printFloat(double val) {
  // fixed pour forcer l'affichage decimal et non scientifique
  std::cout << std::fixed << std::setprecision(1);
  std::cout << "float: " << static_cast<float>(val) << "f" << std::endl;
}

void ScalarConverter::printDouble(double val) {
  std::cout << std::fixed << std::setprecision(1);
  std::cout << "double: " << val << std::endl;
}

void ScalarConverter::convertFromChar(const std::string &str) {
  // str[0] c'est le char, on le cast en double pour passer aux print
  double val = static_cast<double>(str[0]);
  printChar(val);
  printInt(val);
  printFloat(val);
  printDouble(val);
}

void ScalarConverter::convertFromInt(const std::string &str) {
  // strtol parse la string en long, on passe en double pour les print
  double val = static_cast<double>(std::strtol(str.c_str(), NULL, 10));
  printChar(val);
  printInt(val);
  printFloat(val);
  printDouble(val);
}

void ScalarConverter::convertFromFloat(const std::string &str) {
  // strtof parse la string en float, on cast en double pour les print
  double val = static_cast<double>(std::strtof(str.c_str(), NULL));
  printChar(val);
  printInt(val);
  printFloat(val);
  printDouble(val);
}

void ScalarConverter::convertFromDouble(const std::string &str) {
  // strtod parse directement en double
  double val = std::strtod(str.c_str(), NULL);
  printChar(val);
  printInt(val);
  printFloat(val);
  printDouble(val);
}

void ScalarConverter::convertFromPseudo(const std::string &str) {
  std::cout << "char: impossible" << std::endl;
  std::cout << "int: impossible" << std::endl;

  if (str == "nanf" || str == "nan")
    std::cout << "float: nanf" << std::endl;
  else if (str == "+inff" || str == "+inf")
    std::cout << "float: +inff" << std::endl;
  else
    std::cout << "float: -inff" << std::endl;

  if (str == "nanf" || str == "nan")
    std::cout << "double: nan" << std::endl;
  else if (str == "+inff" || str == "+inf")
    std::cout << "double: +inf" << std::endl;
  else
    std::cout << "double: -inf" << std::endl;
}

void ScalarConverter::convert(const std::string &str) {
  if (isPseudoLiteral(str))
    convertFromPseudo(str);
  else if (isChar(str))
    convertFromChar(str);
  else if (isInt(str))
    convertFromInt(str);
  else if (isFloat(str))
    convertFromFloat(str);
  else if (isDouble(str))
    convertFromDouble(str);
  else
    std::cout << "Error: unrecognized literal" << std::endl;
}
