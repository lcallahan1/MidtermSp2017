// CS135 Project #1
// Math pratice for basic levels

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>//For RNG
#include <ctime> //RNG  need to seed system time for "truly" random numbers
//#include <iomanip>

using namespace std;

void studentTeacher();
void teacherMenu(int attempts);
void studentMenu();
void teacherSettings();
void writeFile(string filepath, string info);
string readFile(string filepath);
void operatorMenu(string name);
void levelMenu(string name, string mathtype);
void quiz(string mathType, int &score);
int randNum(int magnitude, bool negatives);


//main only used to initiate the first menu function
int main()
{
	studentTeacher();
	return 0;
}

void studentTeacher() // Student, teacher or quit: main menu
{
	const int INITIAL_ATTEMPT = 1; //declaring & assigning in same line, initialization

	int choice;
	bool quit = false;
	/*If using a menu function
	const int TEACHER_CHOICE = 1,
	STUDENT_CHOICE = 2 */
	while (!quit)  //bool shortcut allows us to not need quit == false, b/c bool (quit varible is a bool, expecting a bool in () )
	{
		//system("CLS"); ***need to figure out where to clear screen
		cout << "Main Menu" << endl
			<< "________________" << endl << endl
			<< "\n1. I am an instructor." << endl
			<< "2. I am a student." << endl
			<< "3. Quit." << endl << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			teacherMenu(INITIAL_ATTEMPT); //correct password parameter to get to teacher settings menu
			break;
		case 2:
			studentMenu();
			break;
		case 3:
			quit = true; //assignment
			break;
		default: //anything else, gives message
			cout << "Please enter either option 1, 2 or 3.\n";
		}
	}
}

void teacherMenu(int attempts)
{
	string password;
	cout << "(case-sensitive) Password, please: " << endl;

	cin >> password;

	if (password == "password") //password correct; == tests equality
	{
		teacherSettings(); //if password is correct, to teacher settings
	}
	else
	{
		if (attempts >= 3)//3 tries
		{
			cout << "Sorry, that password is wrong." << endl; //return to studentTeacher menu if pass wrong
			return;
		}
		else
		{
			teacherMenu(attempts + 1); //each attempt adds 1 to counter
		}
		return;
	}
}


void teacherSettings()//instructor settings
{
	int choice;
	int percentage = 0;
	cout << "Instructor Settings Menu" << endl
		<< "__________________________" << endl << endl;
	cout << "Please choose an option from the following:" << endl << endl;
	cout << "1. Set passing %" << endl; //currently only only option
										//maybe add option to update happy/crappy responses
	cin >> choice;

	switch (choice)
	{
	case 1:
		break;
	}
	if (choice == 1)
	{
		string percentage = readFile("storage/passing_percentage.txt");//read in percentage from file where it's stored
		cout << "The current percentage is " << percentage << "%, to what would you like to change the passing percentage?" << endl;
		cin >> percentage;
		cout << "The new percentage required to pass a level is " << percentage << "%." << endl; //display new percentage
		writeFile("storage/passing_percentage.txt", percentage);  //output new percentage/write to file
	}
}

//******************
// FILE I/O
//******************

void writeFile(string filepath, string info)
{
	ofstream outputFile; //declare 
	outputFile.open(filepath);//parameter is filepath variable
	outputFile << info; //output the new info to file
	outputFile.close(); //close file
	return;

}

string readFile(string filepath)
{
	ifstream inputFile; //declare
	string info; //file info is stored as a string
	inputFile.open(filepath); //parameter is variable filepath
	inputFile >> info; //reading info from the file
	inputFile.close();
	return info;
}

void studentMenu()
{
	ofstream outputFile;

	string name;
	cout << "Please enter your name with no spaces [first_last]: " << endl;
	cin >> name;
	outputFile.open("storage/users/" + name); //how to incorporate name as variable with the filestream
	operatorMenu(name); //no need for declaration/data type when calling function

}

void operatorMenu(string name)
{
	char choice; //choices set as letters, not integers


	cout << "Student Menu" << endl
		<< "______________" << endl << endl
		<< "Please enter an option from the following: A, S, M or D." << endl << endl
		<< "A. Addition (levels 1-4)" << endl
		<< "S. Subtraction (levels 1-4)" << endl
		<< "M. Multiplication (levels 1-4)" << endl
		<< "D. Division (levels 1-4)" << endl;

	cin >> choice;
	switch (choice)
	{
	case 'A':
		levelMenu(name, "addition"); //each menu parameter gives a menu with the 4 (8) level options 
		break;
	case 'S':
		levelMenu(name, "subtraction");
		break;
	case 'M':
		levelMenu(name, "multiplication");
		break;
	case 'D':
		levelMenu(name, "division");
		break;
	default:
		cout << "Please enter a valid selection: A, S, M or D.";
	}
}

void levelMenu(string name, string mathType)
{
	int percentage;
	int level;
	int levels[8]; // array!
	levels[0] = 0;
	cout << "Your unlocked levels: " << endl << endl;

	cin >> level;
	switch (level)
	{
	case 1:
		quiz(mathType, levels[0]);
		break;


	}
}

void quiz(string mathType, int &score) //we are passing scores in the array as a reference 
{
	int magnitude;
	bool negatives;
	magnitude = 1;
	negatives = 0;

	//randNum(magnitude, negatives);

	int num1;
	int num2;
	int answer;



}

//int randNum(int magnitude, bool negatives)
//{

	//if (level > 1)
	//{
		//const int MAX_VALUE = MAX_VALUE * level; // really ~ x10 to the level-1


	//}
	/*
	//random numbers for 1A
	const int MIN_VALUE = 0; //Make neg for B and add digits for 2-4
	const int MAX_VALUE = 9;
	//y = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE

	int num1;
	int num2;
	int answer;

	//need system time
	unsigned seed = time(0);

	//then seed the RMG
	srand(seed);

	num1 = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
	num2 = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
	answer = (num1 + num2);

	cout << num1 << "  +  " << num2 << "  =  " << endl;
	cin >> answer;

	if (answer == (num1 + num2))
	cout << "Correct!" << endl;
	else
	cout << "Incorrect. The answer is " << (num1 + num2) << "." << endl;

	//return num1, num2;
	*/
//}
/*
//array for level score keeping
const int LEVELS = 8; //array size
int scores[LEVELS]; //array has 8 elements
ofsteam outputFile;


*/