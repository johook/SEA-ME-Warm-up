#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class Contact
{
public:
	string name;
	string number;
	string nickname;
	bool bookmarked;

	Contact(string name, string number, string nickname)
		: name(name), number(number), nickname(nickname), bookmarked(false) {}
	// Initialize Contact
};

class Phonebook
{
private:
	vector<Contact> contacts;		// 'contacts' is a vector name, a collection of Contact class objects



public:
	void addContact();
	void searchContacts();
	void removeContacts();
	void listBookmarkedContacts();
	void exitProgram();
};

void Phonebook::addContact()
{
	string name, number, nickname;

	cout << "Enter name: ";
	cin >> name;
	cout << "Enter Phone Number: ";
	cin >> number;

	for (const auto& info : contacts) {		// Returns if the phone number is already exists.
		if (info.number == number) {
			cout << "Check the Phonenumber." << endl;
			return;
		}
	} 
	// Reference for the [for loop with auto&, const auto&] https://boycoding.tistory.com/210 
	// Read only for loop: auto& -> No copying, so the cost is reduced
	cout << "Enter Nickname: ";
	cin >> nickname;

	contacts.push_back(Contact(name, number, nickname));
	cout << "Success" << endl;
}

void Phonebook::searchContacts() {

	if (contacts.empty()) {
		cout << "Phonebook is empty" << endl;
		return;
	}

	for (int i = 0; i < contacts.size(); i++) {
		cout << i + 1 << ". " << contacts[i].name << endl;
	}
	cout << "Enter the index number to view details, or enter 0 to bookmark a contact: ";
	int index;
	cin >> index;

	// Show detailed info
	if (index > 0 && index <= contacts.size()) {
		const Contact& contact = contacts[index - 1];  // Need -1, cause index starts from 0
		cout << "Name: " << contact.name << endl;
		cout << "Phone Number: " << contact.number << endl;
		cout << "Nickname: " << contact.nickname << endl;
		cout << "Bookmarked: " << (contact.bookmarked ? "Yes" : "No") << endl;
	}
	// Bookmark contact
	else if (index == 0) {
		cout << "Enter the number of the contact to bookmark: ";
		int bookmarkIndex;
		cin >> bookmarkIndex;

		if (bookmarkIndex > 0 && bookmarkIndex <= contacts.size()) {
			contacts[bookmarkIndex - 1].bookmarked = true;
			cout << "Contact bookmarked successfully!" << endl;
		}
		else {
			cout << "Invalid index for bookmarking." << endl;
		}
	}
	else {
		cout << "Wrong index." << endl;
	}

}

void Phonebook::removeContacts() {
	cout << "Enter the index or phone number of the contact to remove: ";
	string input;
	cin >> input;

	// 1. Remove by index
	int index = stoi(input); // Convert input to integer
	if (index > 0 && index <= contacts.size()) {
		contacts.erase(contacts.begin() + (index - 1));
		cout << "Contact removed successfully!" << endl;
		return;
	}

	// 2. Remove by phonenumber
	auto it = find_if(contacts.begin(), contacts.end(), [&](const Contact& contact) {
		return contact.number == input;
		});

	if (it != contacts.end()) {
		contacts.erase(it);
		cout << "Contact removed successfully!" << endl;
	}
	else {
		cout << "Contact not found." << endl;
	}

}

void Phonebook::listBookmarkedContacts() {
	cout << "Bookmarked Contacts:" << endl;

	for (const auto& contact : contacts) {
		if (contact.bookmarked) {
			cout << contact.name << " (" << contact.number << ")" << endl;
		}
	}

}

void Phonebook::exitProgram() {
	cout << "Exiting Phonebook. Goodbye!" << endl;
}


int main()
{
	Phonebook phonebook;
	string command;

	while (true) {
		cout << "\nEnter command (ADD, SEARCH, REMOVE, LIST_BOOKMARK, EXIT): ";
		cin >> command;

		if (command == "ADD") {
			phonebook.addContact();
		}
		else if (command == "SEARCH") {
			phonebook.searchContacts();
		}
		else if (command == "REMOVE") {
			phonebook.removeContacts();
		}
		else if (command == "LIST_BOOKMARK") {
			phonebook.listBookmarkedContacts();
		}
		else if (command == "EXIT") {
			phonebook.exitProgram();
			break;
		}
		else {
			cout << "Invalid command." << endl;
		}
	}

	return 0;
}
