#include "Records.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

Student::Student() { //constructor
	firstname = "";
	lastname = "";
	count = 0;
	proj_score = NULL;
}

Student::Student(string fname, string lname) { // constructor with given name
	firstname = fname;
	lastname = lname;
	count = 0;
	proj_score = NULL;
}

void Student::setfname(string name) {
	firstname = name; //set first name to desired name
}

void Student::setlname(string name) {
	lastname = name; //set last name to desired name
}

bool Student::addscore(float grade) {
	if (count == NUM_TESTS) {
		return false; //if score list is full return fail
	}
	scores[count++] = grade; //add score to list

	return true; //return success
}

bool Student::deletelastscore() // find the last score, delete it and reduce the count by 1
{
	if (count == 0)
	{
		cout << "Not grades found" << endl;
		return false;
	}
	scores[--count] = NULL;
	return true;
}

void Student::addprojscore(float score) { //add project score
	proj_score = score;
}

string Student::getfname() {
	return firstname; //return first name of student
}

string Student::getlname() {
	return lastname; //return last name of student
}

//Undergrad
Ugrad::Ugrad(string fname, string lname) : Student(fname, lname) { //constructor
	student_type = 'U';
}

char Ugrad::getgrade() { //calculate grade for user
	if (count == 0 && proj_score == NULL) {
		return '-'; //no scores added
	}

	float grade = 0, sum = 0, average;
	for (int i = 0; i < count; i++) {
		grade += scores[i]; //add all scores together
		sum += 1; //get total number of grades
	}

	if (proj_score != NULL) { //if project score entered
		grade += proj_score; //add project score
		sum += 1; //add prject score to total amount of scores added
	}

	average = grade / sum; //get average score

	//return letter grade
	if (average >= 90) {
		return 'A';
	}
	else if (average >= 80) {
		return 'B';
	}
	else if (average >= 70) {
		return 'C';
	}
	else if (average >= 60) {
		return 'D';
	}
	else {
		return 'F';
	}
}

bool Ugrad::deletelastscore()// delete last score
{
	if (count == 0)
	{
		cout << "Not grades found" << endl;
		return false;
	}
	scores[--count] = NULL;
	return true;
}

//Graduate
Grad::Grad(string fname, string lname) : Student(fname, lname) { //constructor
	student_type = 'G';
}

char Grad::getgrade() { //calculate grade
	if (count == 0 && proj_score == NULL) {
		return '-'; //no scores added
	}

	float grade = 0, sum = 0, average;
	for (int i = 0; i < count; i++) {
		grade += scores[i]; //add all scores together
		sum += 1; //get total number of grades
	}

	if (proj_score != NULL) { //if project score entered
		grade += (5 * proj_score); //add project score
		sum += 5; //add prject score to total amount of scores added
	}

	average = grade / sum; //get average score

	if (proj_score > MIN_PROJ_SCORE && average > 65) {
		return 'P';
	}
	else {
		return 'F';
	}
}

bool Grad::deletelastscore() // delete last score
{
	if (count == 0)
	{
		cout << "Not grades found" << endl;
		return false;
	}
	scores[--count] = NULL;
	return true;
}

//Records
Records::Records() { //constructor
	count = 0;
}

int Records::addstudent(string fname, string lname) { //undergrad
	if (count == MAX_NUM_STUDENTS) {
		return -1; //return error if student list is full
	}

	for (int i = 0; i < count; i++) { //sheck if student exists in database
		if ((students[i]->firstname == fname) && //check if first/last name matches
			(students[i]->lastname == lname)) {
			return -2; //return error if student exists in database
		}
	}

	students[count++] = new Ugrad(fname, lname); //add undergrad to list
	return 0; //return success
}

int Records::addgrad(string fname, string lname) { //undergrad
	if (count == MAX_NUM_STUDENTS) {
		return -1; //return error if student list is full
	}

	for (int i = 0; i < count; i++) { //sheck if student exists in database
		if ((students[i]->firstname == fname) && //check if first/last name matches
			(students[i]->lastname == lname)) {
			return -2; //return error if student exists in database
		}
	}

	students[count++] = new Grad(fname, lname); //add grad to list
	return 0; //return success
}

bool Records::deletelastscore(string fname, string lname) // delete last score
{
	for (int i = 0; i < count; i++) {
		if ((students[i]->firstname == fname) && //chick if first name matches
			(students[i]->lastname == lname)) { //check if last name matches
			return students[i]->deletelastscore(); //delete last score
		}
	}
}

bool Records::addscore(string fname, string lname, float sc) {
	for (int i = 0; i < count; i++) {
		if ((students[i]->firstname == fname) && //chick if first name matches
			(students[i]->lastname == lname)) { //check if last name matches
			students[i]->addscore(sc); //add score
			return true;
		}
	}
	return false;
}

bool Records::addprojscore(string fname, string lname, float sc) {
	for (int i = 0; i < count; i++) {
		if ((students[i]->firstname == fname) && //chick if first name matches
			(students[i]->lastname == lname)) { //check if last name matches
			students[i]->addprojscore(sc); //add score
			return true;
		}
	}
	return false;
}

void Records::print() { //print students and their scores
	cout << left << setw(15) << "Name" << "|"
		<< left << setw(5) << "Type" << "|"
		<< left << setw(7) << "Project" << "|"
		<< right << setw(20) << "Scores" << "|"
		<< setw(5) << "Grade" << endl;

	for (int i = 0; i < count; i++) {
		//print name, student type, project score
		cout << left << setw(7) << students[i]->firstname
			<< left << setw(9) << students[i]->lastname
			<< left << setw(6) << students[i]->student_type;

		//print project score if it is entered
		if (students[i]->proj_score != NULL) {
			cout << left << setw(8) << students[i]->proj_score;
		}
		else {
			cout << left << setw(8) << "-";
		}

		//print scores
		int j;
		for (j = 0; j < students[i]->count; j++) {
			cout << right << setw(4) << students[i]->scores[j];
		}
		for (; j < NUM_TESTS; j++) {
			cout << right << setw(4) << "-";
		}

		//print grade
		cout << " " << right << setw(4) << students[i]->getgrade() << endl;
	}

	cout << endl;
}

bool Records::load(string& filename) {//copy student info from file to records database
	bool works = false;
	ifstream loadfile(filename, ios::in); //try to open a file
	while (loadfile) { //if file can open
		works = true;
		string first, last, type, proj, score, grade;
		loadfile >> first >> last >> type >> proj; //get full name

		if (first == "") { //if first name empty then there is no more in database
			break;
		}

		//add student to database
		if (type == "U") {
			addstudent(first, last); //create undergrad
		}
		else if (type == "G") {
			addgrad(first, last); //create grad
		}

		if (proj != "-") {
			addprojscore(first, last, stof(proj));
		}

		for (int i = 0; i < NUM_TESTS; i++) { //get their scores
			loadfile >> score;
			if (score == "-") { //there are no more scores for this student
				continue;
			}
			else { //add score to students list
				addscore(first, last, stof(score));
			}
		}

		loadfile >> grade; //just to get to the end of the line
	}

	loadfile.close();
	return works;
}

bool Records::save(string& filename) {
	ofstream savefile(filename, ios::out);
	for (int i = 0; i < count; i++) {
		//print name, student type, project score
		savefile << left << setw(7) << students[i]->firstname
			<< left << setw(9) << students[i]->lastname
			<< left << setw(6) << students[i]->student_type;

		//print project score if it is entered
		if (students[i]->proj_score == NULL) {
			savefile << left << setw(8) << "-";
		}
		else {
			savefile << left << setw(8) << students[i]->proj_score;
		}

		//print scores
		int j;
		for (j = 0; j < students[i]->count; j++) {
			savefile << right << setw(4) << students[i]->scores[j];
		}
		for (; j < NUM_TESTS; j++) {
			savefile << right << setw(4) << "-";
		}

		//print grade
		savefile << " " << right << setw(4) << students[i]->getgrade();

		if (i != count - 1) { //if not at the end of array 
			savefile << endl;	  //start new line for next student
		}
	}

	savefile.close();
	return true;
}