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