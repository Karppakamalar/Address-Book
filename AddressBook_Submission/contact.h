#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void name_validation(AddressBook *addressBook,int index);
void phonenum_validation(AddressBook *addressBook,int index);
void mail_validation(AddressBook *addressBook,int index);
int search_by_name(AddressBook *addressBook);
void search_by_phone(AddressBook *addressBook);
void search_by_mail(AddressBook *addressBook);
int phone_exists(AddressBook *addressBook, char *phone, int index);
int email_exists(AddressBook *addressBook, char *email, int index);

#endif
