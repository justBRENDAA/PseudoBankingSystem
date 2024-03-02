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
	string idNumSTR;

	cout << "Enter your 3 digit ID Number: ";
	cin >> idNumSTR;

	idValidation(idNumSTR);
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
		getline(inFile, custName); // get first line of file containing customer name

		cout << "\n  Account Holder: " << custName << endl << endl; // displays name

		cout << "\tAccount Activity\n"
			 << "\t-----------------\n";
		while (inFile >> date) // gets the date
		{
			cout << "\t" << date << "   "; // displays date
			inFile >> money; // gets the money ammount
			cout << setw(5) << money << endl; // displays money transaction
			balance += money; // adds or subtracts to balance

		}

		cout << "\n  Your account balance is: $" << balance << endl << endl;

		inFile.close();
		
	}

	else
		cout << "\nError: The ID number provided does not match any accounts in our system." << endl << endl;

	cout << "\nPress any key to return to the menu.\n\n";
	cin.ignore();
	cin.get( );
}