CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = Phonebook
SRCS = contact.cpp phonebook.cpp main.cpp commands.cpp

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
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
