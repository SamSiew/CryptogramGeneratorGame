/**************************************************
Project: The Amazing Cryptogram Generator
Author: Ming Shern Siew
Purpose: Application File
Create and Display game Menu,
Display an Information about The Amazing Cryptogram Generator,
Read and Store Data from a File filled with quote, 
Generate and Display a Random Cryptogram from list of quote,
Save a Cryptogram to a File and
Display Saved Cryptograms from a File.
**************************************************/
#include "main.h"

int main() {
	/******************************************************************************
	 * Run menu options which allow user to different kind of service.
	 * Terminate after user decide to exit menu options
	 ******************************************************************************/
	// seed randoms number for unique random number every time program starts.
	srand(unsigned(time(NULL)));
	// display menu and run the game. 
	runMenu();
	return 0;
}

void runMenu() {
	/******************************************************************************
	 * Display and run menu options which allow user to different kind of service.
	 ******************************************************************************/
	// declare and initialise local variables
	int userInput;
	string lastCryptogram;
	bool isGameStillRunning = true;
	// decare constant allow other developer knows value not change in entire program
	const string ABOUT_FILENAME = "CryptoAbout.txt";
	const string QUOTE_FILENAME = "CryptogramData.txt";
	const string CRYPTOGRAM_FILENAME = "savedCryptograms.txt";
	// game will run untill it receive [0] command which indicate end of the game
	while (isGameStillRunning) {
		system("cls");
		displayMenu();
		// Prompt user for input and force non-empty and between 0 and 5.
		userInput = askForNumber("Which option would you like", 0, 5);
		// terminate programs.
		if (userInput == 0) {
			isGameStillRunning = false;
			displayInformation("Thank you for testing this application.", true);
		}
		// display rules of games information.
		else if (userInput == 1) {
			displayText(ABOUT_FILENAME);
		}
		// read and store cryptograms file and quotes file.
		else if (userInput == 2) {
			createLists(QUOTE_FILENAME, quotes);
			createLists(CRYPTOGRAM_FILENAME, cryptograms);
		}
		// generate random cryptograms from selected quotes and save into lastCryptogram
		else if (userInput == 3) {
			lastCryptogram = generateCryptogram();
		}
		// save string lastCryptogram to a File named savedCryptograms.txt
		else if (userInput == 4) {
			saveData(CRYPTOGRAM_FILENAME, lastCryptogram);
		}
		// display string saved Cryptograms from a File named savedCryptograms.txt
		else {
			displaySavedData(CRYPTOGRAM_FILENAME);
		}
		system("pause");
	}
}

string askForString(string question) {
	/******************************************************************************
	 * Asks user for valid string input.
	 * 
	 * @param   question      Prompt to be displayed to the user.
     * @return  userInput     Appropriate string entered by user.
	 ******************************************************************************/
	// Initialise empty string to prompt user with question later.
	string userInput = "";

	// Keep asking for string input until it is not empty.
	while (userInput.empty()) {
		displayInformation(question, false);
		getline(cin, userInput);
		// let user knows thier response should not be empty.
		if (userInput.empty()) {
			displayInformation("Your response should not be empty, Try again!", true);
		}
	}
	return userInput;
}

int askForNumber(string question, int minimumRange, int maximumRange) {
	/***************************************************************************
	* Asks user for valid integer input.
	*
	* @param   question        Prompt to be displayed to the user. 
	* @param   minimumRange    Lowest integer user can input.
	* @param   maximumRange    Highest integer user can input.
	* @return  num             Appropriate integer entered by user.
	**************************************************************************/
	// Initialise num to -1 because postive value is expected.
	int num = -1;
	// Keep asking for input until it is within range specified.
	while (num < minimumRange || num > maximumRange) {
		num = stoi(askForString(question +" (" + to_string(minimumRange) + "-" + to_string(maximumRange) +  "): "));
	}
	return num;
}


void displayMenu() {
	/***************************************************************************
	 * Displays a text menu in the console.
	 **************************************************************************/
	// Display menu header.
	displayInformation("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", true);
	displayInformation("      The Amazing Cryptogram Generator", true);
	displayInformation("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", true);
	// Display menu options.
	displayInformation(" [0] End Testing the Program", true);
	displayInformation(" [1] Display \"About\" Information", true);
	displayInformation(" [2] Read and store data from files", true);
	displayInformation(" [3] Generate a Random Cryptogram", true);
	displayInformation(" [4] Save Cryptogram to a File", true);
	displayInformation(" [5] Load Cryptogram from a File", true);
	displayInformation("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", true);
}

void displayText(string filename) {
	/***************************************************************************
	 * Prints out every new line of a file into the console.
	 *
	 * @param filename: Name of the text file to be displayed.
	 **************************************************************************/
	// declare local variables
	string textline;
	ifstream file;
	
	// clear all console.
	file.open(filename);

	// Validate if file found and not empty.
	if (isValidFile(file)) {
		// Clear system for new information.
		system("cls");
		// Display all line in file.
		while (getline(file, textline)) {
			displayInformation(textline, true);
		}
	}
	else {
		// print error file is not found
		displayInformation(filename + " not Found or is empty.", true);
	}
	file.close();
}

void displayInformation(string information, bool isEndOfLine) {
	/***************************************************************************
	 * Prints out contents of a file into the console exactly the way it was
	 * formatted.
	 *
	 * @param information:     String value which will need to be displayed to user.
	 * @param isEndOfLine:     Boolean value which indicate whether it is end of a line
	 **************************************************************************/
	// print string into console
	cout << information;
	// when isEndOfLine = True, console will have new line for next consecutive string.
	if (isEndOfLine) {
		cout << endl;
	}
}

bool isValidFile(ifstream& file) {
	/***************************************************************************
	 * validate if file exist and not empty.
	 * 
	 * @param   file:             Text file which will need to validate if it exist and not empty.
	 * @return  boolean value     True: File can be read; False: File can't be read 
	 **************************************************************************/
	// is_open() check if file exist and peek() will check if file is not end of file which indicate empty file if it is end of file.
	return file.is_open() && file.peek() != EOF;
}

void createLists(string filename, vector<string>& selectedVector) {
	/***************************************************************************
	 * Loads data from a file and returns this data as a vector.
	 *
	 * @param   filename          Name of the text file to be displayed.
	 * @param   selectedVector    String vector containing data from each line of
	 *                            file. Empty if file does not exist or is empty.
	 **************************************************************************/
	// declare local variables
	string currData;
	ifstream file;
	
	// Open file.
	file.open(filename);
	
	// Validate if file found and not empty.
	if (isValidFile(file)) {
		// clear vector to store brand new data.
		selectedVector.clear();
		// Read file into vector.
		while (getline(file, currData, ';')) {
			selectedVector.push_back(currData);
		}
		// Display succession of data loading from file.
		displayInformation("Data loading from " + filename, true);
	}
	else {
		// print error file is not found
		displayInformation(filename + " not Found or is empty. Unable to update information in this system", true);
	}
}

string generateCryptogram() {
	/***************************************************************************
	 * generating cryptogram using a random element from stored “quotes” with caesar cipher and 
	 * display the result as a concatenated or formatted string.
	 *
	 * @return  cryptogramString   New string which is result of caesar cipher on a selected quote.
	 *
	 * Preconditions:
	 * - quotes must not be empty.
	 **************************************************************************/
	 
	// declare and intialise local variable
	int position;
	int shiftvalue;
	string selectedQuote;
	const int MAXIMUM_LETTER = 26;
	string cryptogramString = "";
	// Validation checks that quotes collection have been created
	if (quotes.empty() == false) {
		// One random quote is selected from the quotes collection
		position = rand() % quotes.size();
		selectedQuote = quotes[position];
		// Initialise shiftvalue to be a value that increment for ascii value for letter .
		shiftvalue = askForNumber("Choose a number", 1, 25);
		// encrypt all each letter in the selectedQuote with caesar cipher      
		for (size_t indexString = 0; indexString < selectedQuote.size(); indexString++) {
			/*
			Letter will be transform via caesar cipher and Encryption of lowercase character is 
			Encryption of character = (character - ascii value of a + amount of shift) % maximum number of letter + ascii value of a
		    The function can be intepretted by mapping the character with corresponding number between 0 - 26 because 0 correspond to a and 26 correspond to z.
			The number will then be shifted by any value chosen by user. Then, the number will be placed in a location via modulus between 0 - 26 because some number can go beyond 26.
			Then, the number will then map it back to character between a-z after adding ascii of a.
			C++ assume character as int, a-z has 26 letters, a is smallest letter and z is largest letter of lower case character
			*/  
			if (selectedQuote[indexString] >= 'a' && selectedQuote[indexString] <= 'z') {
				cryptogramString += (selectedQuote[indexString] - 'a' + shiftvalue) % MAXIMUM_LETTER + 'a';
			}
			/*
			Encryption of uppercase character is
			Encryption of character = (character - ascii value of A + amount of shift) % maximum number of letter + ascii value of A
			The function can be intepretted by mapping the character with corresponding number between 0 - 26 because 0 correspond to A and 26 correspond to Z.
			The number will then be shifted by any value chosen by user. Then, the number will be placed in a location via modulus between 0 - 26 because some number can go beyond 26.
			Then, the number will then map it back to character between A-Z after adding ascii of A.
			C++ assume character as int, A-Z has 26 letters, A is smallest letter and Z is largest Letter of upper case character
			*/
			else if (selectedQuote[indexString] >= 'A' && selectedQuote[indexString] <= 'Z') {
				cryptogramString += (selectedQuote[indexString] - 'A' + shiftvalue) % MAXIMUM_LETTER + 'A';
			}
			// copy actual character if it is not a letter.
			else {
				cryptogramString += selectedQuote[indexString];
			}
		}
		displayInformation(cryptogramString, true);
	}
	else {
		displayInformation("Please store non-empty cryptogram data via [2] command!", true);
	}
	return cryptogramString;
}

void saveData(string cryptogramFilename, string cryptogramString) {
	/***************************************************************************
	 * Write a single line of text into a file.
	 *
	 * @param   cryptogramFilename       Name of the cryptogram file to be edited.
	 * @param   cryptogramString         Cryptogram String to be written on to file.
	 **************************************************************************/
	 // declare and initialise local variables
	string iscryptosaved;
	ofstream fileToWrite(cryptogramFilename, ios::app);

	// validate whether cryptogramString is not empty 
	if (cryptogramString.empty() == false) {
		displayInformation(cryptogramString, true);
		// ask user if they want to save this Cryptogram into file.
		iscryptosaved = askForString("Do you want to save this Cryptogram?(y/n): ");
		if (iscryptosaved == "y" || iscryptosaved == "Y") {
			// validate if fileToWrite can be written
			if (fileToWrite.is_open()) {
				// save the content into file 
				fileToWrite << cryptogramString << ';';
				displayInformation("This Cryptogram is now saved.", true);
			}
			else {
				// print error unable to write to file
				displayInformation("Unable to write to " + cryptogramFilename + ".", true);
			}
			// close the file
			fileToWrite.close();
		}
	}
	else {
		displayInformation("Generate a cryptogram with [3] before proceeds", true);
	}
}

void displaySavedData(string cryptogramFilename) {
	/***************************************************************************
	 * Read and displays cryptograms data stored in a savedCryptograms.txt.
	 * 
	 * @param   cryptogramFilename       Name of the cryptogram file to be edited.
	 **************************************************************************/
	// declare and initialise local variables
	string line = "";
	ifstream fileToRead(cryptogramFilename);

	// validate if fileToRead can be read before proceeds.
	if (isValidFile(fileToRead)) {
		// clear up cryptogram to update
		cryptograms.clear();
		displayInformation("All Saved Cryptograms", true);
		// reading from a file and print it into console
		while (getline(fileToRead, line, ';')) {
			// add one cryptogram at a time to update
			cryptograms.push_back(line);
			displayInformation(line, true);
		}

	}
	else {
		// print error file is not found
		displayInformation(cryptogramFilename + " not Found or is empty.", true);
	}
	// close the file
	fileToRead.close();
}
