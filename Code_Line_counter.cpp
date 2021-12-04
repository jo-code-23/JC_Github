//Function
// This program will tell you how many lines of your code are contain code - "not counting lines containing only brackets or nothing at all!"

// instructions------------------------------------------------
// 1. copy and paste all code to a text file and call it "code"
// 2. make sure file is in same folder as this project
// 3. run and then check new file: "just_code.txt" to make sure its right

//Assumptions made---------------------------------------------
//comments are using the "//" format
// no line consists of '{' followed by code


#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

int main()
{
	char char1, char2;
	string code, code_check;
	int counter = 0;

	ifstream infile;
	infile.open("code.txt"); //open file to be read

	ofstream outfile;
	outfile.open("just_code.txt"); //create and open file to write to

	if (!infile.is_open()) { //error message
		cout << "Error: File is missing" << endl;
		cout << "It is possible the file is not in the correct folder, please ensure it is located in this project's folder." << endl;
	}


	while (!infile.eof()) // loop until end of file
	{
		getline(infile, code); // read line and assign it to a temporary string
		code_check = code; // while keeping that string intact incase it needs printed, define another string with same info
		code_check.erase(remove_if(code_check.begin(), code_check.end(), ::isspace), code_check.end()); // this deletes all empty space in the string
		char1 = code_check[0]; // set char1 as first non-space character in string
		if (char1 != '{' && char1 != '}' && char1 != '/' && size(code_check) != 0) // as long as that character is not a bracket or slash or non existant
		{
			outfile << code << endl; //print that line to new file
			counter++; //count that line
		}
		if (char1 == '}') // in the instance of a do while loop there can be an instance where a '}' is followed by code
		{
			char2 = code_check[1];
			if (char2 == 'w')
			{
				outfile << code << endl; //print and count the line in this instance
				counter++;
			}
		}
	}
	infile.close(); //close files
	outfile.close();

	cout << "Your file contains " << counter - 1 << " lines of code excluding empty lines and lines with only a bracket or comment" << endl; //your answer
		return 0;
}
