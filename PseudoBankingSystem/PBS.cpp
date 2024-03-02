/*
Homework: 2
Team:3
Team Members:
	- Brenda Luis: 33% Contribution
	- Hector Romero: 33% Contribution
	- Dante Rodriguez: 33% contribution

Submission Date: 01/23/2024
1.	DISPLAY THE ACCOUNT SUMMARY: This option allows the user to enter a 3-digit customer ID
	(e.g., 007 for the customer name James Bond). The program should read-in an appropriate dat
	file (e.g., Cust_007.txt) corresponding to the customer ID and display the account information,
	including the total account balance on the console. [10 points]

2.	DEPOSIT THE AMOUNT INTO THE ACCOUNT: This option allows the user to enter a 3-digit customer ID,
	add the requested amount at the end of the file, and save the file. The option should display
	the account information on the console, including the total account balance. [20 points]

3.	WITHDRAW THE AMOUNT FROM THE ACCOUNT: This option allows the user to enter a 3-digit customer ID,
	read the customer’s dat file, verify that the requested withdrawal is less than the account balance,
	and then add the withdrawal amount at the end of the file. The option should display the account
	information on the console, including the total account balance.

In case if the requested withdrawal exceeds the account balance, the program should display an error message
and terminate the transaction. [25 points]

4.	Quit the program: This option terminates the program. [5 points]
Four test files are provided to test your program. The dat files are named based on the customer id. For instance, the bank’s first customer is the book’s author, Tony Gaddis, and his customer ID is Cust_001. The dat file of his checking account is Cust_001.dat.
Input validations: The menu-based option should not allow any options other than 1 to 4 [10 points]. The program should not allow users to enter negative numbers [10 points]. As long as the user does not enter the correct values, the program should not move forward and keep asking the user to enter the correct values.


*/


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

void displayMenu(int&);             // display menu
void accountSummary();              // account summary choice
void depositAccount();              // deposit choice
void withdrawAccount();             // withdraw choice
void idValidation(string&);         // validate id
void displayAccountInfo(string);    // read from file and display summary
void getBalance(string, float&);    // read from file and get balance


int main() {
	// CONSTANTS FOR MENU CHOICES
	const int ACC_SUMMARY_CHOICE = 1,
			  DEPOSIT_CHOICE = 2,
			  WITHDRAW_CHOICE = 3,
			  QUIT_CHOICE = 4;
	int choice;
	
	do {
		// DISPLAY MENU AND OBTAIN USER CHOICE
		displayMenu(choice);

		// SWITCH STATEMENT TO SELECT APPROPRIATE FUNCTION
		switch (choice) {
		case ACC_SUMMARY_CHOICE:
			accountSummary();
			break;
		case DEPOSIT_CHOICE:
			depositAccount();
			break;
		case WITHDRAW_CHOICE:
			withdrawAccount();
			break;
		case QUIT_CHOICE:
			cout << "\n\nThank you for choosing Online Banking!\n\n";
			break;
		}
	} while (choice != QUIT_CHOICE);

	return 0;
}

// function to display menu and get user choice
void displayMenu(int& choice) {
	cout << "\n   Online Banking Menu\n"
		<< "--------------------------\n"
		<< "1. Display Account Summary\n"
		<< "2. Deposit into Account\n"
		<< "3. Withdraw from Account\n"
		<< "4. Quit the Program\n\n"
		<< "Enter your choice: ";

	cin >> choice;

	while (choice < 0 || choice > 4) {
		cout << "\nChoice must be between 1-4. Please try again.\n"
			<< "Enter your choice: ";

		cin >> choice;
	}
}

// account summary choice
void accountSummary(){
	string idNumSTR;
	
	cout << "\n\n         ACCOUNT SUMMARY\n"
		 << "----------------------------------\n";

	cout << "Enter your 3 digit ID Number: ";
	cin >> idNumSTR;

	idValidation(idNumSTR);
	
	string fileName = "Cust_" + idNumSTR + ".dat";

	displayAccountInfo(fileName);

}

// deposit account choice
void depositAccount() {
	string idNumSTR, date;
	float deposit;

	cout << "\n\n         ACCOUNT DEPOSIT\n"
		<< "----------------------------------\n";

	cout << "Enter your 3 digit ID Number: ";
	cin >> idNumSTR;

	idValidation(idNumSTR);

	string fileName = "Cust_" + idNumSTR + ".dat";   // file name

	cout << "Enter today's date (MM/DD/YY): ";
	cin >> date;

	cout << "Enter deposit amount: ";
	cin >> deposit;

	while (deposit <= 0) {
		cout << "\nError: Deposit amount must be greater than $0.\n"
			<< "Enter deposit amount: ";
		cin >> deposit;
	}

	fstream dataFile;
	dataFile.open(fileName, ios::app);        // file in append mode 

	if (dataFile) {
		dataFile << date << "\t" << deposit << endl;  // writes date and deposit amount with tab as separator ** if cursor is not on a newline in file it will cause error
		cout << "\n\tDeposit Successful.\n";
		dataFile.close();


		cout << "\n\n         ACCOUNT SUMMARY\n"
			<< "----------------------------------\n";
		displayAccountInfo(fileName);        // display account summary 
	}
}

// withdraw account choice
void withdrawAccount() {
	string idNumSTR, date;
	float balance = 0, withdrawal = 0, w_amount;

	cout << "\n\n         ACCOUNT WITHDRAWAL\n"            // menu header
		<< "----------------------------------\n";

	cout << "Enter your 3 digit ID Number: ";             // get id
	cin >> idNumSTR;
	
	idValidation(idNumSTR);                               // validate id

	string fileName = "Cust_" + idNumSTR + ".dat";        // create file name

	getBalance(fileName, balance);                        // get balance


	cout << "Enter today's date (MM/DD/YY): ";           // withdrawal date
	cin >> date;

	cout << "Enter withdrawal amount: ";                 // positive withdrawal amount
	cin >> w_amount;

	withdrawal -= w_amount;                              // negative withdrawal amount

	if (w_amount >= balance){
		cout << "\n\nError: Withdrawal amount must be less than account balance.";
		cout << "\nPress any key to return to the menu.\n\n";    // pause program 
		cin.ignore();
		cin.get();
	}
	else {
		fstream dataFile;
		dataFile.open(fileName, ios::app);        // file in append mode 
		
		dataFile << date << "\t" << withdrawal << endl;
		dataFile.close();

		cout << "\n\tWithdrawal Successful.\n\n";

		cout << "\n\n         ACCOUNT SUMMARY\n"
			<< "----------------------------------\n";
		displayAccountInfo(fileName);
	}
}

// validate id is 3 digits
void idValidation(string &idNumSTR) {
	int idLength;

	do {
		idLength = idNumSTR.length();

		if (idLength != 3) {
			cout << "\nError. ID number must be a three digit number."
				<< "\nEnter your 3 digit ID Number: ";
			cin >> idNumSTR;
		}

	} while (idLength != 3);
}

// display account info
void displayAccountInfo(string fileName) {
	string custName, date;
	float balance = 0, money;
	
	ifstream inFile;
	inFile.open(fileName);

	if (inFile){
		getline(inFile, custName); // gets entire first line with cust name

		cout << "\n  Account Holder: " << custName << endl << endl; // display cust name

		cout << "\tAccount Activity\n"
			 << "\t-----------------\n";
		while (inFile >> date) // gets the date
		{
			cout << "\t" << date << "   ";    // display date
			inFile >> money;                  // read in money amount
			cout << setw(7) << fixed << setprecision(2) << money << endl; // displays money activity 
			balance += money;                 // updates balance

		}

		cout << fixed << setprecision(2);
		cout << "\n  Your account balance is: $" << balance << endl << endl; // display balance

		inFile.close(); // close file 
		
	}

	else
		cout << "\nError: The ID number provided does not match any accounts in our system." << endl << endl;  // file not found with id num

	cout << "\nPress any key to return to the menu.\n\n";    // pause program 
	cin.ignore();
	cin.get( );
}

// get acc balance
void getBalance(string fileName, float& balance) {
	string trash;
	float money;

	ifstream inFile;
	inFile.open(fileName);

	if (inFile) {
		getline(inFile, trash); // read name and store in junk variable

		while (inFile >> trash) // read date and store in junk variable
		{
			inFile >> money;    // read in money amount
			balance += money;   // update balance

		}

		cout << fixed << setprecision(2);
		cout << "\nYour account balance is: $" << balance << endl << endl; // display balance

		inFile.close(); // close file 

	}
}