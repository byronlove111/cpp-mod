#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
  std::cout << "--- Valid form ---" << std::endl;
  try {
    Form A("Declaration A", 50, 25);
    std::cout << A << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- Form grade too high (0) ---" << std::endl;
  try {
    Form B("Bad Form", 0, 25);
    std::cout << B << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- Form grade too low (151) ---" << std::endl;
  try {
    Form C("Bad Form", 151, 25);
    std::cout << C << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- Successful signature ---" << std::endl;
  try {
    Bureaucrat bob("Bob", 10);
    Form f("TaxForm", 50, 25);
    std::cout << f << std::endl;
    bob.signForm(f);
    std::cout << f << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- Failed signature ---" << std::endl;
  try {
    Bureaucrat alice("Alice", 100);
    Form f("TaxForm", 50, 25);
    alice.signForm(f);
    std::cout << f << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
