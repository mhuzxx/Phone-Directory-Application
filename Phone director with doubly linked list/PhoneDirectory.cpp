#include "PhoneDirectory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

PhoneDirectory::PhoneDirectory() : head(NULL), tail(NULL) {
    loadContactsFromFile();
}

PhoneDirectory::~PhoneDirectory() {
    Contact* current = head;
    while (current != NULL) {
        Contact* next = current->next;
        delete current;
        current = next;
    }
}

void PhoneDirectory::addContact(const string& firstName, const string& lastName,
                                const string& mobileNumber, const string& homeNumber,
                                const string& workNumber, const string& emailAddress,
                                const string& birthday) {
    Contact* newContact = new Contact(firstName, lastName, mobileNumber, homeNumber, workNumber, emailAddress, birthday);
    if (head == NULL) {
        head = tail = newContact;
    } else {
        tail->next = newContact;
        newContact->prev = tail;
        tail = newContact;
    }
    lastNameMap[lastName].push_back(newContact);
    saveContactsToFile();
}

vector<Contact*> PhoneDirectory::getAllContacts() const {
    vector<Contact*> contacts;
    Contact* current = head;
    while (current != NULL) {
        contacts.push_back(current);
        current = current->next;
    }
    return contacts;
}

void PhoneDirectory::displayContacts(const string& sortBy) const {
    vector<Contact*> contacts = getAllContacts();

    if (sortBy == "name") {
        sort(contacts.begin(), contacts.end(), [](Contact* a, Contact* b) {
            return a->getLastName() < b->getLastName() ||
                   (a->getLastName() == b->getLastName() && a->getFirstName() < b->getFirstName());
        });
    } else if (sortBy == "mobile") {
        sort(contacts.begin(), contacts.end(), [](Contact* a, Contact* b) {
            return a->getMobileNumber() < b->getMobileNumber();
        });
    }

    if (contacts.empty()) {
        cout << "There are no contacts in the directory." << endl;
    } else {
        for (const auto& contact : contacts) {
            cout << "Name: " << contact->getFirstName() << " " << contact->getLastName() << endl;
            cout << "Mobile Number: " << contact->getMobileNumber() << endl;
            cout << "Home Number: " << contact->getHomeNumber() << endl;
            cout << "Work Number: " << contact->getWorkNumber() << endl;
            cout << "Email Address: " << contact->getEmailAddress() << endl;
            cout << "Birthday: " << contact->getBirthday() << endl;
            cout << endl;
        }
    }
}

void PhoneDirectory::editContact(const string& firstName, const string& lastName,
                                 const string& newMobile, const string& newHome,
                                 const string& newWork, const string& newEmail,
                                 const string& newBirthday) {
    Contact* current = head;
    while (current != NULL) {
        if (current->getFirstName() == firstName && current->getLastName() == lastName) {
            current->setMobileNumber(newMobile);
            current->setHomeNumber(newHome);
            current->setWorkNumber(newWork);
            current->setEmailAddress(newEmail);
            current->setBirthday(newBirthday);
            saveContactsToFile();
            cout << "Contact updated successfully!" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Contact not found!" << endl;
}

void PhoneDirectory::deleteContact(const string& firstName, const string& lastName) {
    if (head == NULL) {
        cout << "Contact not found!" << endl;
        return;
    }

    Contact* current = head;
    while (current != NULL) {
        if (current->getFirstName() == firstName && current->getLastName() == lastName) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            
            auto& vec = lastNameMap[lastName];
            vec.erase(remove(vec.begin(), vec.end(), current), vec.end());
            
            delete current;
            saveContactsToFile();
            cout << "Contact deleted successfully!" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Contact not found!" << endl;
}

void PhoneDirectory::searchContact(const string& query, const string& sortBy) const {
    vector<Contact*> results;
    auto it = lastNameMap.find(query);
    if (it != lastNameMap.end()) {
        results.insert(results.end(), it->second.begin(), it->second.end());
    }

    Contact* current = head;
    while (current != NULL) {
        if (current->getFirstName() == query || current->getMobileNumber() == query ||
            current->getHomeNumber() == query || current->getWorkNumber() == query) {
            results.push_back(current);
        }
        current = current->next;
    }

    if (sortBy == "name") {
        sort(results.begin(), results.end(), [](Contact* a, Contact* b) {
            return a->getLastName() < b->getLastName() ||
                   (a->getLastName() == b->getLastName() && a->getFirstName() < b->getFirstName());
        });
    } else if (sortBy == "mobile") {
        sort(results.begin(), results.end(), [](Contact* a, Contact* b) {
            return a->getMobileNumber() < b->getMobileNumber();
        });
    }

    if (!results.empty()) {
        cout << "Search results:" << endl;
        for (Contact* contact : results) {
            cout << "Name: " << contact->getFirstName() << " " << contact->getLastName() << endl;
            cout << "Mobile Number: " << contact->getMobileNumber() << endl;
            cout << "Home Number: " << contact->getHomeNumber() << endl;
            cout << "Work Number: " << contact->getWorkNumber() << endl;
            cout << "Email Address: " << contact->getEmailAddress() << endl;
            cout << "Birthday: " << contact->getBirthday() << endl;
            cout << endl;
        }
    } else {
        cout << "Contact not found!" << endl;
    }
}

void PhoneDirectory::saveContactsToFile() const {
    ofstream outFile("contacts.txt");
    Contact* current = head;
    while (current != NULL) {
        outFile << current->getFirstName() << ","
                << current->getLastName() << ","
                << current->getMobileNumber() << ","
                << current->getHomeNumber() << ","
                << current->getWorkNumber() << ","
                << current->getEmailAddress() << ","
                << current->getBirthday() << "\n";
        current = current->next;
    }
    outFile.close();
}

void PhoneDirectory::loadContactsFromFile() {
    ifstream inFile("contacts.txt");
    string line;
    while (getline(inFile, line)) {
        istringstream ss(line);
        string firstName, lastName, mobile, home, work, email, birthday;
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, mobile, ',');
        getline(ss, home, ',');
        getline(ss, work, ',');
        getline(ss, email, ',');
        getline(ss, birthday, ',');
        addContact(firstName, lastName, mobile, home, work, email, birthday);
    }
    inFile.close();
}

