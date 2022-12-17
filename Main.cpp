#include "Records.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
using namespace std;
void toLower(string&); //make input lowercase
bool checkName(string&); //check if name contains certain characters
bool checkNum(string&); //check for valid score
bool checkFile(string&); //check for valid file name

void main() {
	cout << "STUDENT RECORDS\nValid commands: addstudent, addgrad, addscore, addpscore, deletelastscore ,save, load, print, quit\n";

	bool run = true;
	Records record;
	while (run) { // while command isn't quit
		string line, command, first, last, score;
		cout << "What would you like to do?: ";

		getline(cin, line); //get line of input
		istringstream stream(line);	//go string by string
		stream >> command >> first >> last >> score; //initialize

		//make input lowercase
		toLower(command);
		toLower(first);
		toLower(last);

		if (command == "quit") { //stop program
			if (first != "") { //If more than 1 argument given
				cout << "Too many arguements.\n";
			}
			else {
				run = false;
			}
		}
		else if (command == "print") { //print out current database
			if (first != "") { //If more than 1 argument given
				cout << "Too many arguements.\n";
			}
			else {
				record.print(); //print list of students with their grades
			}
		}
		else if (command == "save") { //save record database
			if (first == "" || last != "") { //if no file name given or too many arguments given
				cout << "Invalid arguements.\n";
			}
			else if (checkFile(first)) {
				cout << "Invalid file name.\n";
			}
			else {
				bool check = record.save(first); //save file 
				if (!check) {
					cout << "Could not save file.\n";
				}
			}
		}
		else if (command == "load") { //load record database
			if (first == "" || last != "") { //if no file name given or too many arguments given
				cout << "Invalid arguments.\n";
			}
			else if (checkFile(first)) {
				cout << "Invalid file name.\n";
			}
			else {
				bool check = record.load(first); //load file
				if (!check) {
					cout << "Could not load file.\n";
				}
			}
		}
		else if (command == "addstudent" || command == "addgrad") { //add studuent
			if (first == "" || last == "") {
				cout << "Invalid arguments.\n";
			}
			else if (!checkName(first) || !checkName(last)) { //If full name is not given
				cout << "Please enter a name again.\n";
			}
			else {
				int check;
				if (command == "addstudent") {
					check = record.addstudent(first, last);
				}
				else {
					check = record.addgrad(first, last);
				}

				if (check == -2) { //If student is already in database
					cout << "This student already exists in database.\n";
				}
				else if (check == -1) { //If database is full
					cout << "Database is at max capacity.\n";
				}
			}
		}
		else if (command == "addscore" || command == "addpscore") { //add score
			if (first == "" || last == "" || score == "") {
				cout << "Invalid arguments.\n";
			}
			else if (!checkName(first) || !checkName(last)) { //If full name is not given
				cout << "Please enter a name again.\n";
			}
			else if (!checkNum(score)) { //If invalid score is given
				cout << "Please enter a valid score.\n";
			}
			else {
				bool check;
					if (command == "addscore") {
						check = record.addscore(first, last, stof(score));
					}
					else {
						check = record.addprojscore(first, last, stof(score));
					}

					if (!check) { //check if score could be added
						cout << "Could not add score.\n";
					}
			}
		}
		else if (command == "deletelastscore")
		{
			if (first == "" || last == "") {
				cout << "Invalid arguments.\n";
			}
			else if (!checkName(first) || !checkName(last)) { //If full name is not given
				cout << "Please enter a name again.\n";
			}
			else
			{
				record.deletelastscore(first, last);
			}
		}
		else { //Incorrect command
			cout << "Invalid command.\n";
		}
	}

}

void toLower(string& s) {
	for (int i = 0; i < s.length(); i++) {//make string lowercase
		s[i] = tolower(s[i]);
	}
}

bool checkName(string& n) { //check if name contains letters and special characters
	for (int i = 0; i < n.length(); i++) {
		if ((n[i] < 'a' || n[i] > 'z') && (n[i] != '-' && n[i] != '\''
			&& n[i] != '.')) {
			return false; //if name is contains non letters or allowed special characters
		}
	}
	return true;
}

bool checkNum(string& n) { //check if score is numeric and positive
	if (n[0] == '0' && n[1] != '\0') {
		return false; //if number is empty or starts with a zero return false
	}
	for (int i = 0; i < n.length(); i++) {
		if ((n[i] < '0' || n[i] > '9') && n[i] != '.') {
			return false; //if number is not numeric
		}
	}

	return true;
}

bool checkFile(string& filename) {
	for (int j = 0; j < filename.length(); j++) { //Check if file name is valid
		if (filename[j] == '/' || filename[j] == '\'' || filename[j] == ':'
			|| filename[j] == '*' || filename[j] == '?' || filename[j] == '"'
			|| filename[j] == '<' || filename[j] == '>' || filename[j] == '|') {
			return true; //file is invalid
		}
	}
	return false; //file is good
}