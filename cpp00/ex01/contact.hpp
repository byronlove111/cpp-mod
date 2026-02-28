#ifndef CONTACT_HPP
#define CONTACT_HPP
#include <string>

class Contact {
private:
  std::string first_name;
  std::string last_name;
  std::string nickname;
  std::string phone_number;
  std::string darkest_secret;

public:
  Contact();
  std::string getFirstName() const;
  void setFirstName(std::string val);
  std::string getLastName() const;
  void setLastName(std::string val);
  std::string getNickName() const;
  void setNickName(std::string val);
  std::string getPhoneNumber() const;
  void setPhoneNumber(std::string val);
  std::string getDarkestSecret() const;
  void setDarkestSecret(std::string val);
  void printContact();
};

#endif
