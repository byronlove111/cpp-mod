#include "Bureaucrat.hpp"

int main() {
  std::cout << "--- Valid construction ---" << std::endl;
  try {
    Bureaucrat A("Hollande", 1);
    std::cout << A << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- Grade too high (0) ---" << std::endl;
  try {
    Bureaucrat B("Sarkozy", 0);
    std::cout << B << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- Grade too low (151) ---" << std::endl;
  try {
    Bureaucrat C("Hidalgo", 151);
    std::cout << C << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- decrementGrade normal (1 -> 2) ---" << std::endl;
  try {
    Bureaucrat A("Hollande", 1);
    std::cout << A << std::endl;
    A.decrementGrade();
    std::cout << A << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- incrementGrade normal (2 -> 1) ---" << std::endl;
  try {
    Bureaucrat A("Hollande", 2);
    std::cout << A << std::endl;
    A.incrementGrade();
    std::cout << A << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- incrementGrade at limit (1) ---" << std::endl;
  try {
    Bureaucrat A("Hollande", 1);
    std::cout << A << std::endl;
    A.incrementGrade();
    std::cout << A << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- decrementGrade at limit (150) ---" << std::endl;
  try {
    Bureaucrat A("Hollande", 150);
    std::cout << A << std::endl;
    A.decrementGrade();
    std::cout << A << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
