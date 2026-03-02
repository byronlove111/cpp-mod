CXX = c++
FLAGS = -Werror -Wextra -Wall -std=c++98

SRCS = HumanA.cpp HumanB.cpp Weapon.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = a.out

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
