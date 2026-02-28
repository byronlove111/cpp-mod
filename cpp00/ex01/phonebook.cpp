#include "phonebook.hpp"
#include "contact.hpp"
#include <iomanip>
#include <iostream>
#include <stdlib.h>

// constructor
Phonebook::Phonebook() { contacts_counter = 0; contacts_total = 0; }

// getter and setters
Contact Phonebook::getContact(int index) { return contacts[index]; }

int Phonebook::getContactCounter() { return contacts_total; }

void Phonebook::addContact(std::string firstName, std::string lastName,
                           std::string nickName, std::string phoneNumber,
                           std::string darkestSecret) {
  if (contacts_counter >= 8)
    contacts_counter = 0;
  Contact contact;
  contact.setFirstName(firstName);
  contact.setLastName(lastName);
  contact.setNickName(nickName);
  contact.setPhoneNumber(phoneNumber);
  contact.setDarkestSecret(darkestSecret);
  contacts[contacts_counter] = contact;
  contacts_counter++;
  if (contacts_total < 8)
    contacts_total++;
}

static std::string truncate(std::string str) {
  if (str.length() >= 10) {
    str = str.substr(0, 10);
    str[9] = '.';
    return str;
  }
  return str;
}

static int readIndex(const std::string &message, int limit) {
  std::string field;
  int index;
  bool valid_input = false;

  while (!valid_input) {
    std::cout << message;
    std::getline(std::cin, field);

    index = std::atoi(field.c_str());
    if (index <= limit && index > 0) {
      valid_input = true;
    } else {
      std::cout << "Invalid index, please try again." << '\n';
    }
  }
  return index;
}

void Phonebook::searchContact() {
  std::cout << std::setw(10) << std::right << "index" << '|';
  std::cout << std::setw(10) << std::right << "first name" << '|';
  std::cout << std::setw(10) << std::right << "last name" << '|';
  std::cout << std::setw(10) << std::right << "nickname" << '|' << '\n';

  if (contacts_total > 0) {
    for (int i = 0; i < contacts_total; i++) {
      Contact contact = getContact(i);
      std::cout << std::setw(10) << std::right << i + 1 << '|';
      std::cout << std::setw(10) << std::right
                << truncate(contact.getFirstName()) << '|';
      std::cout << std::setw(10) << std::right
                << truncate(contact.getLastName()) << '|';
      std::cout << std::setw(10) << std::right
                << truncate(contact.getNickName()) << '|' << '\n';
    }

    int user_index = readIndex("Enter an index : ", contacts_total);
    Contact selectedContact = getContact(user_index - 1);
    selectedContact.printContact();
  }
}
