/**************************************************
Project: The Amazing Cryptogram Generator
Author: Ming Shern Siew
Purpose: Header File
Header file organize all dependency and package which will be used in application file.
The structured file is in order of following: 
#include, using
declare global variables
declare user defined functions
**************************************************/
#ifndef MAIN_H
#define MAIN_H

// #include, using
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

// declare global variables
vector<string> cryptograms;
vector<string> quotes;

// declare functions
void runMenu();
string askForString(string question);
int askForNumber(string question, int minimumRange, int maximumRange);
void displayMenu();
void displayText(string filename);
void displayInformation(string information, bool isEndOfLine);
bool isValidFile(ifstream& file);
void createLists(string filename, vector<string>& selectedVector);
string generateCryptogram();
void saveData(string cryptogramFilename, string cryptogramString);
void displaySavedData(string cryptogramFilename);

#endif