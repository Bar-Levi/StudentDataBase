#pragma once
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
    string proj_name;
    float scores[NUM_TESTS]; //list of scores
    long id;
    string score_names[NUM_TESTS];
    char student_type; //undergrad(U) and grad(G)


    Student(); //construct Student
    Student(string, string, long); //construct student with name
    bool addscore(float, string); //add score for student
    void addprojscore(float, string); //add project score
    bool editscore();// delete last score
    bool addbonus(float, string); // adds a bonus by percentage to the final score of a given subject
    void setfname(string); //set student first name
    void setlname(string); //set student last name
    string getfname(); //return first name
    string getlname(); //return last name
    bool delscore(int index);
    bool changeCN(int index, string newName);

    // overridables
    virtual char getgrade() = 0; // This is a pure virtual function -> Student is an abstract class
                     // It is defined to force children to implement this interface function.
};

//Child classes
class Ugrad : public Student {
public:
    Ugrad(string, string, long);
    char getgrade();
    bool editscore();//delete last score
};

class Grad : public Student {
public:
    Grad(string, string, long);
    char getgrade();
    bool editscore();//delete last score
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
    int addstudent(string, string, long); //add undergrad to records
    int addgrad(string, string, long); //add grad to records
    int deletestudent(long); // delete a student
    bool addscore(long, string, string); //add score to a student
    bool addprojscore(long, string, string); //add project
    bool changename(string fname);//change name
    bool editscore(long id);//delete last score
    bool addbonus(long, string); // adds a bonus to the final grade of a given subject
    void print(); //print list of students
    bool load(string&); //copy student info from file to records database
    bool save(string&); //save student info from record database to file
    bool checkID(long num); // check if id exists in database
    bool checkForLetter(string& n);
    bool deletescoredex(int index, long id);
    bool changecourseName(int index, long id, string newName);
    bool checkIndex(long id, int index);
    bool changeid(long lid);//change id
    int getcount() { return count; } //number of students in lists
    char get_type(long num);
    Student& operator[](int idx) //overload [] operator
    {
        return *students[idx];
    }
};
#endif // !RECORDS_H
