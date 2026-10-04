# Address Book

A menu-driven C application for managing contacts with input validation and file-based data persistence.

## Features

- List all saved contacts
- Create a new contact
- Search contacts by name, phone number, or email
- Edit existing contact details
- Delete contacts
- Save contacts to a file
- Load saved contacts when the application starts
- Input validation for contact details
- Menu-driven console interface


## Technical Concepts

- C programming
- Structures (`struct`)
- Arrays and strings
- Pointers and passing structures to functions using pointers
- Functions and modular programming
- Input validation
- File handling using `fopen()`, `fscanf()`, `fprintf()`, and `fclose()`
- Searching and updating records
- Persistent data storage
- Command-line menu-driven application

## Project Structure

Address_book/
├── main.c          # Program entry point and menu handling
├── contact.c       # Contact management and file operations
├── contact.h       # Structures, constants, and function declarations
├── contacts.txt    # Persistent contact data
├── README.md       # Project documentation
└── .gitignore      # Ignores generated files