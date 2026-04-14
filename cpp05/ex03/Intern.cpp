#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern() {}
Intern::~Intern() {}
Intern::Intern(const Intern &other) { (void)other; }
Intern &Intern::operator=(const Intern &other) { (void)other; return *this; }

static AForm *makeShrubbery(std::string const &target) {
  return new ShrubberyCreationForm(target);
}

static AForm *makeRobotomy(std::string const &target) {
  return new RobotomyRequestForm(target);
}

static AForm *makePresidential(std::string const &target) {
  return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(std::string const &formName, std::string const &target) {
  struct FormEntry {
    std::string name;
    AForm *(*create)(std::string const &);
  };

  FormEntry forms[] = {
    {"shrubbery creation", makeShrubbery},
    {"robotomy request",   makeRobotomy},
    {"presidential pardon", makePresidential}
  };

  for (int i = 0; i < 3; i++) {
    if (forms[i].name == formName) {
      std::cout << "Intern creates " << formName << std::endl;
      return forms[i].create(target);
    }
  }

  std::cerr << "Intern: unknown form '" << formName << "'" << std::endl;
  return NULL;
}
