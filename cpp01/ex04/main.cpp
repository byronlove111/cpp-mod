#include <fstream>
#include <iostream>
#include <string>

static void replace_str(std::string &line, std::string str_to_replace,
                        std::string new_str) {
  size_t pos = line.find(str_to_replace);
  while (pos != std::string::npos) {
    pos = line.find(str_to_replace, pos + new_str.size());
  }
}

int main(int ac, char *av[]) {

  if (ac != 4) {
    std::cout << "Usage: " << av[0] << " <filename> <s1> <s2>" << '\n';
    std::cout << "  filename: file to read" << '\n';
    std::cout << "  s1: string to replace" << '\n';
    std::cout << "  s2: replacement string" << '\n';
    return (1);
  }

  std::ifstream raw_file(av[1]);
  std::string replace_name = std::string(av[1]) + ".replace";
  std::ofstream replace_file(replace_name.c_str());
  std::string str_to_replace = av[2];
  std::string new_str = av[3];

  if (!raw_file) {
    std::cout << "Error : Unable to open file1: " << av[1] << '\n';
  }
  if (str_to_replace.empty()) {
    std::cout << "Error : s1 is empty" << '\n';
  }
  if (new_str.empty()) {
    std::cout << "Error : s2 is empty" << '\n';
  }

  std::string line;
  int i = 0;
  while (getline(raw_file, line)) {
    std::cout << "current line : " << line << '\n';
    replace_str(line, str_to_replace, new_str);
    i++;
  }

  return (0);
}
