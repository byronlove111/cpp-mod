#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
  std::cout << "--- ShrubberyCreationForm: success ---" << std::endl;
  try {
    Bureaucrat bob("Bob", 137);
    ShrubberyCreationForm f("home");
    bob.signForm(f);
    bob.executeForm(f);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- ShrubberyCreationForm: execute without signing ---" << std::endl;
  try {
    Bureaucrat bob("Bob", 137);
    ShrubberyCreationForm f("home");
    bob.executeForm(f);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- ShrubberyCreationForm: grade too low to execute ---" << std::endl;
  try {
    Bureaucrat bob("Bob", 137);
    Bureaucrat alice("Alice", 138);
    ShrubberyCreationForm f("home");
    bob.signForm(f);
    alice.executeForm(f);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- RobotomyRequestForm: success ---" << std::endl;
  try {
    Bureaucrat bob("Bob", 45);
    RobotomyRequestForm f("Marvin");
    bob.signForm(f);
    bob.executeForm(f);
    bob.executeForm(f);
    bob.executeForm(f);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- PresidentialPardonForm: success ---" << std::endl;
  try {
    Bureaucrat bob("Bob", 5);
    PresidentialPardonForm f("Arthur");
    bob.signForm(f);
    bob.executeForm(f);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "\n--- PresidentialPardonForm: grade too low to sign ---" << std::endl;
  try {
    Bureaucrat bob("Bob", 26);
    PresidentialPardonForm f("Arthur");
    bob.signForm(f);
    bob.executeForm(f);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
