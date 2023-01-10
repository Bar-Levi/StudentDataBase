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
    proj_name = "";
    id = 0;
}

Student::Student(string fname, string lname, long id) { // constructor with given name
    firstname = fname;
    lastname = lname;
    count = 0;
    proj_score = NULL;
    this->id = id;
}

void Student::setfname(string name) {
    firstname = name; //set first name to desired name
}

void Student::setlname(string name) {
    lastname = name; //set last name to desired name
}

bool Student::addscore(float grade, string course) {
    if (count == NUM_TESTS) {
        return false; //if score list is full return fail
    }
    scores[count] = grade; //add score to list
    score_names[count] = course;
    count++;

    return true; //return success
}

bool Student::addbonus(float percentage, string subject) {
    for (int i = 0; i < count; i++) {
        if (score_names[i] == subject)
            scores[i] *= (1 + (percentage / 100));
        scores[i] = int(round(scores[i]));
        if (scores[i] > 100 || scores[i] < 0)
            scores[i] > 100 ? scores[i] = 100 : scores[i] = 0;
    }
    return true;
}


bool Student::editscore() // find the last score, delete it and reduce the count by 1
{
    int edit;
    if (count == 0)
    {
        cout << "Not grades found" << endl;
        return false;
    }
    cout << "Enter which grade you want to edit?" << endl;
    cin >> edit;
    if (edit > count || edit < 0)
    {
        cout << "Not valid index" << endl;
        getchar();
        return false;
    }
    cout << "Enter new grade" << endl;
    int newscore;
    cin >> newscore;
    if (newscore < 0 || newscore>100)
    {
        cout << "Not Valid Score" << endl;
        return false;
    }
    scores[edit - 1] = newscore;
    getchar();
    cout << "Grade Changed Successfully" << endl;
    return true;
}




void Student::addprojscore(float grade, string course) { //add project score
    if (!proj_score || (proj_name == course))
    {
        proj_score = grade;
        proj_name = course;
    }
    else
    {
        cout << "CANT CHANGE PSCORE" << endl;
    }





}

string Student::getfname() {
    return firstname; //return first name of student
}

string Student::getlname() {
    return lastname; //return last name of student
}

//Undergrad
Ugrad::Ugrad(string fname, string lname, long id) : Student(fname, lname, id) { //constructor
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

bool Records::changeid(long lid)
{
    long nid = 0;
    cout << "Enter the new id :";
    cin >> nid;
    getchar();
    for (int i = 0; i < count; i++)
    {
        if (students[i]->id == lid) //check if the id matches
        {
            students[i]->id = nid;
            return true;
        }

    }
    return false;
}

char Records::get_type(long num)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i]->id == num)
        {
            return students[i]->student_type;

        }
    }
    return 'i';
}

bool Records::deletescoredex(int index, long id)
{
    for (int i = 0; i < count; i++)
        if (students[i]->id == id)  //check if id matches
            return students[i]->delscore(index);

    return false;
}

bool Records::changecourseName(int index, long id, string newName)
{
    for (int i = 0; i < count; i++)
        if (students[i]->id == id)  //check if id matches
            return students[i]->changeCN(index, newName);

    return false;
}

bool Records::checkIndex(long id, int index)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i]->id == id)
            if (students[i]->scores[index] >= 0)
                return true;
    }
    return false;
}

bool Student::delscore(int index)
{

    if (count == 0)
    {
        cout << "Not grades found" << endl;
        return false;
    }
    if (index > count || index < 0)
    {
        cout << "Not valid index" << endl;
        getchar();
        return false;
    }
    scores[index] = NULL;
    score_names[index] = "";
    for (int i = index; i < count - 1; i++)
    {
        score_names[i] = score_names[i + 1];
        scores[i] = scores[i + 1];
    }
    scores[count - 1] = NULL;
    score_names[count - 1] = "";
    count--;
    cout << "Grade Deleted Successfully" << endl;
    getchar();
    return true;
}

bool Student::changeCN(int index, string newName)
{

    if (count == 0)
    {
        cout << "No grades found" << endl;
        return false;
    }
    if (index > count || index < 0)
    {
        cout << "Not valid index" << endl;
        getchar();
        return false;
    }

    score_names[index] = newName;
    cout << "Course name changed successfully" << endl;
    getchar();

    return true;
}

bool Records::changename(string fname)
{
    string new_first, new_last;
    cout << "Type your first name:\n";
    cin >> new_first;
    cout << "Type your last name:\n";
    cin >> new_last;
    getchar();
    for (int i = 0; i < count; i++) {
        if (students[i]->id == (stol(fname)))
        { //check if last name matches
            students[i]->firstname = new_first;
            students[i]->lastname = new_last;
            return true;
        }
    }
    cout << "There is no student with this name!\n";
    return false;
}

bool Ugrad::editscore()// delete last score
{
    int edit;
    if (count == 0)
    {
        cout << "Not grades found" << endl;
        return false;
    }
    cout << "Enter which grade you want to edit?" << endl;
    cin >> edit;
    if (edit > count || edit < 0)
    {
        cout << "Not valid index" << endl;
        getchar();
        return false;
    }
    cout << "Enter new grade" << endl;
    int newscore;
    cin >> newscore;
    scores[edit - 1] = newscore;
    getchar();
    cout << "Grade Changed Successfully" << endl;
    return true;
}

//Graduate
Grad::Grad(string fname, string lname, long id) : Student(fname, lname, id) { //constructor
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

bool Grad::editscore() // delete last score
{
    int edit;
    if (count == 0)
    {
        cout << "Not grades found" << endl;
        return false;
    }
    cout << "Enter which grade you want to edit?" << endl;
    cin >> edit;
    if (edit > count || edit < 0)
    {
        cout << "Not valid index" << endl;
        getchar();
        return false;
    }
    cout << "Enter new grade" << endl;
    int newscore;
    cin >> newscore;
    scores[edit - 1] = newscore;
    getchar();
    cout << "Grade Changed Successfully" << endl;
    return true;
}

//Records
Records::Records() { //constructor
    count = 0;
}

int Records::addstudent(string fname, string lname, long id) { //undergrad
    if (count == MAX_NUM_STUDENTS) {
        return -1; //return error if student list is full
    }
    students[count++] = new Ugrad(fname, lname, id); //add undergrad to list
    return 0; //return success
}

int Records::addgrad(string fname, string lname, long id) { //undergrad
    if (count == MAX_NUM_STUDENTS) {
        return -1; //return error if student list is full
    }

    for (int i = 0; i < count; i++) { //sheck if student exists in database
        if ((students[i]->id == id))  //check if id matches
            return -2; //return error if student exists in database
    }

    students[count++] = new Grad(fname, lname, id); //add grad to list
    return 0; //return success
}

int Records::deletestudent(long id) { //undergrad
    int deleted = 0;

    for (int i = 0; i < count; i++) { //check if student exists in database
        if (deleted)
        {
            students[i] = students[i + 1];
        }

        if (students[i]->id == id) { //check if first/last name matches
            students[i] = students[i + 1];
            count--;
            deleted = 1; //return success
        }
    }
    return deleted; //return failure
}

bool Records::editscore(long id) // delete last score
{
    for (int i = 0; i < count; i++)
        if (students[i]->id == id)  //chick if first name matches
            return students[i]->editscore(); //delete last score
    return false;
}

bool Records::checkForLetter(string& n) // check if there is a letter in the string
{
    for (int i = 0; i < n.length(); i++)
    {
        if (n[i] < '0' || n[i]>'9')
            return true;
    }
    return false;
}

bool Records::addscore(long id, string course, string score)
{
    if (checkForLetter(score))
    {
        string temp = course;
        course = score;
        score = temp;
    }
    for (int i = 0; i < count; i++) {
        if (students[i]->id == id) { //chick if first name matches
            students[i]->addscore(stof(score), course); //add score
            return true;
        }
    }
    return false;
}

bool Records::addprojscore(long id, string course, string score) {
    if (checkForLetter(score))
    {
        string temp = course;
        course = score;
        score = temp;
    }
    for (int i = 0; i < count; i++) {
        if (students[i]->id == id) { //chick if first name matches
            students[i]->addprojscore(stof(score), course); //add score
            return true;
        }
    }
    return false;
}

void Records::print() { //print students and their scores
    cout << left << setw(20) << "Name" << "|"
        << left << setw(9) << "ID " << "|"
        << left << setw(12) << "Type" << "|"
        << left << setw(10) << "Project" << "|"
        << left << setw(55) << "Scores" << "|"
        << setw(5) << "Grade" << endl;

    for (int i = 0; i < count; i++) {
        //print name, student type, project score
        cout << left << setw(9) << students[i]->firstname
            << left << setw(13) << students[i]->lastname
            << left << setw(10) << students[i]->id
            << left << setw(10) << students[i]->student_type;

        //print project score if it is entered
        if (students[i]->proj_score != NULL)
        {
            cout << left << ' ' << students[i]->proj_name << ":" << students[i]->proj_score << " ";
        }
        else {
            cout << left << setw(13) << "-";
        }

        //print scores, course name
        int j;
        for (j = 0; j < students[i]->count; j++) {
            cout << right << setw(7) << students[i]->score_names[j] << ":";
            cout << left << setw(3) << students[i]->scores[j] << " ";
        }
        for (; j < NUM_TESTS; j++) {
            cout << left << setw(10) << "-";
        }

        //print grade
        cout << " " << right << setw(4) << students[i]->getgrade() << endl;
    }

    cout << endl;
}

bool Records::load(string& filename) {//copy student info from file to records database
    bool works = false;
    ifstream loadfile(filename, ios::in); //try to open a file
    while (loadfile) { //if afile can open
        works = true;
        string first, last, type, project_score, score, course, grade, project_course_and_score;
        string project_course = "";
        long id;
        loadfile >> first >> last >> id >> type >> project_course_and_score; //get full name

        if (first == "") { //if first name empty then there is no more in database
            break;
        }

        //add student to database
        if (type == "U") {
            addstudent(first, last, id); //create undergrad
        }
        else if (type == "G") {
            addgrad(first, last, id); //create grad
        }
        bool passed = false;
        for (int i = 0; i < project_course_and_score.length(); i++)
        {
            if (project_course_and_score[i] == ':')
            {
                passed = true;
                i++;
            }
            if (passed && project_course_and_score[i] < '0' && project_course_and_score[i] > '9')
                break;
            if (!passed)
                project_course += project_course_and_score[i];
            else
                project_score += project_course_and_score[i];
        }

        if (project_course_and_score != "-") {
            addprojscore(id, project_course, project_score);
        }
        string course_and_score;
        for (int i = 0; i < NUM_TESTS; i++) { //get their scores
            passed = false;
            loadfile >> course_and_score;
            course = score = "";
            for (int i = 0; i < course_and_score.length(); i++)
            {
                if (course_and_score[i] == ':')
                {
                    passed = true;
                    i++;
                }
                if (passed && course_and_score[i] < '0' && course_and_score[i] > '9')
                    break;
                if (!passed)
                    course += course_and_score[i];
                else
                    score += course_and_score[i];
            }
            if (course_and_score == "-") { //there are no more scores for this student
                continue;
            }
            else { //add score to students list
                addscore(id, course, score);
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
        savefile << left << setw(7) << students[i]->firstname << ' '
            << left << setw(9) << students[i]->lastname << ' '
            << left << setw(6) << students[i]->id << ' '
            << left << setw(6) << students[i]->student_type << ' ';


        //print project score if it is entered
        if (students[i]->proj_score == NULL) {
            savefile << left << setw(8) << " - ";
        }
        else {
            savefile << left << students[i]->proj_name << ':' << students[i]->proj_score << ' ';
        }

        //print scores
        int j;
        for (j = 0; j < students[i]->count; j++) {
            savefile << right << setw(7) << students[i]->score_names[j] << ":";
            savefile << left << setw(3) << students[i]->scores[j] << "  ";
        }
        for (; j < NUM_TESTS; j++) {
            savefile << left << setw(10) << " -";
        }

        //print grade
        savefile << " " << right << setw(4) << students[i]->getgrade();

        if (i != count - 1) { //if not at the end of array
            savefile << endl;      //start new line for next student
        }
    }

    savefile.close();
    return true;
}

bool Records::checkID(long num)
{
    for (int i = 0; i < count; i++)
    {
        if (num == students[i]->id)
            return false;
    }
    return true;
}

bool Records::addbonus(long id, string percentage) {
    string subject;
    cout << "Enter subject:\n";
    cin >> subject;
    getchar();
    float val = std::stof(percentage);
    for (int i = 0; i < count; i++) {
        if ((students[i]->id == id)) { //check if ID matches
            students[i]->addbonus(val, subject); // add bonus(can be negative)
            return true;
        }
    }
    return false;

}
