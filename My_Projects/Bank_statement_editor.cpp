/* 
Author: Jordan Cruickshank
Date last edit: 16/12/2020

Problem: Read bank statement, extract valuable data, make description clearer and/or print new statement to new file.

Description: This code will read a bank statemnt and add valuable data to arrys within a class. From there, the user is able to:
1. Display current balance
2. Display transations for a specified range
3. Display net spend
4. Redefine transaction descriptions
5. Print new statement to console
6. Print new statement to file of choice
7. The user can select 7 to exit the program.
*/

//----------libraries---------------

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//----------Class---------------

class transactions
{
private:
	string statement_name, transactionDate[90], transactionDescription[90], updated_transactionDescription[90];
	int counter = 0;
	int i = 0;
	double transaction_value[90], account_balance[90], net_spend;

public:
	transactions(); // line57
	transactions(string, string, string, double, double, string, int); // line 68
	void setDate(string, int); // line 79
	void setDescription(string, int); // line 84
	void setNewDescription(string, int); // line 90
	void setValue(double, int); // line 95
	void setBalance(double, int); // line 100
	void setNet(double); // line 105
	void setCounter(int); // line 110
	void setinFile(string); // line 115
	void readStatement(); // line 140
	string getinFile(); // line 197
	void printStatement(); // line 202
	void printRange(); // line 213
	void redefineDescription(); // line 246
	void getBalance(); // line 263
	void getNet(); // line 268
	int getCounter(); // line 275
	void printtoFile(); // line 280
};

transactions::transactions() // constructor
{
	transactionDate[i] = "date";
	transactionDescription[i] = "description";
	updated_transactionDescription[i] = transactionDescription[i];
	transaction_value[i] = -1;
	account_balance[i] = -1;
	statement_name = "bs.csv";
	counter = 0;
}

transactions::transactions(string date, string description, string new_description, double transaction_value_dub, double balance, string file, int i) // constructor
{
	transactionDate[i] = date;
	transactionDescription[i] = description;
	updated_transactionDescription[i] = new_description;
	transaction_value[i] = transaction_value_dub;
	account_balance[i] = balance;
	statement_name = file;
	counter = i; // number of transactions
}

void transactions::setDate(string date, int i) // store date for each transaction in array
{
	transactionDate[i] = date;
} 

void transactions::setDescription(string description, int i) // store description for each transaction in array
{
	transactionDescription[i] = description;
	setNewDescription(description, i); // triggers function to set the initial descriptions the most recent descriptions
}

void transactions::setNewDescription(string new_description, int i) // called by the redefinedescription() function to store the new description by user
{
	updated_transactionDescription[i] = new_description;
}

void transactions::setValue(double transaction_value_dub, int i) // strore transaction amount for each transaction in array
{
	transaction_value[i] = transaction_value_dub;
}

void transactions::setBalance(double balance, int i) // store balance before each transaction for each transaction in array
{
	account_balance[i] = balance;
}

void transactions::setNet(double net) // stores the value of the net sum of all transactions
{
	net_spend = net;
}

void transactions::setCounter(int i) // counter = the number of transactions
{
	counter = i;
}

void transactions::setinFile(string file) // prompts user to input the name of the file to be used and instructs user of requirements
{
	char ans_correct;


	cout << "-------Instructions-------" << endl;
	cout << "\nPlease enter the full name of the file containing your bank statement\n(e.g. BankStatement.csv)" << endl;
	cout << "Note: Please ensure your file is a .csv or .txt and contains only the bank statement information." << endl;
	cout << "Delete table descriptors if required" << endl;
	cout << "\nFile Name: ";
	cin >> file;

	cout << "Your input file is: " << file << ", is this correct? [y/n]" << endl; // ask user if info correct
	cin >> ans_correct;

	while (ans_correct != 'y' && ans_correct != 'Y' && ans_correct != 'n' && ans_correct != 'N') {
		cout << "ERROR32: Invalid Character. Please enter y or n" << endl;
		cin >> ans_correct;
	}
	if (ans_correct == 'y' || ans_correct == 'Y')
		statement_name = file;
	else
		setinFile(file); // restart function
}

void transactions::readStatement() // reads statement and defines private attributes in class by calling appropriate functions
{
	ifstream BankStatement;
	BankStatement.open(statement_name.c_str()) // converts string to char[]

	if (!BankStatement.is_open()) {
		cout << "ERROR33: File cannot be opened or is missing" << endl;
		cout << "It is possible the file is not in the correct folder, please ensure it is located in this project's folder.\n" << endl;
		setinFile(statement_name)
	}

	cout << "\nFile " << statement_name << " being read..." << endl;


	string date, type, description, value, balance, account_name, account_number, null_info;
	int i = 0;
	double temp, net = 0, value_dub, balance_dub;

	while (BankStatement.peek() != EOF) // keep reading till end of file
	{
		getline(BankStatement, date, ','); // get all text until next comma and assign to a string
		getline(BankStatement, type, ',');
		if (BankStatement.peek() == '"') { // some statements seperated by double quotes 
			getline(BankStatement, null_info, '"');
			getline(BankStatement, description, '"');
			getline(BankStatement, null_info, ',');
		}
		else
			getline(BankStatement, description, '"');

		getline(BankStatement, value, '"');
		getline(BankStatement, balance, '"');
		getline(BankStatement, account_name, '"');
		getline(BankStatement, account_number, '\n'); // end of line


		value_dub = stod(value); // convert string to double
		temp = value_dub; 
		net += temp
		balance_dub = stod(balance);

		setCounter(i); // feed values to classes for storage
		setDate(date, i);
		setDescription(description, i);
		setValue(value_dub, i);
		setBalance(balance_dub, i);


		i++; // repeat for next line

	}
	setNet(net);
	BankStatement.close(); // close file

	cout << "\nFile has been successfully read and is now closed" << endl; 
}

string transactions::getinFile() //
{
	return statement_name;
}

voide transactions::printStatement () // print out statement to console in condensed format from the input file
{
	for (int j = 0; j <= counter; j++)
	{
		if (transaction_value[j] < 0) // display cleanly if negative value
			cout << "\n" << transactionDate[j] << "  \"" << updated_transactionDescription[j] << "\"  " << char(156) << transaction_value[j] *(-1) << endl;
		else 
			cout << "\n" << transactionDate[j] << "  \"" << updated_transactionDescription[j] << "\"  " << char(156) << transaction_value[j] << endl;
	}
}

void transactions::printRange() // print out all transactions incoming or outgoing in a user specific range
{
	char polarity; //selects value dependant on + or -
	double min_amount, max_amount;

	cout << "\nWould you like to print incoming or outgoing transactions?" << endl;
	cout << "1. Incoming." << endl;
	cout << "2. Outgoing." << endl;
	cin >> polarity;

	cout << "\nPrint out transactions between (min): " << char(156);
	cin >> min_amount;
	cout << "and (max): " << char(156);
	cin >> max_amount;

	switch (polarity) {
		case '1': // display desired values
			for (int k = 0; k <= counter; k++) {
				if (transaction_value[k] >= min_amount && transaction_value[k] <= max_amount)
					cout << "\nDate: " << transactionDate[k] << ", Description: " << transactionDescription[k] << ", Amount: " << char(156) << transaction_value[k];
			}
			break;
		case '2':
			for (int k = 0; k <= counter; k++) {
				if (transaction_value[k] < min_amount && transaction_value[k] > max_amount)
					cout << "\nDate: " << transactionDate[k] << ", Description: " << transactionDescription[k] << ", Amount: " << char(156) << transaction_value[k];
			}
			break;
		default:
			cout << "\nERROR57: Invalid choice, please select either 1 or 2." << endl; //error catch	
	}
}

void transactions::redefineDescription() // function displays current description then prompts user to input new description of each transaction
{
	string new_description;

	cout << "\nPlease enter a description of each transaction as it is displayed" << endl;

	for (int k = 0; k <= counter; k++) {
		cout << "\nOn " << transactionDate[k] << "a transaction was made for the amount of " << char(156) << transaction_value[k] << endl;
		cout << "Current description: " << transactionDescription[k] << endl;
		cout << "New description: ";
		cin >> new_description;
		cout << endl;

		setNewDescription(new_description, k); // assigns new description to correct place in array
	}
}

void transactions::getBalance() // retrieves balance and prints to console
{
	cout << "\nYour current balance is: -" << char(156) << -account_balance[0] << endl;
}

void transactions::getNet() // retrieve net transaction value and prints to console
{
	if (net_spend < 0) // ensures correct syntax
		cout << "\nYour net spend is: -" << char(156) << -net_spend << endl;
	else cout << "Your net spend is: " << char(156) << net_spend << endl;
}

int transactions::getCounter() // returns the number of transactions
{
	return counter;
}

void transactions::printtoFile() // creates a new file and prints the cleaner statement to it (in csv) also provides summary at end of file
{
	ofstream NeatStatement;
	NeatStatement.open("new.txt");

	cout << "\nFile ready to print to: 'new.txt', located in project folder." << endl;

	for (int j = 0; j <= counter; j++) {
		NeatStatement << transactionDate[j] << ",  \"" << updated_transactionDescription[j] << "\",  " << transaction_value[j] << endl;
	}

	NeatStatement << "\nAccount balance at start of statement term: " << account_balance[counter] - transaction_value[counter] << "gbp" << endl;
	NeatStatement << "\nAccount balance at end of statement term: " << account_balance[0] << "gbp" << endl;
	NeatStatement << "\nNet spend over term: " << net_spend << "gbp" << endl;


	NeatStatement.close(); // close file
	cout << "\nFile successfully created, printed and closed." << endl; 
}

//-------Main-------

int main()
{
	string statement_name;
	transactions statement;
	char user_ans;

	statement.setinFile(statement_name); // calls function to let user input file name

	statement.readStatement(); // call statement reader function


	do {
		cout << "\n------------------------------\n" << endl; // relay options for user selection
		cout << "\nPlease select what you would like to do now: " << endl;
		cout << "1. Display current balance." << endl;
		cout << "2. Display transactions for a specific range." << endl;
		cout << "3. Display net spend." << endl;
		cout << "4. Redefine descriptions." << endl;
		cout << "5. Print new statement." << endl;
		cout << "6. Print new statement to a new file." << endl;
		cout << "7. End program.\n" << endl;
		cin >> user_ans;
		switch (user_ans) {
		case '1':
			statement.getBalance();
			break;
		case '2':
			statement.printRange();
			break;
		case '3':
			statement.getNet();
			break;
		case '4':
			statement.redefineDescription();
			break;
		case '5':
			statement.printStatement();
			break;
		case '6':
			statement.printtoFile();
			break;
		case '7':
			break;
		default:
			cout << "ERROR52: Invalid choice, please select a number between 1 and 7." << endl; // error catch							
		}

	} While (user_ans != '7');

	cout << "\n-------------Goodbye--------------" << endl;	

	return 0;
}