#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct{
	char name[20];
	char phone[11];
	char mail[20];
}contact;

typedef struct{
	contact contacts[MAX_CONTACTS];
	int contactcount;
}AddressBook;

void listContact(AddressBook *addressbook);
void createContact(AddressBook *addressbook);
void searchContact(AddressBook *addressbook);
void EditContact(AddressBook *addressbook);
void DeleteContact(AddressBook *addressbook);
void InitializeAddressBook(AddressBook *addressbook);
void SaveandExit(AddressBook *addressbook);
void saveContactsToFile(AddressBook *addressbook);
void loadContactsFromFile(AddressBook *addressbook);
#endif
