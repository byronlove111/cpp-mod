#include <cctype>
#include <iostream>

int main(int ac, char **av) {
  if (ac >= 2) {
    for (int i = 1; i < ac; i++) {
      for (int j = 0; av[i][j] != '\0'; j++) {
        if (isspace(av[i][j])) {
          std::cout << av[i][j];
        } else {
          char c = toupper(av[i][j]);
          std::cout << c;
        }
      }
    }
  } else {
    std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
  }
  std::cout << '\n';
  return (0);
}
