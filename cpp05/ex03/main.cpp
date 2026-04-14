#include "Bureaucrat.hpp"
#include "Intern.hpp"

int main() {
  Intern someRandomIntern;

  std::cout << "--- makeForm: robotomy request ---" << std::endl;
  AForm *rrf = someRandomIntern.makeForm("robotomy request", "Bender");
  if (rrf) {
    Bureaucrat bob("Bob", 45);
    bob.signForm(*rrf);
    bob.executeForm(*rrf);
    delete rrf;
  }

  std::cout << "\n--- makeForm: shrubbery creation ---" << std::endl;
  AForm *scf = someRandomIntern.makeForm("shrubbery creation", "garden");
  if (scf) {
    Bureaucrat alice("Alice", 137);
    alice.signForm(*scf);
    alice.executeForm(*scf);
    delete scf;
  }

  std::cout << "\n--- makeForm: presidential pardon ---" << std::endl;
  AForm *ppf = someRandomIntern.makeForm("presidential pardon", "Arthur");
  if (ppf) {
    Bureaucrat zaphod("Zaphod", 5);
    zaphod.signForm(*ppf);
    zaphod.executeForm(*ppf);
    delete ppf;
  }

  std::cout << "\n--- makeForm: unknown form ---" << std::endl;
  AForm *unknown = someRandomIntern.makeForm("coffee making", "Bob");
  if (!unknown)
    std::cout << "No form created." << std::endl;

  return 0;
}
