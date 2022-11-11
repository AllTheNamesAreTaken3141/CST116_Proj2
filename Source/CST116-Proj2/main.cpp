// The main changes I made that involve your code are to make sure the user enters a number, and only asking the user what number they want to test when they decide to change it. I did my best to keep your code as intact as possible but a few things are changed:
// The whole process of printing a prompt, checking if it's a number within the right range, repeat if needed, etc. is a lot more tedious to rewrite, so I've moved it into its own function that just takes a prompt and a range as parameters.
// Not asking for a new number every time required a few more changes, but most of it is just updating the text for the menu and the other prompts. The only code change is that getData now uses a reference, not a return, since this makes it far easier for processMenuChoice to call it.

#pragma region libraries
#include <iostream>
#include <iomanip> // For tables.
#include <string> // String-specific functions. Mainly used for converting a number to a string.
#include <sstream> // Stringstreams are pretty much just couts that don't print to the console. Very useful sometimes.
#include <math.h> // Used for the floor function, which is the easiest way to check if a number is an integer.
using namespace std;
#pragma endregion

#pragma region functionDefinitions
bool isNumber(string);
void getIntegerInput(string, int&, int, int);
void displayMenu(int);
int readInput();
void getData(int&);
void processMenuChoice(int, int&);
void isPosNeg(int);
void isOddEven(int);
void findNumDigits(int);
void findDigitAtPosition(int);
void displayAdditionTable(int);
void displayMultiplicationTable(int);
#pragma endregion


int main()
{

	int menuSelection = 0, data;
	getData(data); // Start by immediately getting a number since we don't have one yet.
	while (menuSelection != 8)
	{
		displayMenu(data);
		menuSelection = readInput();

		// I removed the break statement here since it's actually not necessary. The loop will already end if menuSelection is 8, and processMenuChoice also doesn't do anything.

		processMenuChoice(menuSelection, data);
	}

	return 0;
}


// Returns true if the given string is a number, and false if it isn't.
bool isNumber(string str)
{
	istringstream iss(str); // Creates a new stringstream with the string in the input buffer (as if a user had just typed it in).
	float f;
	iss >> noskipws >> f; // Attempts to convert the string to a float. This won't throw an error if it fails, but it will set the stream's failbit to true. noskipws causes a failure if there's any leading whitespace.
	return (iss.eof() && !iss.fail()); // If the conversion consumed the entire string (meaning there was no trailing whitespace), and it didn't fail (meaning there wasn't any leading whitespace and the string was a number), return true; otherwise return false.
}

// This technically doesn't need to be a function, but I decided to make it one since like half the functions make the user input a number at some point. The first parameter is the prompt that is printed before getting the input, the second is the variable to put the number into, and the last two will specify a range (inclusive) of acceptable numbers if you use them.
void getIntegerInput(string prompt, int& dest, int min = 1, int max = -1)
{
	bool skipRangeCheck = (min > max);
	string input;
	float f;
	while (true)
	{
		cout << prompt;
		cin >> input;
		if (!isNumber(input))
		{
			cout << "You need to enter a number!" << endl;
			continue; // Skips the rest of the loop and goes back to the top
		}
		f = stof(input);
		if (floor(f) != f)
		{
			cout << "You need to enter an integer!" << endl;
			continue;
		}
		if (!((min <= f && f <= max) || skipRangeCheck))
		{
			cout << "You need to enter a number between " << min << " and " << max << "!" << endl;
			continue;
		}
		dest = f;
		return;
	}
}

// Menu now reminds the user what their number is.
void displayMenu(int data)
{
	cout << "What do you want to do with your number (" << data << ")?" << endl
		 << "1. Enter a new number." << endl
		 << "2. Check if the number is positive or negative." << endl
		 << "3. Check if the number is even or odd." << endl
		 << "4. Find the number of digits in the number." << endl
		 << "5. Find the digit at a certain position." << endl
		 << "6. Display an addition table from 0-10. " << endl
		 << "7. Display a multiplication table from 0-10." << endl
		 << "8. End program." << endl << endl;
	return;
}

int readInput()
{
	int choice = 1;
	getIntegerInput("Enter your choice: ", choice, 1, 8);
	return choice;
}

void getData(int& data) {
	getIntegerInput("What number do you want to test? ", data, -1000000, 1000000);
}

void processMenuChoice(int menuChoice, int& data) {
	switch (menuChoice) {
	case 1:
		getData(data);
		break;
	case 2:
		isPosNeg(data);
		break;
	case 3:
		isOddEven(data);
		break;
	case 4:
		findNumDigits(data);
		break;
	case 5:
		findDigitAtPosition(data);
		break;
	case 6:
		displayAdditionTable(data);
		break;
	case 7:
		displayMultiplicationTable(data);
		break;
	case 8:
		break;
	}
}

void isPosNeg(int val)
{
	if (val < 0) {
		cout << "Your number is negative." << endl;
	}
	else if (val > 0) {
		cout << "Your number is positive." << endl;
	}
	else {
		cout << "Your number is 0, and therefore neither positive nor negative." << endl;
	}
	cout << endl << "----------------" << endl << endl;
	return;
}

void isOddEven(int val)
{
	int temp = abs(val) % 2;
	if (temp == 1) {
		cout << "Your number is odd." << endl;
	}
	else if (temp == 0) {
		cout << "Your number is even." << endl;
	}
	cout << endl << "----------------" << endl << endl;
	return;
}

void findNumDigits(int val)
{
	// Yes, this is valid code. C++ ignores line breaks because you end each line with a semicolon. It's useful for things like this.
	cout << "Your number has "
		 << to_string(val).size() // Finding the number of digits in a number is surprisingly non-trivial. The best way I've found is to use to_string() to convert the number to a string, and then use .size() to find the length of the string.
		 << " digits."
		 << endl;

	cout << endl << "----------------" << endl << endl;
	return;
}

void findDigitAtPosition(int val)
{
	string vstr = to_string(val);
	int index;
	string suffix;
	getIntegerInput("What digit would you like to find? ", index, 1, vstr.length());

	// This is called a "ternary operator" and it's really just a more readable way of writing a big chain of else ifs. The formatting is [condition] ? [do if true] : [do if false, or another condition].
	index == 1 ? suffix = "st" :
		index == 2 ? suffix = "nd" :
		index == 3 ? suffix = "rd" :
		suffix = "th";

	index--; // String indices start at 0 just like everything else, so you have to subtract 0 to make everything line up.

	cout << "The " << index + 1 << suffix << " digit of your number is " << vstr[index] << "." << endl;
	cout << endl << "----------------" << endl << endl;
	return;
}

void displayAdditionTable(int val)
{
	cout << "Addition Table:" << endl;
	int col1width = to_string(val).length() + 3; // Add 3 more to fit the "+__"
	int col2width = to_string(val + 10).length(); // This will always be the result with the most digits.

	cout.setf(ios::left, ios::adjustfield);
	for (int i = 1; i <= 10; i++)
	{
		cout << "|" << setw(col1width) << to_string(val) + "+" + to_string(i) << "|" << setw(col2width) << to_string(val + i) << "|" << endl;
	}
	cout << endl << "----------------" << endl << endl;
	return;
}

void displayMultiplicationTable(int val)
{
	cout << "Multiplication Table:" << endl;
	int col1width = to_string(val).length() + 3; // Add 3 more to fit the "+__"
	int col2width = to_string(val * 10).length(); // This will always be the result with the most digits.

	cout.setf(ios::left, ios::adjustfield);
	for (int i = 1; i <= 10; i++)
	{
		cout << "|" << setw(col1width) << to_string(val) + "*" + to_string(i) << "|" << setw(col2width) << to_string(val * i) << "|" << endl;
	}
	cout << endl << "----------------" << endl << endl;
	return;
}