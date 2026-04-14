#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <stdexcept>
#include <string>

class AForm;

class Bureaucrat {
  private:
  const std::string _name;
  int _grade;

  public:
  Bureaucrat();
  Bureaucrat(std::string name, int grade);
  ~Bureaucrat();
  Bureaucrat(const Bureaucrat &other);
  Bureaucrat &operator=(const Bureaucrat &other);

  class GradeTooHighException : public std::exception {
    virtual const char *what() const throw();
  };

  class GradeTooLowException : public std::exception {
    virtual const char *what() const throw();
  };

  std::string getName() const;
  int getGrade() const;
  void incrementGrade();
  void decrementGrade();
  void signForm(AForm &f);
  void executeForm(AForm const &f);
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &b);

#endif
