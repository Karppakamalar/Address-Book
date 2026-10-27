#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook; //single sturcture variable
    initialize(&addressBook);
   

    do {
        printf("\n");
        printf("==============================================================\n");
        printf("                  ADDRESS BOOK SYSTEM\n");
        printf("==============================================================\n");
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving contacts...\n");
                saveContactsToFile(&addressBook);
                printf("Contacts saved successfully.\n");
                break;
            case 7 :
                printf("\n==============================================================\n");
                printf("      Thank you for using Address Book System!\n");
                printf("==============================================================\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
