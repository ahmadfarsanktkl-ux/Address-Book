#ifndef FILE_H
#define FILE_H

#include "contact.h"
//Function declaration to save all contacts to a file.
//This function writes the contacts in the AddressBook to a CSV file.
void saveContactsToFile(AddressBook *addressBook);


//Function declaration to load contacts from a file.
//This function reads contact information from a CSV file and loads it into the AddressBook.
void loadContactsFromFile(AddressBook *addressBook);

#endif
