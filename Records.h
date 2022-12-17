#ifndef RECORDS_H
#define RECORDS_H
#include <string>
using namespace std;

#define NUM_TESTS 5
#define MAX_NUM_STUDENTS 30
#define MIN_PROJ_SCORE 65

//abstract base class
class Student {
public:
	string firstname, lastname; //student name
	int count; //number of scores for student
	float proj_score;
	float scores[NUM_TESTS]; //list of scores
	string score_names[NUM_TESTS];
	char student_type; //undergrad(U) and grad(G)

	Student(); //construct Student
	Student(string, string); //construct student with name
	bool addscore(float,string); //add score for student
	void addprojscore(float); //add project score
	bool deletelastscore();// delete last score
	bool addbonus(float); // adds a bonus by percentage to all of the student scores
	void setfname(string); //set student first name
	void setlname(string); //set student last name
	string getfname(); //return first name
	string getlname(); //return last name

	// overridables
	virtual char getgrade() = 0; // This is a pure virtual function -> Student is an abstract class
				     // It is defined to force children to implement this interface function.
};

//Child classes
class Ugrad : public Student {
public:
	Ugrad(string, string);
	char getgrade();
	bool deletelastscore();//delete last score
};

class Grad : public Student {
public:
	Grad(string, string);
	char getgrade();
	bool deletelastscore();//delete last score
};

//The actual database
class Records {
private:
	Student* students[MAX_NUM_STUDENTS]; //list of students
	int count;
public:
	Records(); // construct record
	~Records() 
	{
		for (int i = 0; i < count; i++) 
		{
			delete students[i];
		}
	}
	int addstudent(string, string); //add undergrad to records
	int addgrad(string, string); //add grad to records
	bool addscore(string, string, float, string); //add score to a student
	bool addprojscore(string, string, float); //add project 
	bool changename(string fname, string lname);//change name
	bool deletelastscore(string fname, string lname);//delete last score
	bool addbonus(string, string, string); // add a bonus to all of the grades of a given student
	void print(); //print list of students
	bool load(string&); //copy student info from file to records database
	bool save(string&); //save student info from record database to file

	int getcount() { return count; } //number of students in lists
	Student& operator[](int idx) //overload [] operator
	{
		return *students[idx];
	}
};
#endif // !RECORDS_H
