# Accomodation_Rental
This code is a command-line application for managing accommodation rental data.
Accommodation Management System

This C program is designed to manage accommodation rental data. It uses a menu-driven approach to offer various functionalities for interacting with accommodation records. Accommodation data is stored in a linked list data structure.

Features:

User Authentication: Before accessing the system, users must log in with a valid username and password. User credentials are stored in a file named "login.txt".

Main Menu: After successful login, users can choose from the following options in the main menu:

Add accommodation: Add a new accommodation entry.
Display all accommodations: View details of all accommodations.
Display specific accommodation: Search for and display details of a specific accommodation by its ID.
Update accommodation: Modify information of a specific accommodation.
Delete accommodation: Remove a specific accommodation from the list.
Generate statistics: Compute and display statistics based on rental prices and accommodation types.
Print data: Save all accommodation details, along with statistics, to a report file named "DataFile.txt".
List by monthly rent: Sort accommodations in ascending order of monthly rent.
Data Persistence: Accommodation data is read from and saved to a file named "dataValue.txt" to ensure data persistence between program executions.
