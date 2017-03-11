// CS135 Project #1
// Math pratice for basic levels

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>//For RNG
#include <ctime> //RNG  need to seed system time for "truly" random numbers
#include <cmath> 
//#include <iomanip>

using namespace std;

void studentTeacher(); //The "main menu", user chooses to continue as "student" or "teacher".
void teacherMenu(int attempts); // If teacher, user is prompted for password (max 3 attempts) and sent to teacherSettings.
void studentMenu(); // Prompts student for name, to access file for scores and such.
void teacherSettings(); // Option to change the percentage required for passing.
void writeFile(string filepath, string info); // function to write to file (used for percentage and scores)
void writeFile(string filepath, int scores[], int length);
string readFile(string filepath); // function to read info from file (same)
void operatorMenu(string name); // Menu for which to choose the operator (+, -, *, / or combo), uses student name (string).
void levelMenu(string name, char mathType, string mathPath);//Choose from available levels (1 plus any unlocked levels), uses student name and mathtyye from operator menu.
void quiz(char mathType, int &score); // Runs math quiz of appropriate operator, level and saves score in name file.
int randNum(int magnitude, bool negatives); //generates random number, proper number of digits and negative for B levels
int randNum(int min, int max); //same function, diff parameters, uses same min and max from previous
string crappyResponse(); // List of "wrong answer" responses, to display in random order.
string happyResponse(); // List of "correct answer" responses, to display in random order.



//main only used to initiate the first menu function and to seed RNG
int main()
{
	// Seed random number generator
	unsigned seed = time(0);
	srand(seed);

	studentTeacher();
	return 0;
}

void studentTeacher() // Student, teacher or quit: main menu
{
	const int INITIAL_ATTEMPT = 1; //initialization

	int choice;
	bool quit = false;
	while (!quit)  //bool shortcut allows us to not need quit == false, b/c bool (quit varible is a bool, expecting a bool in () )
	{
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
	cout << "Please enter your (case-sensitive) password, please: " << endl;
	cin >> password;
	if (password == "pass") //password correct; == tests equality
	{
		teacherSettings(); //if password is correct, to teacher settings menu
	}
	else
	{
		if (attempts >= 3)// Given a max of 3 tries
		{
			cout << "Sorry, that password is wrong." << endl; //return to studentTeacher menu if pass wrong 3 times
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
	cin >> choice;
	switch (choice)
	{
	case 1:
		break;
	}
	if (choice == 1) // If they wish to change the percentage required to pass...
	{
		string percentage = readFile("storage/passing_percentage.txt");//read in percentage from file where it's stored as a string only
		cout << "The current percentage is " << percentage << "%, to what would you like to change the passing percentage?" << endl;
		cin >> percentage; //new percentage
		cout << "The new percentage required to pass a level is " << percentage << "%." << endl; //display new percentage
		writeFile("storage/passing_percentage.txt", percentage);  //output new percentage, i.e. write to passing_percentage file
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

void writeFile(string filepath, int scores[], int length)
{
	ofstream outputFile;
	outputFile.open(filepath);
	for (int index = 0; index < length; index++)
	{
		outputFile << scores[index] << endl;
	}
	outputFile.close();
}

string readFile(string filepath)
{
	ifstream inputFile; //declare
	string info; //file info is stored as a string (always)
	inputFile.open(filepath); //parameter is variable filepath
	inputFile >> info; //reading info from the file
	inputFile.close();
	return info;
}

void studentMenu()
{
	//ofstream outputFile;

	string name;
	cout << "Please enter your name with no spaces and all lowercase [first_last]: " << endl;
	cin >> name;
	//outputFile.open("storage/users/" + name); //how to incorporate name as variable with the filestream
	operatorMenu(name); //no need for declaration/data type when calling function
}

void operatorMenu(string name)
{
	int choice; //options 1-5 (easier than char or string, consistancy)
	cout << "Student Menu" << endl
		<< "______________" << endl << endl
		<< "Please enter an option from the following: " << endl << endl
		<< "1. Addition (levels 1-5)" << endl
		<< "2. Subtraction (levels 1-5)" << endl
		<< "3. Multiplication (levels 1-5)" << endl
		<< "4. Division (levels 1-5)" << endl
		<< "5. Combination of all operators (levels 1-5)" << endl << endl;
	cin >> choice;
	switch (choice)
	{//each menu parameter gives a menu with the 5 (10, considering A & B) level options for chosen operator
	case 1:
		levelMenu(name, '+', "addition"); //addition
		break;
	case 2:
		levelMenu(name, '-', "subtraction"); //subtraction
		break;
	case 3:
		levelMenu(name, '*', "multiplication"); // multiplication
		break;
	case 4:
		levelMenu(name, '/', "division"); // division
		break;
	case 5:
		levelMenu(name, 'C', "combination"); // combination-- random display of all 4 operators
	default:
		cout << "Please enter a valid selection, 1-5."; // input needs to be 1 to 5
	}
}

void levelMenu(string name, char mathType, string mathPath) //student name, mathType is operator option
{
	//int percentage; 
	int level;
	const int TOTAL_LEVELS = 10;
	int levels[TOTAL_LEVELS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // array!

	cout << "Your unlocked levels: " << endl << endl;  //User sees only levels available to them (1 and those passed up to)
	//need to cout unlocked levels
	cin >> level; //chosen level
	if (level > 0 && level <= TOTAL_LEVELS) {
        quiz(mathType, levels[level - 1]);
	    writeFile("storage/" + mathPath + "/" + name + ".txt", levels, TOTAL_LEVELS);
	}
	else
	{
		cout << "Please enter a valid option, 1-11" << endl; // error message, level out of bounds
	}
	/*switch (level)
	{
	case 1:
		quiz(mathType, levels[0]);
		break;
	case 2:
		quiz(mathType, levels[1]);
		break;
	case 3:
		quiz(mathType, levels[2]);
		break;
	case 4:
		quiz(mathType, levels[3]);
		break;
	case 5:
		quiz(mathType, levels[4]);
		break;
	case 6:
		quiz(mathType, levels[5]);
		break;
	case 7:
		quiz(mathType, levels[6]);
		break;
	case 8:
		quiz(mathType, levels[7]);
		break;
	case 9:
		quiz(mathType, levels[8]);
		break;
	case 10:
		quiz(mathType, levels[9]);
		break;
	}*/
}

void quiz(char mathType, int &score) //char mathType here because we are pulling in the paramenter from operatorMenu
									 //passing scores in the array as a reference so the score stored in file is actually updated
{
	int level;
	level = 1; //level to start at 1, not 0.
	bool negatives; // for B levels
	negatives = 0;
	int answer; //answer == (num1 mathType num2);
	int quotient; // need quotient and remainder so division can be calculated and entered "long" way instead of with a float (calculator way).
	int remainder; // above
	int questions;
	int correctCount = 0; //initiating correct question count at 0
	ifstream inFile;
	int percentage; //need to convert percentage from string (in file) to int for math
	for (questions = 0; questions < 10; questions++) //display 10 questions each time quiz is started
	{
		int num1 = randNum(level, negatives); //calling randNum function with levels and sublevels parameters
		int num2 = randNum(level, negatives);
		cout << endl << num1 << " " << mathType << " " << num2 << "  =  "; //display equation and prompt for answer
		switch (mathType)
		{
		case '+':
			cin >> answer;
			if (answer == (num1 + num2)) //if correct
			{
				correctCount++; //add 1 to correct question count to determine quiz score
				cout << happyResponse() << endl << endl; //display congradulatory response, call function which randomates list of responses.
			}
			else // or incorrect (could probably do this outside switch statement, but this is easier for division)
				cout << "Incorrect. The answer is " << (num1 + num2) << "." << endl //shows correct answer right away
				<< crappyResponse() << endl << endl; //display response, call function which randomates list of "wrong" responses.
			break;
		case '-':
			cin >> answer;
			if (answer == (num1 - num2))
			{
				correctCount++;
				cout << happyResponse() << endl << endl;
			}
			else
				cout << "Incorrect. The answer is " << (num1 - num2) << "." << endl
				<< crappyResponse() << endl << endl;
			break;
		case '*':
			cin >> answer;
			if (answer == (num1 * num2))
			{
				correctCount++;
				cout << happyResponse() << endl << endl;
			}
			else
				cout << "Incorrect. The answer is " << (num1 * num2) << "." << endl
				<< crappyResponse() << endl << endl;
			break;
		case '/':
			if (num2 == 0) //cannot divide by zero, so if denominator is 0
				num2 += 1; // add one to the denominator so it is no longer 0.
			cout << "please enter quotient (without remainder):  ";
			cin >> quotient;
			cout << "and remainder:  ";
			cin >> remainder;
			if ((quotient == (num1 / num2)) && (remainder == (num1 % num2))) // if both parts (quotient and remainder) are correct
			{
				correctCount++; //add 1 to correct count
				cout << happyResponse() << endl << endl; //display response
			}
			else
				cout << "Incorrect. The answer is " << (num1 / num2) << " with R = " << (num1 % num2) << "." << endl
				//displays correct answer, broken up with quotient and remainder
				<< crappyResponse() << endl << endl;
			break;
		case 'C': //combination of all 4 operators
			//cin >> answer
			//how to randomize this?
			//how to deal with quotients again?
			break;
		}
	}
	inFile.open("storage/passing_percentage.txt"); //open percentage file
	inFile >> percentage; //read in current passing percentage from file where it's stored
	inFile.close();
	score = correctCount * 10;
	if (score >= percentage) //if percentage correct is at least the passing percentage stored in file...
	{
		//int percentage = readFile("storage/passing_percentage.txt"); //read in current passing percentage from file where it's stored
		cout << "Your score is " << score << "%. " << " Congratulations, you are ready to move on to the next level!" << endl << endl;
		//displays total score
	}
	else
	{ //if score is less than the passing percentage set by instructor
		cout << "Your score is " << score << "%." << " Please see your teacher for some extra help." << endl << endl;
	}
}

int randNum(int level, bool negatives)
{
	int magnitude = pow(10, level); //magnitude for multiple digits according to level
	int num;
	num = rand() % magnitude;
	return num;
}

int randNum(int min, int max)
{ // integer between 0 and 9
	int x = (rand() % (max - min + 1)) + min;
	return x;
}

string happyResponse()
//generate random response
{
	//srand seed up top in int main function
	const int MIN_SIZE = 0;
	const int MAX_SIZE = 9; // 10 different responses (0 to 9 = 10)
	string response;
	string responses[10]; //negative responses will be in diff scope, so reusing variable "responses"
	responses[0] = "Correct!";
	responses[1] = "Great job!";
	responses[2] = "Cool beans!";
	responses[3] = "Correct-o-mundo!";
	responses[4] = "Cowabunga, dude!";
	responses[5] = "Smashing!";
	responses[6] = "Super-duper!";
	responses[7] = "Wow, way to be!";
	responses[8] = "Awesome, keep it up!";
	responses[9] = "Bingo!";
	//generate an index for array
	int index = randNum(MIN_SIZE, MAX_SIZE);  //initializing index for array
	response = responses[index];
	return response; // return randomly generated response to quiz function
}

string crappyResponse()
{
	const int MIN_SIZE = 0;
	const int MAX_SIZE = 9;
	string response;
	string responses[10]; //positive responses in diff scope, so reusing variable
	responses[0] = "Bummer, dude!";
	responses[1] = "Oops! Try again";
	responses[2] = "Bullocks!";
	responses[3] = "Mmm...Let's try another.";
	responses[4] = "Drat!";
	responses[5] = "False!";
	responses[6] = "Sorry, that's incorrect.";
	responses[7] = "Scat!";
	responses[8] = "Oh, no!";
	responses[9] = "Whoops! Keep trying.";
	//generate an index for array
	int index = randNum(MIN_SIZE, MAX_SIZE);  //initializing index for array
	response = responses[index];
	return response;
}
/*
//array for level score keeping
const int LEVELS = 8; //array size
int scores[LEVELS]; //array has 8 elements
ofstream outputFile;

*/

//******************************************
//TO DO:
// - negative numbers for B levels
// - array to store scores and levels
// - display available levels    
// - option for mix of all operators
// - determine if new user and create file, or read from existing
// - system("CLS"); ***need to figure out where to clear screen
//******************************************