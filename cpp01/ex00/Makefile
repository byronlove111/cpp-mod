CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = zombie

SRCS = main.cpp newZombie.cpp Zombie.cpp randomChump.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
