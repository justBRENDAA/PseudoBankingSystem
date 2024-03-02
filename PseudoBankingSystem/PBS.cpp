#include <iostream>
#include <string>
using namespace std;

void displayMenu(int&);
void accountSummary();
void depositAccount();
void withdrawAccount();
void idValidation(string&);


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
	
	cout << "Enter your 3 digit ID Number: ";
	cin >> idNumSTR;

	idValidation(idNumSTR);
	
}

void depositAccount() {
	cout << "you are in deposti to account\n";
	
	string idNumSTR;

	cout << "Enter your 3 digit ID Number: ";
	cin >> idNumSTR;

	idValidation(idNumSTR);
}

void withdrawAccount() {
	cout << "you are in withdraw account\n";

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