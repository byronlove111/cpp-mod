#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name(""), _isSigned(false), _gradeToSign(1), _gradeToExecute(1) {
}

AForm::AForm(std::string name, int gradeToSign, int gradeToExecute) : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
  if (gradeToSign < 1 || gradeToExecute < 1)
    throw GradeTooHighException();
  if (gradeToSign > 150 || gradeToExecute > 150)
    throw GradeTooLowException();
}

AForm::~AForm() {
  std::cout << "Destructor called" << std::endl;
}

AForm::AForm(const AForm &other) : _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
}

AForm &AForm::operator=(const AForm &other) {
  if (this != &other) {
    _isSigned = other._isSigned;
  }
  return *this;
}

const char *AForm::GradeTooHighException::what() const throw() {
  return "Grade too high";
}

const char *AForm::GradeTooLowException::what() const throw() {
  return "Grade too low";
}

const char *AForm::NotSignedException::what() const throw() {
  return "Form is not signed";
}

std::string AForm::getName() const {
  return this->_name;
}

bool AForm::getIsSigned() const {
  return this->_isSigned;
}

int AForm::getGradeToSign() const {
  return this->_gradeToSign;
}

int AForm::getGradeToExecute() const {
  return this->_gradeToExecute;
}

void AForm::beSigned(const Bureaucrat &b) {
  if (b.getGrade() > this->_gradeToSign) {
    throw GradeTooLowException();
  }
  this->_isSigned = true;
}

void AForm::checkExecute(Bureaucrat const &executor) const {
  if (this->_isSigned == false) {
    throw NotSignedException();
  }
  if (executor.getGrade() > _gradeToExecute) {
    throw GradeTooLowException();
  }
}

std::ostream &operator<<(std::ostream &os, const AForm &f) {
  os << f.getName() << ", ";
  os << "form grade to sign " << f.getGradeToSign() << ", ";
  os << "grade to execute " << f.getGradeToExecute() << ", ";
  os << "signed: " << (f.getIsSigned() ? "yes" : "no");
  return os;
}
