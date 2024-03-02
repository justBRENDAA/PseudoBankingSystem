#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

void displayMenu(int&);
void accountSummary();
void depositAccount();
void withdrawAccount();
void idValidation(string&);
void displayAccountInfo(string);


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
			cout << "\nThank you for choosing Online Banking!\n\n";
		}
	} while (choice != QUIT_CHOICE);

	return 0;
}

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

void withdrawAccount() {
	string idNumSTR;

	cout << "Enter your 3 digit ID Number: ";
	cin >> idNumSTR;

	idValidation(idNumSTR);
}

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