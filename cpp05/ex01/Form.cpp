#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name(""), _isSigned(false), _gradeToSign(1), _gradeToExecute(1) {
}

Form::Form(std::string name, int gradeToSign, int gradeToExecute) : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
  if (gradeToSign < 1 || gradeToExecute < 1)
    throw GradeTooHighException();
  if (gradeToSign > 150 || gradeToExecute > 150)
    throw GradeTooLowException();
}

Form::~Form() {
  std::cout << "Destructor called" << std::endl;
}

Form::Form(const Form &other) : _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
}

Form &Form::operator=(const Form &other) {
  if (this != &other) {
    _isSigned = other._isSigned;
  }
  return *this;
}

const char *Form::GradeTooHighException::what() const throw() {
  return "Grade too high";
}

const char *Form::GradeTooLowException::what() const throw() {
  return "Grade too low";
}

std::string Form::getName() const {
  return this->_name;
}

bool Form::getIsSigned() const {
  return this->_isSigned;
}

int Form::getGradeToSign() const {
  return this->_gradeToSign;
}

int Form::getGradeToExecute() const {
  return this->_gradeToExecute;
}

void Form::beSigned(const Bureaucrat &b) {
  if (b.getGrade() > this->_gradeToSign) {
    throw GradeTooLowException();
  }
  this->_isSigned = true;
}

std::ostream &operator<<(std::ostream &os, const Form &f) {
  os << f.getName() << ", ";
  os << "form grade to sign " << f.getGradeToSign() << ", ";
  os << "grade to execute " << f.getGradeToExecute() << ", ";
  os << "signed: " << (f.getIsSigned() ? "yes" : "no");
  return os;
}
