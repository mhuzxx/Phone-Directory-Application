#ifndef CONTACT_H
#define CONTACT_H
#include <string>
class Contact {
private:
    std::string firstName;
    std::string lastName;
    std::string mobileNumber;
    std::string homeNumber;
    std::string workNumber;
    std::string emailAddress;
    std::string birthday;

public:
    Contact* next;
    Contact* prev;

    Contact(const std::string& firstName, const std::string& lastName,
            const std::string& mobileNumber, const std::string& homeNumber,
            const std::string& workNumber, const std::string& emailAddress,
            const std::string& birthday);
    // Getter methods
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getMobileNumber() const;
    std::string getHomeNumber() const;
    std::string getWorkNumber() const;
    std::string getEmailAddress() const;
    std::string getBirthday() const;
    // Setter methods
    void setMobileNumber(const std::string& mobile);
    void setHomeNumber(const std::string& home);
    void setWorkNumber(const std::string& work);
    void setEmailAddress(const std::string& email);
    void setBirthday(const std::string& bday);
};
#endif // CONTACT_H

