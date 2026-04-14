#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45), _target("") {
}

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("RobotomyRequestForm", 72, 45), _target(target) {
}

RobotomyRequestForm::~RobotomyRequestForm() {
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(other), _target(other._target) {
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
  if (this != &other) {
    AForm::operator=(other);
    _target = other._target;
  }
  return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
  checkExecute(executor);
  std::cout << "DRRRRRR..." << std::endl;
  if (std::rand() % 2)
    std::cout << _target << " has been robotomized" << std::endl;
  else
    std::cout << _target << " robotomization failed" << std::endl;
}
