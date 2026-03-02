#include <fstream>
#include <iostream>
#include <string>

static void replace_str(std::string &line, std::string str_to_replace,
                        std::string new_str) {
  size_t pos = line.find(str_to_replace);
  while (pos != std::string::npos) {
    std::string before = line.substr(0, pos);
    std::string after = line.substr(pos + str_to_replace.size(), line.size());
    line = before + new_str + after;
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
    return (1);
  }
  if (str_to_replace.empty()) {
    std::cout << "Error : s1 is empty" << '\n';
    return (1);
  }
  if (new_str.empty()) {
    std::cout << "Error : s2 is empty" << '\n';
    return (1);
  }

  std::string line;
  while (getline(raw_file, line)) {
    replace_str(line, str_to_replace, new_str);
    replace_file << line << '\n';
  }

  return (0);
}
