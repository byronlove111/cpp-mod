#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>

class Brain {
  private:
  std::string ideas[100];

  public:
  Brain();
  Brain(const Brain &brain);
  Brain &operator=(const Brain &other);
  ~Brain();
  std::string getIdea(unsigned int index) const;
  void setIdea(std::string idea, unsigned int index);
};

#endif
