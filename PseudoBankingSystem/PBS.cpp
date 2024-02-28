#include <iostream>
using namespace std;

void displayMenu(int&);
void accountSummary();
void depositAccount();
void withdrawAccount();


int main() {
	// CONSTANTS FOR MENU CHOICES
	const int ACC_SUMMARY_CHOICE = 1,
			  DEPOSIT_CHOICE = 2,
			  WITHDRAW_CHOICE = 3,
			  QUIT_CHOICE = 4;
	int choice;
	 
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

}

void depositAccount() {

}

void withdrawAccount() {

}