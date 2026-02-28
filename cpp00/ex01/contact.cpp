#include "contact.hpp"
#include <iostream>

Contact::Contact() {
  first_name = "";
  last_name = "";
  nickname = "";
  phone_number = "";
  darkest_secret = "";
}

// getters and setters
std::string Contact::getFirstName() const { return first_name; }
void Contact::setFirstName(std::string val) { first_name = val; }

std::string Contact::getLastName() const { return last_name; }
void Contact::setLastName(std::string val) { last_name = val; }

std::string Contact::getNickName() const { return nickname; }
void Contact::setNickName(std::string val) { nickname = val; }

std::string Contact::getPhoneNumber() const { return phone_number; }
void Contact::setPhoneNumber(std::string val) { phone_number = val; }

std::string Contact::getDarkestSecret() const { return darkest_secret; }
void Contact::setDarkestSecret(std::string val) { darkest_secret = val; }

void Contact::printContact() {
  std::cout << '\n';
  std::cout << "First Name : " << first_name << '\n';
  std::cout << "Last Name : " << last_name << '\n';
  std::cout << "Nickname : " << nickname << '\n';
  std::cout << "Phone Number : " << phone_number << '\n';
  std::cout << "Darkest Secret : " << darkest_secret << '\n' << '\n';
}
