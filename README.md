Description

This is a console-based Bank Client Management System implemented in C++. It allows managing bank client accounts efficiently, supporting essential operations such as adding, updating, deleting, and searching clients, as well as performing transactions like deposits and withdrawals. The system uses a file-based storage mechanism to persist client data across program runs.

This project demonstrates object management, file handling, and menu-driven user interaction in C++. It is designed for simplicity and clarity while providing real-world banking functionalities.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




Features

1-Client Management

A- Add New Client: Enter account number, PIN, name, phone, and initial balance.

B- Update Client: Modify client information safely after confirmation.

C- Delete Client: Delete accounts with confirmation, marking them before permanent removal.

D- Search Client: Quickly search by account number and display detailed info.

Duplicate Check: Prevents adding clients with duplicate account numbers.



//////////////////////////////////////////////////////////////////////////////////////////////////////



2-Transactions

A- Deposit Money: Add funds to a client’s account.

B- Withdraw Money: Withdraw funds with balance checks.

C- View Total Balances: Display all clients’ balances in a clean table format.



//////////////////////////////////////////////////////////////////////////////////////////////////////


3 - Data Handling

All client information is stored in ClientsData.txt using a custom delimiter (#//#) to separate fields.

Supports persistent storage, so data is saved and loaded automatically across sessions.



//////////////////////////////////////////////////////////////////////////////////////////////////////



4- User Interface

A- Menu-Driven Interface: Clear main menu and transaction menus for easy navigation.

B - Formatted Tables: Display client information in a structured, readable format.

C -Input Validation: Checks for correct input and prevents invalid operations.



//////////////////////////////////////////////////////////////////////////////////////////////////////

5 - Technologies

C++ Standard Library: vector, string, fstream, iomanip, limits

Console I/O: cin and cout for interaction

File Handling: Persistent storage using text files

File Structure

ClientsData.txt – stores all client records

main.cpp – contains all program logic including client management and transactions
