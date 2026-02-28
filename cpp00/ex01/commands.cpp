#include "phonebook.hpp"
#include <iostream>
#include <string>

struct ContactInfo {
  std::string firstName;
  std::string lastName;
  std::string nickName;
  std::string phoneNumber;
  std::string darkestSecret;
};

static std::string readField(const std::string &message) {
  std::string field;
  while (field.empty()) {
    std::cout << message;
    std::getline(std::cin, field);
    if (field.empty()) {
      std::cout << "Field cannot be empty." << '\n';
    }
  }
  return field;
}

void print_commands() {
  std::cout << '\n';
  std::cout << "--- PHONEBOOK ---" << '\n';
  std::cout << '\n';
  std::cout << "Available commands:" << '\n';
  std::cout << '\n';
  std::cout << "  ADD    : Save a new contact" << '\n';
  std::cout << "  SEARCH : Display saved contacts" << '\n';
  std::cout << "  EXIT   : Quit the phonebook" << '\n';
  std::cout << '\n';
}

void add_contact(Phonebook &phonebook) {
  ContactInfo contact;
  contact.firstName = readField("First Name : ");
  contact.lastName = readField("Last Name : ");
  contact.nickName = readField("Nickname : ");
  contact.phoneNumber = readField("Phone Number : ");
  contact.darkestSecret = readField("Darkest Secret : ");

  phonebook.addContact(contact.firstName, contact.lastName, contact.nickName,
                       contact.phoneNumber, contact.darkestSecret);
  std::cout << "Contact added successfully." << '\n';
}
