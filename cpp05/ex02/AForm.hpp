#ifndef AFORM_HPP
#define AFORM_HPP

#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

class AForm {

  private:
  const std::string _name;
  bool _isSigned;
  const int _gradeToSign;
  const int _gradeToExecute;

  protected:
  void checkExecute(Bureaucrat const &executor) const;

  public:
  AForm();
  AForm(std::string name, int gradeToSign, int gradeToExecute);
  virtual ~AForm();
  AForm(const AForm &other);
  AForm &operator=(const AForm &other);

  class GradeTooHighException : public std::exception {
    virtual const char *what() const throw();
  };

  class GradeTooLowException : public std::exception {
    virtual const char *what() const throw();
  };

  class NotSignedException : public std::exception {
    virtual const char *what() const throw();
  };

  std::string getName() const;
  bool getIsSigned() const;
  int getGradeToSign() const;
  int getGradeToExecute() const;
  void beSigned(const Bureaucrat &b);
  virtual void execute(Bureaucrat const &executor) const = 0;
};

std::ostream &operator<<(std::ostream &os, const AForm &f);

#endif
