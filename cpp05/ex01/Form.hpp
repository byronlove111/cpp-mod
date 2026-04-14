#ifndef FORM_HPP
#define FORM_HPP

#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

class Form {

  private:
  const std::string _name;
  bool _isSigned;
  const int _gradeToSign;
  const int _gradeToExecute;

  public:
  Form();
  Form(std::string name, int gradeToSign, int gradeToExecute);
  ~Form();
  Form(const Form &other);
  Form &operator=(const Form &other);

  class GradeTooHighException : public std::exception {
    virtual const char *what() const throw();
  };

  class GradeTooLowException : public std::exception {
    virtual const char *what() const throw();
  };

  std::string getName() const;
  bool getIsSigned() const;
  int getGradeToSign() const;
  int getGradeToExecute() const;
  void beSigned(const Bureaucrat &b);
};

std::ostream &operator<<(std::ostream &os, const Form &f);

#endif
