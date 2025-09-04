#include <stdio.h>
#include "file.h"


// Function to save contacts to a CSV file
void saveContactsToFile(AddressBook *addressBook) {

   	// Open the file for writing in "w" mode, which creates an empty file for output
    	FILE *fptr = fopen("file.csv", "w");

    	// If file cannot be opened, print an error and return
    	if (fptr == NULL) 
    	{
        	printf("Error: Could not open file for writing\n");
        	return;
    	}

    	// First, write the number of contacts in the file
    	fprintf(fptr, "%d\n", addressBook->contactCount);

    	// Loop through all contacts and write them to the file in CSV format
    	for (int i = 0; i < addressBook->contactCount; i++) 
    	{
        	fprintf(fptr, "%s,%s,%s\n", 
                        addressBook->contacts[i].name, 
                	addressBook->contacts[i].phone, 
                	addressBook->contacts[i].email);
    	}

    	// Close the file after writing
    	fclose(fptr);
}

//Function to Load contact from csv file
void loadContactsFromFile(AddressBook *addressBook) {
     	// Open the file for reading in "r" mode
    	FILE *fptr = fopen("file.csv", "r");

    	// If the file cannot be opened (possibly because it doesn't exist), print an error and return
    	if (fptr == NULL) 
    	{
        	printf("Error: File not found. No contacts to load.\n");
        	return;
    	}

    	// Read the number of contacts stored in the file (the first line)
    	if (fscanf(fptr, "%d\n", &addressBook->contactCount) != 1) 
    	{
        	printf("Error: Failed to read the contact count\n");
        	fclose(fptr);  // Close the file and exit the function
        	return;
    	}

    	// Loop through the file and read each contact's name, phone number, and email
    	for (int i = 0; i < addressBook->contactCount; i++) 
    	{
        /* Read each contact's data from the CSV file. It reads until a comma (`,`) for name and phone, 
	  and until newline for email*/
        	fscanf(fptr, "%[^,],%[^,],%s\n", 
               		addressBook->contacts[i].name, 
               		addressBook->contacts[i].phone, 
               		addressBook->contacts[i].email);
    	}

    	// Close the file after reading
    	fclose(fptr);
}
