#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>
void listContacts(AddressBook *addressBook)
{
    
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("Name : %s \t\t", addressBook->contacts[i].name);
        printf("Phone Number : %s", addressBook->contacts[i].phone);
        printf("Email ID : %s", addressBook->contacts[i].email);

        printf("\n");
    }
}
void displayContact(Contact contact) {
    printf("\nContact Details:\n");//Displaying contact information
    printf("Name: %s", contact.name);//display Name
    printf("Phone: %s", contact.phone);//display Phone number
    printf("Email: %s", contact.email);//Display email
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}
void createContact(AddressBook *addressBook)
{
    char name1[30], phone1[12], email1[30];
    int valid, i, option;

    while (1) {
        printf("\nCreate Contact Menu\n");
        printf("1. Add New Contact\n");
        printf("2. Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                //  Name Validation 
                while (1) {
                    printf("Enter the Name :\n");
                    scanf(" %[^\n]", name1);

                    valid = 1;
                    for (i = 0; name1[i] != '\0'; i++) {
                        if (!isalpha(name1[i]) && name1[i] != ' ') {
                            valid = 0;
                            break;
                        }
                    }
                    if (valid) break;
                    printf("Invalid name, Please use only Alphabets\n");
                }

                // Phone number Validation
                while (1) {
                    printf("Enter the phone Number :\n");
                    scanf(" %[^\n]", phone1);

                    if (strlen(phone1) != 10) {
                        printf("Invalid phone number, Must be 10 digits\n");
                        continue;
                    }

                    valid = 1;
                    for (i = 0; phone1[i] != '\0'; i++) {
                        if (!isdigit(phone1[i])) {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid) {
                        printf("Invalid Phone number, Must contain only digits\n");
                        continue;
                    }

                    // Duplicate phone number check
                    int duplicate = 0;
                    for (i = 0; i < addressBook->contactCount; i++) {
                        if (strcmp(addressBook->contacts[i].phone, phone1) == 0) {
                            duplicate = 1;
                            break;
                        }
                    }

                    if (duplicate) {
                        printf("Phone number already exists, please enter another phone number\n");
                        continue;
                    }

                    break; //Valid & unique phone number
                }

                // Email Validation
                while (1) {
                    printf("Enter the Email ID :\n");
                    scanf(" %[^\n]", email1);

                    char *atpos = strchr(email1, '@');
                    char *dotpos = strstr(email1, ".com");

                    if (!atpos || !dotpos || dotpos < atpos) {
                        printf("Invalid Email ID\n");
                        continue;
                    }

                    if (atpos == email1) {
                        printf("Invalid Email ID: must have text before '@'\n");
                        continue;
                    }

                    valid = 1;
                    for (i = 0; email1[i] != '@'; i++) {
                        if (!isalnum(email1[i]) && email1[i] != '.') {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid) {
                        printf("Invalid Email ID: only alphanumeric and '.' allowed before '@'\n");
                        continue;
                    }

                    char *mid = atpos + 1;
                    if (mid >= dotpos || !isalnum(*mid)) {
                        printf("Invalid Email ID: need valid text after '@'\n");
                        continue;
                    }

                    if (!isalnum(*(dotpos - 1))) {
                        printf("Invalid Email ID: must end with alphanumeric before '.com'\n");
                        continue;
                    }

                    break; //valid email
                }

                if (addressBook->contactCount >= MAX_CONTACTS) {
                    printf("Address book is full!\n");
                    return;
                }

                // Saving Contact 
                strcpy(addressBook->contacts[addressBook->contactCount].name, name1);
                strcpy(addressBook->contacts[addressBook->contactCount].phone, phone1);
                strcpy(addressBook->contacts[addressBook->contactCount].email, email1);
                addressBook->contactCount++;

                printf("Contact added successfully\n");
                break;

            case 2:
                printf("Exiting Create Contact Menu.\n");
                return;

            default:
                printf("Invalid option, Please try again.\n");
                break;
        }
    }
}
int searchContact(AddressBook *addressBook)
{
    int option, i;
    char searchn[50], searchp[20], searche[50];

    while (1) {
        printf("\nSearch Menu\n");
        printf("1. Search by Name\n");
        printf("2. Search by Phone Number\n");
        printf("3. Search by Email\n");
        printf("4. Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            // Searching by Name
            case 1:
                printf("Enter name to search: ");
                scanf(" %[^\n]", searchn);

                for (i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].name, searchn) == 0) {
                        printf("Contact Found at index %d\n", i);
                        printf("%s | %s | %s\n",
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                        return i;
                    }
                }
                printf("Contact not found.\n");
                break;

            // Searching by Phone 
            case 2:
                printf("Enter phone number to search: ");
                scanf(" %[^\n]", searchp);

                for (i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].phone, searchp) == 0) {
                        printf("Contact Found at index %d\n", i);
                        printf("%s | %s | %s\n",
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                        return i;
                    }
                }
                printf("Contact not found.\n");
                break;

            // Searching by Email
            case 3:
                printf("Enter email to search: ");
                scanf(" %[^\n]", searche);

                for (i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].email, searche) == 0) {
                        printf("Contact Found at index %d\n", i);
                        printf("%s | %s | %s\n",
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                        return i;
                    }
                }
                printf("Contact not found.\n");
                break;

            // Exiting from function
            case 4:
                printf("Exiting search menu.\n");
                return -1; // no contact selected

            // Invalid Option
            default:
                printf("Invalid option. Please enter a valid menu choice (1-4).\n");
                break;
        }
    }
}
void deleteContact(AddressBook *addressBook) {
    int option, i, j, found;
    char searchn[30], searchp[12], searche[30];

    while (1) {
        found = 0;
        printf("\nDelete Menu\n");
        printf("1. Delete by Name\n");
        printf("2. Delete by Phone Number\n");
        printf("3. Delete by Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            // Deleting by Name
            case 1: {
                printf("Enter name to delete: ");
                scanf(" %[^\n]", searchn);

                int matches[100], matchCount = 0;
                for (i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].name, searchn) == 0) {
                        matches[matchCount++] = i;
                    }
                }

                if (matchCount == 0) {
                    printf("No contact found with that name.\n");
                } else if (matchCount == 1) {
                    // if contact matches only one by name → delete directly
                    for (j = matches[0]; j < addressBook->contactCount - 1; j++) {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully.\n");
                } else {
                    // Multiple contact found on by name → ask for phone number
                    printf("Multiple contacts found with name \"%s\":\n", searchn);
                    for (i = 0; i < matchCount; i++) {
                        int idx = matches[i];
                        printf("%d. %s, %s, %s\n", i + 1,
                               addressBook->contacts[idx].name,
                               addressBook->contacts[idx].phone,
                               addressBook->contacts[idx].email);
                    }
                    printf("Enter the phone number of the contact you want to delete: ");
                    scanf(" %[^\n]", searchp);

                    found = 0;
                    for (i = 0; i < matchCount; i++) {
                        int idx = matches[i];
                        if (strcmp(addressBook->contacts[idx].phone, searchp) == 0) {
                            for (j = idx; j < addressBook->contactCount - 1; j++) {
                                addressBook->contacts[j] = addressBook->contacts[j + 1];
                            }
                            addressBook->contactCount--;
                            printf("Contact deleted successfully.\n");
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        printf("No contact with that phone number under name \"%s\".\n", searchn);
                    }
                }
                break;
            }

            // Deleting by Phone number
            case 2:
                printf("Enter phone number to delete: ");
                scanf(" %[^\n]", searchp);

                for (i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].phone, searchp) == 0) {
                        found = 1;
                        for (j = i; j < addressBook->contactCount - 1; j++) {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--;
                        printf("Contact deleted successfully.\n");
                        break;
                    }
                }
                if (!found) {
                    printf("Contact not found.\n");
                }
                break;

            //  Deleting by Email 
            case 3:
                printf("Enter email to delete: ");
                scanf(" %[^\n]", searche);

                for (i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].email, searche) == 0) {
                        found = 1;
                        for (j = i; j < addressBook->contactCount - 1; j++) {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--;
                        printf("Contact deleted successfully.\n");
                        break;
                    }
                }
                if (!found) {
                    printf("Contact not found.\n");
                }
                break;

            // Exit from function
            case 4:
                printf("Exiting delete menu.\n");
                return;

            default:
                printf("Invalid option. Please enter a valid menu choice (1-4).\n");
                break;
        }
    }
}


void editContact(AddressBook *addressBook)
{
    int index = searchContact(addressBook);
    if (index == -1) {
        return; // no contact found
    }

    int choice, i, valid;
    char temp[50];

    while (1) {
        printf("\nEdit Menu:\n");
        printf("1. Edit Name\n");
        printf("2. Edit Phone Number\n");
        printf("3. Edit Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            //  Edit Name 
            case 1:
                while (1) {
                    printf("Enter new name: ");
                    scanf(" %[^\n]", temp);

                    valid = 1;
                    for (i = 0; temp[i] != '\0'; i++) {
                        if (!isalpha(temp[i]) && temp[i] != ' ') {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid) {
                        printf("Invalid name. Please use only alphabets and spaces.\n");
                        continue;
                    }
                    strcpy(addressBook->contacts[index].name, temp);
                    printf("Name updated successfully.\n");
                    break;
                }
                break;

            //  Edit Phone Number
            case 2:
                while (1) {
                    printf("Enter new phone number: ");
                    scanf(" %[^\n]", temp);

                    if (strlen(temp) != 10) {
                        printf("Invalid phone number. Must be exactly 10 digits.\n");
                        continue;
                    }

                    valid = 1;
                    for (i = 0; temp[i] != '\0'; i++) {
                        if (!isdigit(temp[i])) {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid) {
                        printf("Invalid phone number. Only digits allowed.\n");
                        continue;
                    }

                    strcpy(addressBook->contacts[index].phone, temp);
                    printf("Phone number updated successfully.\n");
                    break;
                }
                break;

            // Edit Email 
            case 3:
                while (1) {
                    printf("Enter new email: ");
                    scanf(" %[^\n]", temp);

                    char *atpos = strchr(temp, '@');
                    char *dotpos = strstr(temp, ".com");

                    if (!atpos || !dotpos || dotpos < atpos) {
                        printf("Invalid email ID. Must contain '@' and end with '.com'.\n");
                        continue;
                    }

                    if (atpos == temp) {
                        printf("Invalid email: must have text before '@'.\n");
                        continue;
                    }

                    valid = 1;
                    for (i = 0; temp[i] != '@'; i++) {
                        if (!isalnum(temp[i]) && temp[i] != '.') {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid) {
                        printf("Invalid email: only letters, digits and '.' allowed before '@'.\n");
                        continue;
                    }

                    char *mid = atpos + 1;
                    if (mid >= dotpos || !isalnum(*mid)) {
                        printf("Invalid email: need valid text after '@'.\n");
                        continue;
                    }

                    if (!isalnum(*(dotpos - 1))) {
                        printf("Invalid email: must end with alphanumeric before '.com'.\n");
                        continue;
                    }

                    strcpy(addressBook->contacts[index].email, temp);
                    printf("Email updated successfully.\n");
                    break;
                }
                break;

            //  Exiting from function
            case 4:
                printf("Exiting edit menu.\n");
                return; // exit the function

            // Invalid Choice 
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}
     
