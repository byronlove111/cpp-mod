#include "commands.hpp"
#include "phonebook.hpp"
#include <iostream>

static int orchestrate_action(Phonebook &phonebook, std::string arg) {
  if (arg == "ADD") {
    add_contact(phonebook);
    return (1);
  } else if (arg == "SEARCH") {
    phonebook.searchContact();
    return (1);
  } else if (arg == "EXIT") {
    return (0);
  } else {
    return (1);
  }
}

int main(void) {
  Phonebook phonebook;
  while (1) {
    print_commands();
    std::string arg;
    std::getline(std::cin, arg);
    if (!orchestrate_action(phonebook, arg))
      break;
  }
}
