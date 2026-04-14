CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = intern

SRCS = main.cpp Bureaucrat.cpp AForm.cpp \
       ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp \
       Intern.cpp

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
