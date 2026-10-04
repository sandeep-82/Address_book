#include <stdio.h>
#include "contact.h"

// ...existing code...

int main(void)
{
    AddressBook addressbook;
    InitializeAddressBook(&addressbook);

    int choice;
    int ch;

    do
    {
        printf("\n====================================\n");
        printf("          ADDRESS BOOK MENU         \n");
        printf("====================================\n");
        printf("  1. List Contacts\n");
        printf("  2. Create Contact\n");
        printf("  3. Search Contact\n");
        printf("  4. Edit Contact\n");
        printf("  5. Delete Contact\n");
        printf("  6. Save and Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n[Error] Please enter a number from 1 to 6.\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
            choice = 0;
            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF);

        switch (choice)
        {
            case 1:
                listContact(&addressbook);
                break;

            case 2:
                createContact(&addressbook);
                break;

            case 3:
                searchContact(&addressbook);
                break;

            case 4:
                EditContact(&addressbook);
                break;

            case 5:
                DeleteContact(&addressbook);
                break;

            case 6:
                SaveandExit(&addressbook);
                break;

            default:
                printf("\n[Error] Invalid choice. Please select 1 to 6.\n");
        }
    } while (choice != 6);

    return 0;
}