#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <conio.h>

// Accomodation struct
typedef struct accomodation
{
	int id;
	char firstName[30];
	char secondName[30];
	int year;
	float monthlyRent;
	char email[50];
	int type;
	int numOfRooms;
	int pets;
	int duration;
	struct accomodation* NEXT;
}accomodationT;

// Login struct
typedef struct login
{
	char user[50];
	char pass[50];
	struct login* NEXT;
}loginT;

// List of methods
int login(loginT** top);
void menu();
void addAccomodation(accomodationT** top);
void addWithData(accomodationT** top, int id, char firstName[30], char secondName[30], int year, float monthlRent, char email[50], int type, int numOfRooms, int pets, int duration);
void displayAll(accomodationT* top);
void displaySpecific(accomodationT* top);
void update(accomodationT* top);
void deleteAcc(accomodationT** top);
void generateStatistics(accomodationT* top);
void printData(accomodationT* top);
void check_id(accomodationT** top);
void check_email(accomodationT* top);
void enter_details(accomodationT* top);
void select_details(accomodationT* top);
void display(accomodationT* top);
void saveData(accomodationT* top);
void sortByRent(accomodationT** top);
void swapFunction(accomodationT* a, accomodationT* b);

// Main method
void main()
{
	accomodationT* headPtr = NULL;
	loginT* headPtrL = NULL;
	FILE* file1;
	int userChoice = 0;
	file1 = fopen("dataValue.txt", "r");

	int id, y, t, no, p, d;
	char n[30];
	char s[30];
	char e[50];
	float r;
	int log = 1;

	while(log != 0)
	{
		log = login(&headPtrL);
	}

	if (file1 != NULL)
	{
		// Load data
		while (!feof(file1))
		{
			fscanf(file1, "%d %s %s %d %f %s %d %d %d %d\n", &id, n, s, &y, &r, e, &t, &no, &p, &d);
			addWithData(&headPtr, id, n, s, y, r, e, t, no, p, d);
		}
	}
	while (userChoice != -1)
	{
		menu();
		scanf("%d", &userChoice);

		if (userChoice == 1)
		{
			//check_id(&headPtr);
			addAccomodation(&headPtr);
			saveData(headPtr);
		}
		else if (userChoice == 2)
		{
			displayAll(headPtr);
		}
		else if (userChoice == 3)
		{
			displaySpecific(headPtr);
		}
		else if (userChoice == 4)
		{
			update(headPtr);
			saveData(headPtr);
		}
		else if (userChoice == 5)
		{
			deleteAcc(&headPtr);
			saveData(headPtr);
		}
		else if (userChoice == 6)
		{
			generateStatistics(headPtr);
		}
		else if (userChoice == 7)
		{
			printData(headPtr);
		}
		else if (userChoice == 8)
		{
			sortByRent(&headPtr);
			printf("SORTED BY ORDER OF MONTHLY RENT\n");
			displayAll(headPtr);
		}
		
	}
}
// Compares usernames and passwords
int login(loginT** top)
{
	FILE* loginFile;
	loginT* loginVar;
	loginFile = fopen("login.txt", "r");
	char userName[50];
	char password[50];
	bool valid = false;
	char c;
	int i = 0;
	printf("|------------------------------ LOGIN ---------------------------|\n\n");
	printf("USERNAME:");
	scanf("%s", userName);
	printf("PASSWORD:");
	//Password shows an * instead of characters
	//Infinte loop that checks ASCII characters and breaks if user press enter 
	while (i < strlen(password)) 
	{
		c = getch();
		// if user press Enter key
		if (c == 13) 
		{ 
			password[i] = '\0';
			break;
		}
		// if user press Backspace key
		else if (c == 8) 
		{ 
			if (i > 0) 
			{
				i--;
				printf("\b \b"); 
			}
		}
		// else display *
		else 
		{
			password[i] = c;
			i++;
			printf("*");
		}
	}
	printf("\n\n");

	// Scan login file
	while (!feof(loginFile))
	{
		loginVar = (loginT*)malloc(sizeof(loginT));
		fscanf(loginFile, "%s %s\n", &loginVar->user, &loginVar->pass);

		// Compare username and password with the file
		if (strcmp(userName, loginVar->user) == 0 && strcmp(password, loginVar->pass) == 0)
		{
			printf("Access granted!\n\n");
			valid = true;
		}
		loginVar = loginVar->NEXT;
	}
	fclose(loginFile);
	if (valid == false)
	{
		printf("Invalid login!\n\n");
		return 1;
	}
	else
	{
		return 0;
	}

}
// Display menu
void menu()
{
	printf("Select one of the following options:\n\n");
	printf("|------------------------------ MENU ---------------------------|\n");
	printf("\t1. Add accomodation											\n");
	printf("\t2. Display all accomodation									\n");
	printf("\t3. Display an accomodation detail								\n");
	printf("\t4. Update accomodation parameters								\n");
	printf("\t5. Delete accomodation										\n");
	printf("\t6. Generate statistics										\n");
	printf("\t7. Print all accomodation details into a report file			\n");
	printf("\t8. List all the accomodation in order of monthly rental		\n");
	printf("\t-1. EXIT														\n");
	printf("|------------------------------ MENU ---------------------------|\n");
}
// Add accomodation
void addAccomodation(accomodationT** top)
{
	accomodationT* temp;
	accomodationT* temp2;
	FILE* dataFile;

	dataFile = fopen("dataValue.txt", "a");

	temp = (accomodationT*)malloc(sizeof(accomodationT));
	temp2 = (accomodationT*)malloc(sizeof(accomodationT));
	printf("ADD ACCOMODATION\n");

	// Call methods
	//check_id(temp, temp2);
	enter_details(temp);
	check_email(temp);
	select_details(temp);
	temp->NEXT = *top;
	*top = temp;
	//numOfAcc++;
	fclose(dataFile);
}
// Load accomodation
void addWithData(accomodationT** top, int id, char n[30], char s[30], int y, float r, char e[50], int t, int no, int p, int d)
{
	accomodationT* newNode;
	accomodationT* temp;

	newNode = (accomodationT*)malloc(sizeof(accomodationT));
	newNode->id = id;
	strcpy(newNode->firstName, n);
	strcpy(newNode->secondName, s);
	newNode->year = y;
	newNode->monthlyRent = r;
	strcpy(newNode->email, e);
	newNode->type = t;
	newNode->numOfRooms = no;
	newNode->pets = p;
	newNode->duration = d;

	//idArray[numOfAcc] = id;
	//numOfAcc++;
	newNode->NEXT = *top;
	*top = newNode;
	
}
// Display all
void displayAll(accomodationT* top)
{
	accomodationT* temp;
	temp = top;

	printf("DISPLAY ALL ACCOMODATION\n");

	if (temp == NULL)
	{
		printf("There is no data in this database.\n\n");
	}
	while (temp != NULL)
	{
		display(temp);
		temp = temp->NEXT;
	}
}
// Display specific
void displaySpecific(accomodationT* top)
{
	accomodationT* temp;
	temp = top;

	int userInputID = 0;
	bool found = false;

	printf("DISPLAY SPECIFIC ACCOMODATION\n");
	printf("Enter the Property ID number:\n");
	scanf("%d", &userInputID);
	while (temp != NULL)
	{
		if (userInputID == temp->id)
		{
			found = true;
			display(temp);
		}
		temp = temp->NEXT;
	}
	if (found == false)
	{
		printf("This ID number does not exist!\n");
	}
}
// Display function
void display(accomodationT* top)
{
	accomodation* temp = top;

	printf("\nACCOMODATION\n");
	printf("ID Number: %d\n", temp->id);
	printf("Owner Name: %s %s\n", temp->firstName, temp->secondName);
	printf("Year: %d\n", temp->year);
	printf("Monthly Rental: %.2f\n", temp->monthlyRent);
	printf("Email Address: %s\n", temp->email);
	printf("Type of Rental: ");
	if (temp->type == 1)
		printf("Single\n");
	else if (temp->type == 2)
		printf("Appartment\n");
	else if (temp->type == 3)
		printf("Bungalow\n");
	else if (temp->type == 4)
		printf("Two Story\n");
	else
		printf("\n");

	printf("Number of bedrooms: %d\n", temp->numOfRooms);

	printf("Pets allowed: ");
	if (temp->pets == 1)
		printf("Yes\n");
	else
		printf("No\n");

	printf("Average duration of the stay: ");
	if (temp->duration == 1)
		printf("One day\n");
	if (temp->duration == 2)
		printf("Less than 3 days\n");
	if (temp->duration == 3)
		printf("Less than 7 days\n");
	if (temp->duration == 4)
		printf("More than 7 days\n");
	else
		printf("\n");
}
// Update function
void update(accomodationT* top)
{
	accomodationT* temp;
	accomodationT* temp2;
	temp = top;
	int userInput;
	bool found = false;

	printf("UPDATE SPECIFIC ACCOMODATION\n");
	printf("Enter the ID number of property you want to update:\n");
	scanf("%d", &userInput);

	while (temp != NULL)
	{
		if (userInput == temp->id)
		{	
			found = true;
			break;
		}
		temp = temp->NEXT;
	}
	temp = top;

	if (found == false)
	{
		printf("This ID number does not exist!\n");
	}
	else
	{
		while (temp != NULL)
		{
			if (temp->id == userInput)
			{
				//check_id(temp, temp2);
				enter_details(temp);
				check_email(temp);
				select_details(temp);
				break;
			}
		}
	}
}
// Delete specific
void deleteAcc(accomodationT** top)
{
	int userChoice;

	printf("DELETE SPECIFIC ACCOMODATION\n");
	printf("Enter the ID number of property you want to delete:\n");
	scanf("%d", &userChoice);

	// If no data in the list
	if (*top == NULL) {
		printf("There is no data in this database!\n");
		return;
	}

	// If id number is same as user choice
	accomodationT* temp = *top;
	if (temp->id == userChoice) 
	{
		*top = temp->NEXT;
		free(temp);
	}

	accomodationT* tempCurrent = *top;
	while (tempCurrent->NEXT != NULL && tempCurrent->NEXT->id != userChoice) {
		tempCurrent = tempCurrent->NEXT;
	}

	if (tempCurrent->NEXT == NULL) {
		printf("This accomodation does not exist!\n");
		return;
	}

	accomodationT* tempDelete = tempCurrent->NEXT;
	tempCurrent->NEXT = tempDelete->NEXT;
	free(tempDelete);
}
// Generate statistics
void generateStatistics(accomodationT* top)
{
	{
		accomodationT* temp = top;
		float minRent;
		float maxRent;
		float totalNumOfAcc = 0;

		float singleTotal = 0;
		float apartmentTotal = 0;
		float bungalowTotal = 0;
		float twoStoryTotal = 0;

		// User enters minimum rental
		printf("Please enter the minimun rental price for accomodations you are looking for: ");
		scanf("%f", &minRent);
		printf("\n");

		// User enters maximum rental
		printf("Penter the maximun rental price for accomodations you are looking for: ");
		scanf("%f", &maxRent);
		printf("\n");

		while (temp != NULL)
		{
			if (temp->monthlyRent >= minRent && temp->monthlyRent <= maxRent)
			{
				if (temp->type == 1)
				{
					singleTotal++;
				}

				else if (temp->type == 2)
				{
					apartmentTotal++;
				}

				else if (temp->type == 3)
				{
					bungalowTotal++;
				}

				else if (temp->type == 4)
				{
					twoStoryTotal++;
				}

				totalNumOfAcc++;
				temp = temp->NEXT;
			}

			else
			{
				temp = temp->NEXT;
			}
		}

		// Display
		printf("Statistics in percentages:\n");
		printf("Single: %.2f%%\n", singleTotal / totalNumOfAcc * 100);
		printf("Apartment: %.2f%%\n", apartmentTotal / totalNumOfAcc * 100);
		printf("Bungalow: %.2f%%\n", bungalowTotal / totalNumOfAcc * 100);
		printf("Two story: %.2f%%\n", twoStoryTotal / totalNumOfAcc *100);
		printf("\n");
	}
}
// Prints data to a file
void printData(accomodationT* top)
{
	accomodationT* temp;
	FILE* file1;
	temp = top;
	int i = 1;
	float totalNumOfAcc = 0;
	float singleTotal = 0;
	float apartmentTotal = 0;
	float bungalowTotal = 0;
	float twoStoryTotal = 0;

	file1 = fopen("DataFile.txt", "w");
	file1 = fopen("DataFile.txt", "a");
	if (temp == NULL)
	{
		printf("Databse empty.\n");
	}
	else
	{
		printf("File successfully printed.\n");
	}
	while (temp != NULL)
	{
		fprintf(file1, "\n***ACCOMODATION %d***\n", i);
		fprintf(file1, "--------------------------------------\n");
		fprintf(file1, "ID Number: %d\n", temp->id);
		fprintf(file1, "Owner Name: %s %s\n", temp->firstName, temp->secondName);
		fprintf(file1, "Year: %d\n", temp->year);
		fprintf(file1, "Monthly Rental: %.2f\n", temp->monthlyRent);
		fprintf(file1, "E-mail address: %s\n", temp->email);

		fprintf(file1, "Type of Rental: ");
		if (temp->type == 1)
			fprintf(file1, "Single\n");
		else if (temp->type == 2)
			fprintf(file1, "Appartment\n");
		else if (temp->type == 3)
			fprintf(file1, "Bungalow\n");
		else if (temp->type == 4)
			fprintf(file1, "Two Story\n");

		fprintf(file1, "Number of bedrooms: %d\n", temp->numOfRooms);

		fprintf(file1, "Pets allowed: ");
		if (temp->pets == 1)
			fprintf(file1, "Yes\n");
		else
			fprintf(file1, "No\n");

		fprintf(file1, "Average duration of the stay: ");
		if (temp->duration == 1)
			fprintf(file1, "One day\n");
		if (temp->duration == 2)
			fprintf(file1, "Less than 3 days\n");
		if (temp->duration == 3)
			fprintf(file1, "Less than 7 days\n");
		if (temp->duration == 4)
			fprintf(file1, "More than 7 days\n");

		temp = temp->NEXT;
		fprintf(file1, "--------------------------------------\n");
		i++;
	}
	temp = top;
	fprintf(file1, "--------------------------------------\n");
	fprintf(file1, "\n***GENERATED STATISTICS***\n");
	fprintf(file1, "--------------------------------------\n");
	while (temp != NULL)
	{
		if (temp->type == 1)
		{
			singleTotal++;
		}

		else if (temp->type == 2)
		{
			apartmentTotal++;
		}

		else if (temp->type == 3)
		{
			bungalowTotal++;
		}

		else if (temp->type == 4)
		{
			twoStoryTotal++;
		}

		totalNumOfAcc++;
		temp = temp->NEXT;
	}
	fprintf(file1, "Total number of accomodations: %.2f\n", totalNumOfAcc);
	fprintf(file1, "Single: %.2f%%\n", singleTotal / totalNumOfAcc * 100);
	fprintf(file1, "Apartment: %.2f%%\n", apartmentTotal / totalNumOfAcc * 100);
	fprintf(file1, "Bungalow: %.2f%%\n", bungalowTotal / totalNumOfAcc * 100);
	fprintf(file1, "Two Story: %.2f%%\n", twoStoryTotal / totalNumOfAcc * 100);
	fprintf(file1, "--------------------------------------\n");
	fclose(file1);
}
// Check if id is valid
void check_id(accomodationT** top)
{
	//accomodationT* temp = top;
	accomodationT* temp = *top;

	int userInput;
	bool validID = false;
	int userInuput;
	int id;

	while (validID == false || temp->id == 0)
	{
		printf("Please enter the property ID:\n");
		scanf("%d", &id);
		temp->id = id;

		validID = true;

		// Check if id number if bigger than 0
		if (temp->id <= 0)
		{
			printf("ID number must be value grater than 0!\n");
			validID = false;
		}
		/*
		while (temp2 != NULL)
		{
			if (temp2->id == id)
			{
				printf("Entered ID number is not unique!\n");
				validID = false;
				break;
			}
			temp2 = temp2->NEXT;
		}
		*/
	}
	//temp2->id = temp->id;
}
// Check if email is valid
void check_email(accomodationT* top)
{
	accomodationT* temp = top;
	bool validEmail = false;

	while (validEmail == false)
	{
		printf("Please enter the properys e-mail address:\n");
		scanf("%s", temp->email);

		for (int j = 0; j < strlen(temp->email); j++)
		{
			for (int x = 0; x < strlen(temp->email); x++)
			{
				// Check if email has the following characters: '@','.',"com"
				if (temp->email[j] == '@' && temp->email[x] == '.' && (strstr(temp->email, ".com") != NULL))
				{
					validEmail = true;
				}
			}
		}
		if (validEmail == false)
		{
			printf("Email address not valid!\n");
		}
	}
}
// Enter accomodation details
void enter_details(accomodationT* top)
{
	accomodationT* temp = top;

	printf("Please enter the property owners name:\n");
	scanf("%s %s", temp->firstName, temp->secondName);

	printf("Please enter the year property was built:\n");
	scanf("%d", &temp->year);

	printf("Please enter the propert monthly rent price:\n");
	scanf("%f", &temp->monthlyRent);

}
// Select accomodation details
void select_details(accomodationT* top)
{
	accomodationT* temp = top;

	do
	{
		printf("Select type of rental accomodation:\n");
		printf("\t1. Single Room\n");
		printf("\t2. Apartment\n");
		printf("\t3. Bungalow\n");
		printf("\t4. Two Story\n");
		scanf("%d", &temp->type);
		printf("%d", temp->type);
	} while (temp->type < 1 || temp->type > 4);

	do
	{ 
		printf("Select number of bedrooms available:\n");
		printf("\t1. 1 bedroom\n");
		printf("\t2. 2 bedrooms\n");
		printf("\t3. 3 bedrooms\n");
		printf("\t4. 4 bedrooms\n");
		printf("\t5. More than 4 bedrooms\n");
		scanf("%d", &temp->numOfRooms);
	} while (temp->numOfRooms < 1 || temp->numOfRooms > 5);

	do
	{
		printf("Are pets allowed:\n");
		printf("\t1. Yes\n");
		printf("\t2. No\n");
		scanf("%d", &temp->pets);
	} while (temp->pets < 1 || temp->pets > 2);

	do
	{
		printf("Select average duration of the stay:\n");
		printf("\t1. One day\n");
		printf("\t2. Less than 3 days\n");
		printf("\t3. Less than 7 days\n");
		printf("\t4. More than 7 days\n");
		scanf("%d", &temp->duration);
	} while (temp->duration < 1 || temp->duration > 4);
}
// Saves data to a file 
void saveData(accomodationT* top)
{
	accomodationT* temp = top;
	FILE* dataFile;

	dataFile = fopen("dataValue.txt", "w");
	while (temp != NULL)
	{
		fprintf(dataFile, "%d %s %s %d %f %s %d %d %d %d\n", temp->id, temp->firstName, temp->secondName, temp->year, temp->monthlyRent, temp->email, temp->type, temp->numOfRooms, temp->pets, temp->duration);
		temp = temp->NEXT;
	}
	fclose(dataFile);
}
// Bubble sort by monthly rent from lowest to highest
void sortByRent(accomodationT** top)
{
	int swap;
	accomodationT* temp;
	accomodation* temp2 = NULL;

	/* Checking for empty list */
	if (*top == NULL)
	{
		return;
	}
	do
	{
		swap = 0;
		temp = *top;

		while (temp->NEXT != temp2)
		{
			if (temp->monthlyRent > temp->NEXT->monthlyRent)
			{
				swapFunction(temp, temp->NEXT);
				swap = 1;
			}
			temp = temp->NEXT;
		}
		temp2 = temp;
	} while (swap);
}
// Swap the elements when bubble sorting
void swapFunction(accomodationT* a, accomodationT* b)
{
	//Property ID
	int id = a->id;
	a->id = b->id;
	b->id = id;
	//First Name
	char fName[20];
	strcpy(fName, a->firstName);
	strcpy(a->firstName, b->firstName);
	strcpy(b->firstName, fName);
	//Second Name
	char secondName[30];
	strcpy(secondName, a->secondName);
	strcpy(a->secondName, b->secondName);
	strcpy(b->secondName, secondName);
	//Year Built
	int year = a->year;
	a->year = b->year;
	b->year = year;
	//Monthly rent rate
	float monthlyRental = a->monthlyRent;
	a->monthlyRent = b->monthlyRent;
	b->monthlyRent = monthlyRental;
	//E-Mail
	char email[40];
	strcpy(email, a->email);
	strcpy(a->email, b->email);
	strcpy(b->email, email);
	//Accommodation type
	int type = a->type;
	a->type = b->type;
	b->type = type;
	//Bedroom availability
	int numOfRooms = a->numOfRooms;
	a->numOfRooms = b->numOfRooms;
	b->numOfRooms = numOfRooms;
	//Pets allowed
	int pets = a->pets;
	a->pets = b->pets;
	b->pets = pets;
	//Stay Duration
	int duration = a->duration;
	a->duration = b->duration;
	b->duration = duration;
}






	