#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

void listContact(AddressBook *addressbook)
{
        if (addressbook == NULL)
        {
                printf("\n[Error] Address book is not initialized.\n");
                return;
        }

        if (addressbook->contactcount == 0)
        {
                printf("\n+----------------------------------------+\n");
                printf("|          Address book is empty         |\n");
                printf("+----------------------------------------+\n");
                return;
        }

        printf("\n=========================== CONTACTS ===========================\n");
        printf("+------+----------------------+--------------+---------------------------+\n");
        printf("| %-4s | %-20s | %-12s | %-25s |\n",
               "No.", "Name", "Phone", "Email");
        printf("+------+----------------------+--------------+---------------------------+\n");

        for (int i = 0; i < addressbook->contactcount; i++)
        {
                contact *c = &addressbook->contacts[i];

                printf("| %-4d | %-20.20s | %-12.12s | %-25.25s |\n",
                       i + 1, c->name, c->phone, c->mail);
        }

        printf("+------+----------------------+--------------+---------------------------+\n");
        printf("Total contacts: %d\n", addressbook->contactcount);
}
void InitializeAddressBook(AddressBook *addressbook)   
{
        if (addressbook == NULL) return;
        
        addressbook->contactcount = 0;
        loadContactsFromFile(addressbook);
}

void createContact(AddressBook *addressbook)
{
        if (addressbook == NULL)
        {
                printf("\n[Error] Address book is not initialized.\n");
                return;
        }

        if (addressbook->contactcount >= MAX_CONTACTS)
        {
                printf("\n[Error] Address book is full!\n");
                return;
        }

        contact *new_c = &addressbook->contacts[addressbook->contactcount];
        int ch;

        printf("\n+----------------------------------------+\n");
        printf("|             ADD NEW CONTACT            |\n");
        printf("+----------------------------------------+\n");

        while (1)
        {
                printf("  Name  : ");
                if (scanf(" %19[a-zA-Z ]", new_c->name) == 1)
                {
                        while ((ch = getchar()) != '\n' && ch != EOF);

                        int i = 0, j = 0;
                        char tmp[20];

                        while (new_c->name[i] != '\0')
                        {
                                if (new_c->name[i] == ' ' &&
                                    (i == 0 || new_c->name[i - 1] == ' '))
                                {
                                        i++;
                                        continue;
                                }
                                tmp[j++] = new_c->name[i++];
                        }

                        if (j > 0 && tmp[j - 1] == ' ')
                                j--;

                        tmp[j] = '\0';

                        if (strlen(tmp) == 0)
                        {
                                printf("  [Error] Name cannot be empty.\n");
                                continue;
                        }

                        strcpy(new_c->name, tmp);
                        break;
                }

                printf("  [Error] Enter a name using letters only.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
        }

        while (1)
        {
                char temp[30];

                printf("  Phone : ");
                if (scanf(" %29[0-9]", temp) != 1)
                {
                        printf("  [Error] Enter digits only.\n");
                        while ((ch = getchar()) != '\n' && ch != EOF);
                        continue;
                }

                while ((ch = getchar()) != '\n' && ch != EOF);

                if (strlen(temp) != 10)
                {
                        printf("  [Error] Phone number must be 10 digits long.\n");
                        continue;
                }

                if (temp[0] < '6' || temp[0] > '9')
                {
                        printf("  [Error] Number must start with 6, 7, 8, or 9.\n");
                        continue;
                }

                int duplicate = 0;
                for (int i = 0; i < addressbook->contactcount; i++)
                {
                        if (strcmp(addressbook->contacts[i].phone, temp) == 0)
                        {
                                duplicate = 1;
                                break;
                        }
                }

                if (duplicate)
                {
                        printf("  [Error] This phone number already exists.\n");
                        continue;
                }

                strcpy(new_c->phone, temp);
                break;
        }

        while (1)
        {
                printf("  Email : ");
                if (scanf(" %19[a-zA-Z0-9@.]", new_c->mail) != 1)
                {
                        printf("  [Error] Enter a valid email address.\n");
                        while ((ch = getchar()) != '\n' && ch != EOF);
                        continue;
                }

                while ((ch = getchar()) != '\n' && ch != EOF);

                int at_count = 0;
                int at_index = -1;

                for (int i = 0; new_c->mail[i] != '\0'; i++)
                {
                        if (new_c->mail[i] == '@')
                        {
                                at_count++;
                                at_index = i;
                        }
                }

                if (at_count != 1 || at_index == 0)
                {
                        printf("  [Error] Enter a valid email with one '@'.\n");
                        continue;
                }

                int email_len = strlen(new_c->mail);
                const char *suffix = "@gmail.com";
                int suffix_len = strlen(suffix);

                if (email_len < suffix_len ||
                    strcmp(new_c->mail + email_len - suffix_len, suffix) != 0)
                {
                        printf("  [Error] Email must end with @gmail.com.\n");
                        continue;
                }

                int duplicate = 0;
                for (int i = 0; i < addressbook->contactcount; i++)
                {
                        if (strcmp(addressbook->contacts[i].mail, new_c->mail) == 0)
                        {
                                duplicate = 1;
                                break;
                        }
                }

                if (duplicate)
                {
                        printf("  [Error] This email already exists.\n");
                        continue;
                }

                break;
        }

        addressbook->contactcount++;

        printf("+----------------------------------------+\n");
        printf("|          CONTACT ADDED SUCCESSFULLY    |\n");
        printf("+----------------------------------------+\n");
        printf("  Name  : %s\n", new_c->name);
        printf("  Phone : %s\n", new_c->phone);
        printf("  Email : %s\n", new_c->mail);
        printf("+----------------------------------------+\n");
}

        

void searchContact(AddressBook *addressbook)
{
        if (addressbook == NULL) return;

        if (addressbook->contactcount == 0)
        {
                printf("\n[Error] Address book is empty!\n");
                return;
        }

        int choice;
        int ch;
        int found = 0;
        int result;
        char key[25];

        printf("\n+----------------------------------------+\n");
        printf("|             SEARCH CONTACT             |\n");
        printf("+----------------------------------------+\n");
        printf("  Search by: 1. Name  2. Phone  3. Email\n");
        printf("  Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
                printf("\n[Error] Enter numbers 1, 2, or 3 only.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                return;
        }

        while ((ch = getchar()) != '\n' && ch != EOF);

        if (choice < 1 || choice > 3)
        {
                printf("\n[Error] Invalid option.\n");
                return;
        }

        printf("  Enter search key: ");

        switch (choice)
        {
        case 1:
                result = scanf(" %24[a-zA-Z ]", key);
                break;
        case 2:
                result = scanf(" %24[0-9]", key);
                break;
        case 3:
                result = scanf(" %24[a-zA-Z0-9@.]", key);
                break;
        }

        if (result != 1)
        {
                printf("\n[Error] Invalid search input.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                return;
        }

        while ((ch = getchar()) != '\n' && ch != EOF);

        for (int i = 0; i < addressbook->contactcount; i++)
        {
                if ((choice == 1 && strcmp(addressbook->contacts[i].name, key) == 0) ||
                    (choice == 2 && strcmp(addressbook->contacts[i].phone, key) == 0) ||
                    (choice == 3 && strcmp(addressbook->contacts[i].mail, key) == 0))
                {
                        if (found == 0)
                        {
                                printf("\n+------+----------------------+--------------+---------------------------+\n");
                                printf("| %-4s | %-20s | %-12s | %-25s |\n",
                                       "No.", "Name", "Phone", "Email");
                                printf("+------+----------------------+--------------+---------------------------+\n");
                        }

                        printf("| %-4d | %-20.20s | %-12.12s | %-25.25s |\n",
                               i + 1,
                               addressbook->contacts[i].name,
                               addressbook->contacts[i].phone,
                               addressbook->contacts[i].mail);

                        found = 1;
                }
        }

        if (found)
        {
                printf("+------+----------------------+--------------+---------------------------+\n");
        }
        else
        {
                printf("\n[Error] No matching contact found.\n");
        }
}

// ...existing code...
void EditContact(AddressBook *addressbook)
{
        if (addressbook == NULL || addressbook->contactcount == 0)
        {
                printf("\n[Error] Address book is empty!\n");
                return;
        }

        int searchOption, option;
        int found_index = -1;
        int ch, result;
        char key[25];

        printf("\n+----------------------------------------+\n");
        printf("|              EDIT CONTACT              |\n");
        printf("+----------------------------------------+\n");
        printf("  Search by: 1. Name  2. Phone  3. Email\n");
        printf("  Enter choice: ");

        if (scanf("%d", &searchOption) != 1)
        {
                printf("\n[Error] Enter a valid choice.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                return;
        }

        while ((ch = getchar()) != '\n' && ch != EOF);

        if (searchOption < 1 || searchOption > 3)
        {
                printf("\n[Error] Invalid choice.\n");
                return;
        }

        printf("  Enter search key: ");

        switch (searchOption)
        {
        case 1:
                result = scanf(" %24[a-zA-Z ]", key);
                break;
        case 2:
                result = scanf(" %24[0-9]", key);
                break;
        case 3:
                result = scanf(" %24[a-zA-Z0-9@.]", key);
                break;
        }

        if (result != 1)
        {
                printf("\n[Error] Invalid search input.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                return;
        }

        while ((ch = getchar()) != '\n' && ch != EOF);

        for (int i = 0; i < addressbook->contactcount; i++)
        {
                if ((searchOption == 1 && strcmp(addressbook->contacts[i].name, key) == 0) ||
                    (searchOption == 2 && strcmp(addressbook->contacts[i].phone, key) == 0) ||
                    (searchOption == 3 && strcmp(addressbook->contacts[i].mail, key) == 0))
                {
                        found_index = i;
                        break;
                }
        }

        if (found_index == -1)
        {
                printf("\n[Error] Contact not found.\n");
                return;
        }

        printf("\n+------+----------------------+--------------+---------------------------+\n");
        printf("| %-4s | %-20s | %-12s | %-25s |\n",
               "No.", "Name", "Phone", "Email");
        printf("+------+----------------------+--------------+---------------------------+\n");
        printf("| %-4d | %-20.20s | %-12.12s | %-25.25s |\n",
               found_index + 1,
               addressbook->contacts[found_index].name,
               addressbook->contacts[found_index].phone,
               addressbook->contacts[found_index].mail);
        printf("+------+----------------------+--------------+---------------------------+\n");

        printf("\n  Edit: 1. Name  2. Phone  3. Email\n");
        printf("  Enter choice: ");

        if (scanf("%d", &option) != 1)
        {
                printf("\n[Error] Enter a valid choice.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                return;
        }

        while ((ch = getchar()) != '\n' && ch != EOF);

        if (option < 1 || option > 3)
        {
                printf("\n[Error] Invalid choice.\n");
                return;
        }

        char temp_input[30];

        switch (option)
        {
        case 1:
                printf("  Enter new name: ");
                if (scanf(" %19[a-zA-Z ]", temp_input) != 1)
                {
                        printf("\n[Error] Enter a name using letters only.\n");
                        while ((ch = getchar()) != '\n' && ch != EOF);
                        return;
                }

                while ((ch = getchar()) != '\n' && ch != EOF);

                int i = 0, j = 0;
                char tmp[20];

                while (temp_input[i] != '\0')
                {
                        if (temp_input[i] == ' ' &&
                            (i == 0 || temp_input[i - 1] == ' '))
                        {
                                i++;
                                continue;
                        }
                        tmp[j++] = temp_input[i++];
                }

                if (j > 0 && tmp[j - 1] == ' ')
                        j--;

                tmp[j] = '\0';

                if (strlen(tmp) == 0)
                {
                        printf("\n[Error] Name cannot be empty.\n");
                        return;
                }

                strcpy(addressbook->contacts[found_index].name, tmp);
                printf("\nName updated successfully!\n");
                break;

        case 2:
                while (1)
                {
                        printf("  Enter new phone number: ");

                        if (scanf(" %29[0-9]", temp_input) != 1)
                        {
                                printf("\n[Error] Enter digits only.\n");
                                while ((ch = getchar()) != '\n' && ch != EOF);
                                continue;
                        }

                        while ((ch = getchar()) != '\n' && ch != EOF);

                        if (strlen(temp_input) != 10)
                        {
                                printf("\n[Error] Phone number must be 10 digits long.\n");
                                continue;
                        }

                        if (temp_input[0] < '6' || temp_input[0] > '9')
                        {
                                printf("\n[Error] Number must start with 6, 7, 8, or 9.\n");
                                continue;
                        }

                        int duplicate = 0;
                        for (int i = 0; i < addressbook->contactcount; i++)
                        {
                                if (i != found_index &&
                                    strcmp(addressbook->contacts[i].phone, temp_input) == 0)
                                {
                                        duplicate = 1;
                                        break;
                                }
                        }

                        if (duplicate)
                        {
                                printf("\n[Error] This phone number already exists.\n");
                                continue;
                        }

                        strcpy(addressbook->contacts[found_index].phone, temp_input);
                        printf("\nPhone number updated successfully!\n");
                        break;
                }
                break;

        case 3:
                while (1)
                {
                        printf("  Enter new email: ");

                        if (scanf(" %19[a-zA-Z0-9@.]", temp_input) != 1)
                        {
                                printf("\n[Error] Enter a valid email address.\n");
                                while ((ch = getchar()) != '\n' && ch != EOF);
                                continue;
                        }

                        while ((ch = getchar()) != '\n' && ch != EOF);

                        int at_count = 0;
                        int at_index = -1;

                        for (int i = 0; temp_input[i] != '\0'; i++)
                        {
                                if (temp_input[i] == '@')
                                {
                                        at_count++;
                                        at_index = i;
                                }
                        }

                        if (at_count != 1 || at_index == 0)
                        {
                                printf("\n[Error] Enter an email with one '@'.\n");
                                continue;
                        }

                        int email_len = strlen(temp_input);
                        const char *suffix = "@gmail.com";
                        int suffix_len = strlen(suffix);

                        if (email_len < suffix_len ||
                            strcmp(temp_input + email_len - suffix_len, suffix) != 0)
                        {
                                printf("\n[Error] Email must end with @gmail.com.\n");
                                continue;
                        }

                        int duplicate = 0;
                        for (int i = 0; i < addressbook->contactcount; i++)
                        {
                                if (i != found_index &&
                                    strcmp(addressbook->contacts[i].mail, temp_input) == 0)
                                {
                                        duplicate = 1;
                                        break;
                                }
                        }

                        if (duplicate)
                        {
                                printf("\n[Error] This email already exists.\n");
                                continue;
                        }

                        strcpy(addressbook->contacts[found_index].mail, temp_input);
                        printf("\nEmail updated successfully!\n");
                        break;
                }
                break;
        }

        printf("\n+----------------------------------------+\n");
        printf("|             CONTACT UPDATED            |\n");
        printf("+----------------------------------------+\n");
}
void DeleteContact(AddressBook *addressbook)
{
        if (addressbook == NULL || addressbook->contactcount == 0)
        {
                printf("\n[Error] Address book is empty!\n");
                return;
        }

        char key[25];
        int target = -1;
        int ch;

        printf("\n+----------------------------------------+\n");
        printf("|              DELETE CONTACT            |\n");
        printf("+----------------------------------------+\n");
        printf("  Enter name or phone number: ");

        if (scanf(" %24[a-zA-Z0-9 ]", key) != 1)
        {
                printf("\n[Error] Invalid input!\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                return;
        }

        while ((ch = getchar()) != '\n' && ch != EOF);

        for (int i = 0; i < addressbook->contactcount; i++)
        {
                if (strcmp(addressbook->contacts[i].name, key) == 0 ||
                    strcmp(addressbook->contacts[i].phone, key) == 0)
                {
                        target = i;
                        break;
                }
        }

        if (target == -1)
        {
                printf("\n[Error] Contact not found!\n");
                return;
        }

        printf("\n+------+----------------------+--------------+---------------------------+\n");
        printf("| %-4s | %-20s | %-12s | %-25s |\n",
               "No.", "Name", "Phone", "Email");
        printf("+------+----------------------+--------------+---------------------------+\n");
        printf("| %-4d | %-20.20s | %-12.12s | %-25.25s |\n",
               target + 1,
               addressbook->contacts[target].name,
               addressbook->contacts[target].phone,
               addressbook->contacts[target].mail);
        printf("+------+----------------------+--------------+---------------------------+\n");

        for (int i = target; i < addressbook->contactcount - 1; i++)
        {
                addressbook->contacts[i] = addressbook->contacts[i + 1];
        }

        int last_index = addressbook->contactcount - 1;
        addressbook->contacts[last_index].name[0] = '\0';
        addressbook->contacts[last_index].phone[0] = '\0';
        addressbook->contacts[last_index].mail[0] = '\0';

        addressbook->contactcount--;

        printf("\n+----------------------------------------+\n");
        printf("|          CONTACT DELETED SUCCESSFULLY  |\n");
        printf("+----------------------------------------+\n");
}


void saveContactsToFile(AddressBook *addressbook)
{
        if (addressbook == NULL) return;

        FILE *fp = fopen("contacts.txt", "w");
        if (fp == NULL)
        {
                printf("\n[Error] Unable to open contacts.txt for writing.\n");
                return;
        }

        fprintf(fp, "%d\n", addressbook->contactcount);

        for (int i = 0; i < addressbook->contactcount; i++)
        {
                fprintf(fp, "%s,%s,%s\n", 
                        addressbook->contacts[i].name, 
                        addressbook->contacts[i].phone, 
                        addressbook->contacts[i].mail);
        }

        fclose(fp);
}

void loadContactsFromFile(AddressBook *addressbook)
{
        if (addressbook == NULL) return;

        FILE *fp = fopen("contacts.txt", "r");
        if (fp == NULL)
        {
                addressbook->contactcount = 0;
                return;
        }

        if (fscanf(fp, "%d\n", &addressbook->contactcount) != 1)
        {
                addressbook->contactcount = 0;
                fclose(fp);
                return;
        }
        if (addressbook->contactcount > MAX_CONTACTS)
        {
                addressbook->contactcount = MAX_CONTACTS;
        }

        for (int i = 0; i < addressbook->contactcount; i++){
                if (fscanf(fp, " %19[^,],%10[^,],%19[^\n]\n", 
                           addressbook->contacts[i].name, 
                           addressbook->contacts[i].phone, 
                           addressbook->contacts[i].mail) != 3)
                {
                        addressbook->contactcount = i;
                        break;
                }
        }

        fclose(fp);
}

void SaveandExit(AddressBook *addressbook)
{
        if (addressbook == NULL) return;

        saveContactsToFile(addressbook);
        printf("\nAll contacts saved successfully, Exiting AddressBook.\n");
        exit(0);
}