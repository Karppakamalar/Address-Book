#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    printf("\n=====================================================================\n");
    printf("\t\t\tCONTACT LIST\n");
    printf("=====================================================================\n");

    printf("S.No\tName\t\tPhone\t\tEmail\n");
    printf("---------------------------------------------------------------------\n");

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d\t%s\t\t%s\t%s\n",
                i + 1,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    printf("=====================================================================\n");
    
}

void initialize(AddressBook *addressBook) {
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    printf("\n");
    printf("==============================================================\n");
    printf("                     CREATE CONTACT\n");
    printf("==============================================================\n");
    printf("Enter Name : ");
    name_validation(addressBook, addressBook->contactCount);

    printf("Enter Phone : ");
    phonenum_validation(addressBook, addressBook->contactCount);

    printf("Enter Email : ");
    mail_validation(addressBook, addressBook->contactCount);

    addressBook->contactCount++;

    printf("\nContact Created Successfully\n");
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    printf("\n");
    printf("==============================================================\n");
    printf("                     SEARCH CONTACT\n");
    printf("==============================================================\n");
    printf("1. By name\n2. By phone number\n3. By mail id\n");
    printf("Please choose from the above option to search: ");
    int opt;
    scanf("%d", &opt);
    printf("\n");
    int index;
    switch(opt)
    {
        case 1:
            index = search_by_name(addressBook);

            if(index != -1){
                printf("\nName : %s\n",
                        addressBook->contacts[index].name);
                printf("Phone: %s\n",
                        addressBook->contacts[index].phone);
                printf("Email: %s\n",
                        addressBook->contacts[index].email);
            }
            else{
                printf("Contact not found\n");
            }
            break;

        case 2:
            search_by_phone(addressBook);
            break;

        case 3:
            search_by_mail(addressBook);
            break;
        default:
            printf("Invalid choice.\n");

    }
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    printf("\n");
    printf("==============================================================\n");
    printf("                      EDIT CONTACT\n");
    printf("==============================================================\n");
    int index = search_by_name(addressBook);

    if(index == -1)
    {
        printf("Contact not found\n");
        return;
    }

    printf("\nName : %s\n", addressBook->contacts[index].name);
    printf("Phone: %s\n", addressBook->contacts[index].phone);
    printf("Email: %s\n", addressBook->contacts[index].email);

    int opt;

    printf("\n1. Edit Name");
    printf("\n2. Edit Phone");
    printf("\n3. Edit Email");
    printf("\nEnter your choice: ");

    scanf("%d",&opt);

    switch(opt)
    {
        case 1:
            name_validation(addressBook, index);
            printf("Name updated successfully\n");
            break;

        case 2:
            phonenum_validation(addressBook, index);
            printf("Phone number updated successfully\n");
            break;

        case 3:
            mail_validation(addressBook, index);
            printf("Email updated successfully\n");
            break;

        default:
            printf("Invalid choice.\n");


    }
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    printf("\n");
    printf("==============================================================\n");
    printf("                    DELETE CONTACT\n");
    printf("==============================================================\n");

    int i=search_by_name(addressBook);                    

    if(i==-1){
        printf("Contact is not found");
        return;
    }
    for(int j=i;j<addressBook->contactCount-1;j++){
        addressBook->contacts[j]=addressBook->contacts[j+1];
    }
    addressBook->contactCount--;
    printf("\nContact deleted successfully.\n");
}

void name_validation(AddressBook *addressBook,int index){
    char str[50];
    while(1){
        int flag=0;
        int i=0;
        scanf(" %[^\n]",str);
        while(str[i]!='\0'){
            if(!isalpha(str[i]) && str[i]!=' '){
                flag=1;
                break;
            }
            i++;
        }
        if(flag==0){
            strcpy(addressBook->contacts[index].name,str);
            break;
        }
        else{
            printf("Invalid name. Enter again: \n");
        }
    }
}

void phonenum_validation(AddressBook *addressBook,int index){
    char str[20];
    while(1){
        int i=0;
        int flag=0;
        scanf("%s",str);
        int n=strlen(str);
        if(n!=10){
            printf("Invalid phone number. Enter valid number\n");
            continue;
        }
        while(str[i]!='\0'){
            if(!isdigit(str[i])){
                flag=1;
                break;
            }
            
            i++;
        }
        if(phone_exists(addressBook, str, index)){
            printf("Phone number already exists. Enter another number\n");
            continue;
        }
        if(flag==0){
            strcpy(addressBook->contacts[index].phone,str);
            break;
        }
        else{
            printf("Invalid phone number.Please enter a valid number\n");
        }
    }
}
void mail_validation(AddressBook *addressBook,int index){
    char str[50];
    while(1){
        int flag=0;
        scanf("%s",str);
        int n=strlen(str);
        if (n<= 10)
        {
            flag = 1;
        }
        // Check whether the email ends with "@gmail.com" as @gmail.com is 10 char so we reduce that length and check
        else if(strcmp(str + n - 10, "@gmail.com") != 0){
            flag = 1;
        }
        else{
            //check the charac before @gmail.com whether those are valid or not
            for(int i=0;i<n-10;i++){
                if(!isdigit(str[i]) && !islower(str[i])){
                    flag=1;
                    break;
                }
            }
        }
        if(email_exists(addressBook, str, index)){
            printf("Email already exists. Enter another email\n");
            continue;
        }
        if(flag==0){
            strcpy(addressBook->contacts[index].email,str);
            break;
        }
        else{
            printf("Invalid email id . Please enter a valid mail id\n");
        }
    }
}
int search_by_name(AddressBook *addressBook)
{
    char str[50];
    int matches[100];
    int count = 0;

    printf("Please enter the person's name: ");
    scanf(" %[^\n]", str);

    // Convert entered name to lowercase
    for(int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }

    // Search all contacts
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        char temp[50];
        strcpy(temp, addressBook->contacts[i].name);

        // Convert stored name to lowercase
        for(int j = 0; temp[j] != '\0'; j++)
        {
            temp[j] = tolower(temp[j]);
        }

        if(strstr(temp, str) != NULL)
        {
            printf("%d. %s\n",
            count + 1,addressBook->contacts[i].name);
            matches[count] = i;
            count++;
        }
    }

    if(count == 0)
    {
        return -1;
    }

    if(count == 1)
    {
        return matches[0];
    }

    int choice;

    while(1)
    {
        printf("Multiple contacts found.\n");
        printf("Enter your choice (1-%d): ", count);
        scanf("%d", &choice);

        if(choice >= 1 && choice <= count)
        {
            return matches[choice - 1];
        }

        printf("Invalid choice. Try again.\n");
    }
}
void search_by_phone(AddressBook *addressBook){
    char str[20];
    printf("Please enter the person's phone number to get info: ");
    scanf(" %s",str);
    int flag=0;
    int index=0;
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(str,addressBook->contacts[i].phone)==0){
            flag=1;
            index=i;
        }
    }
    printf("\n");
    if(flag==1){
        printf("Name: %s\nPhone number: %s\nMail id: %s\n",addressBook->contacts[index].name,addressBook->contacts[index].phone,
            addressBook->contacts[index].email);
    }
    else{
        printf("contact is not found");
    }
}
void search_by_mail(AddressBook *addressBook){
    char str[20];
    printf("Please enter the person's mail id to get info: ");
    scanf(" %s",str);
    int flag=0;
    int index=0;
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(str,addressBook->contacts[i].email)==0){
            flag=1;
            index=i;
        }
    }
    printf("\n");
    if(flag==1){
        printf("Name: %s\nPhone number:%s \nMail id:%s\n",addressBook->contacts[index].name,addressBook->contacts[index].phone,
            addressBook->contacts[index].email);
    }
    else{
        printf("contact is not found");
    }
}

int phone_exists(AddressBook *addressBook, char *phone, int index)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(i == index)
            continue;

        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
            return 1;
    }

    return 0;
}

int email_exists(AddressBook *addressBook, char *email, int index)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(i == index)
            continue;

        if(strcmp(addressBook->contacts[i].email, email) == 0)
            return 1;
    }

    return 0;
}

