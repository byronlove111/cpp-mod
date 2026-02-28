#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP
#include "contact.hpp"

class Phonebook {
private:
  Contact contacts[8];
  int contacts_counter;
  int contacts_total;

public:
  Phonebook();
  Contact getContact(int index);
  Contact *getAllContacts();
  int getContactCounter();
  void addContact(std::string firstName, std::string lastName,
                  std::string nickName, std::string phoneNumber,
                  std::string darkestSecret);
  void searchContact();
};

#endif
