#include <fstream>
#include <iostream>
#include <string>

int main(int ac, char *av[]) {

  if (ac != 4) {
    std::cout << "Usage: " << av[0] << " <filename> <s1> <s2>" << '\n';
    std::cout << "  filename: file to read" << '\n';
    std::cout << "  s1: string to replace" << '\n';
    std::cout << "  s2: replacement string" << '\n';
    return (1);
  }

  std::string filename = av[1];
  std::ifstream raw_file(filename);
  std::ofstream replace_file(filename + ".replace");
  std::string s1 = av[2];
  std::string s2 = av[3];

  if (!raw_file) {
    std::cout << "Error : Unable to open file1: " << av[1] << '\n';
  }
  if (s1.empty()) {
    std::cout << "Error : s1 is empty" << '\n';
  }
  if (s2.empty()) {
    std::cout << "Error : s2 is empty" << '\n';
  }

  return (0);
}
