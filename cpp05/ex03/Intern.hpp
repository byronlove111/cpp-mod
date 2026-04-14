#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include <string>

class Intern {
  public:
  Intern();
  ~Intern();
  Intern(const Intern &other);
  Intern &operator=(const Intern &other);

  AForm *makeForm(std::string const &formName, std::string const &target);
};

#endif
