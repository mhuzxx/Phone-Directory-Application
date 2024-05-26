#include "Contact.h"

Contact::Contact(const std::string& firstName, const std::string& lastName,
                 const std::string& mobileNumber, const std::string& homeNumber,
                 const std::string& workNumber, const std::string& emailAddress,
                 const std::string& birthday)
    : firstName(firstName), lastName(lastName), mobileNumber(mobileNumber),
      homeNumber(homeNumber), workNumber(workNumber), emailAddress(emailAddress),
      birthday(birthday), next(nullptr), prev(nullptr) {}

// Getter methods
std::string Contact::getFirstName() const { return firstName; }
std::string Contact::getLastName() const { return lastName; }
std::string Contact::getMobileNumber() const { return mobileNumber; }
std::string Contact::getHomeNumber() const { return homeNumber; }
std::string Contact::getWorkNumber() const { return workNumber; }
std::string Contact::getEmailAddress() const { return emailAddress; }
std::string Contact::getBirthday() const { return birthday; }

// Setter methods
void Contact::setMobileNumber(const std::string& mobile) { mobileNumber = mobile; }
void Contact::setHomeNumber(const std::string& home) { homeNumber = home; }
void Contact::setWorkNumber(const std::string& work) { workNumber = work; }
void Contact::setEmailAddress(const std::string& email) { emailAddress = email; }
void Contact::setBirthday(const std::string& bday) { birthday = bday; }

