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
bool checkForLetter(string&); // check if there is a letter in the string

int main() {
    cout << "STUDENT RECORDS\n--------------" << endl;
    bool run = true;
    Records record;
    while (run) { // while command isn't quit
        string line, command, first, last, score, course;
        long id = 0;
        string newid;
        cout << "Valid commands : addstudent, addgrad, addscore, editpscore, delete, change, addbonus, print,save,load, quit\n";
        cout << "What would you like to do?: ";

        getline(cin, line); //get line of input
        istringstream stream(line);    //go string by string
        stream >> command >> first >> last >> score >> course; //initialize

        //make input lowercase
        toLower(command);
        toLower(first);
        toLower(last);
        toLower(course);

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
                cout << "Enter ID : " << endl;
                cin >> newid;
                getchar();
                while (checkForLetter(newid))
                {
                    cout << "No Letters Allowed, try again : " << endl;
                    cin >> newid;
                    getchar();
                }
                while (!record.checkID(stol(newid)))
                {
                    cout << "ID already exists, try again : " << endl;
                    cin >> newid;
                    getchar();
                }
                id = stol(newid);
                int check;
                if (command == "addstudent") {
                    check = record.addstudent(first, last, id);
                }
                else {
                    check = record.addgrad(first, last, id);
                }

                if (check == -2) { // If student is already in database
                    cout << "This student already exists in database.\n";
                }
                else if (check == -1) { //If database is full
                    cout << "Database is at max capacity.\n";
                }
            }
        }

        else if (command == "change")//changes   # A NEW FUNCTIONALITY ---------------------------------------------
        {
            cout << "What would you like to change?\n 1 - Name\n 2 - ID\n 3 - delete score by index\n 4 - change course name by indx\n";
            int choice = 0;
            string firstt, lastt;
            long lid = 0;
            cin >> choice;
            getchar();
            switch (choice)
            {
            case 1:

                cout << "Enter the id of the name you want to change: ";
                cin >> firstt;
                if (firstt == "")
                {
                    cout << "Invalid arguments.\n";
                }
                if (!checkForLetter(firstt))
                {
                    if (record.checkID(stol(firstt))) { //If full name is not given
                        cout << "Please enter id again.\n";
                    }
                    else
                    {
                        record.changename(firstt);
                    }
                }
                else
                {
                    cout << "Invalid arguments\n";
                }


                break;

            case 2:

                cout << "Enter the id you want to change:";
                cin >> lid;
                getchar();

                if (record.checkID(lid) == false)
                {
                    record.changeid(lid);
                }
                else if (record.checkID(lid) == true)
                    cout << "There is no student with this ID! \n";
                break;
            case 3:
                cout << "Enter the id you want to change : ";

                cin >> lid;
                if (record.checkID(lid) == false)
                {
                    getchar();
                    cout << "Enter the index you want delete : ";
                    int index;
                    cin >> index;
                    if (record.checkIndex(lid, index))
                        record.deletescoredex(index, lid);
                }
                else
                {
                    cout << "There is no student with this ID! \n";
                    getchar();
                }

                break;
            case 4:
                cout << "Enter the id you want to change : ";
                cin >> lid;
                if (record.checkID(lid) == false)
                {
                    getchar();
                    cout << "Enter the index you want change : ";
                    int index;
                    cin >> index;
                    cout << "Enter new course name : ";
                    string newName;
                    cin >> newName;
                    if (newName == "") {
                        cout << "Invalid name.\n";
                    }
                    else if (!checkName(newName)) {
                        cout << "Please enter the name again.\n";
                    }
                    else if (record.checkIndex(lid, index))
                    {
                        record.changecourseName(index, lid, newName);
                    }
                }
                else cout << "There is no student with this ID! \n";

                break;
            default:
                cout << "Invalid input" << endl;
            }
        }

        else if (command == "editpscore") { //add pscore
            bool work = true;
            char flag;
            int counter = 0;
            if (first == "" || last == "" || score == "")
            {
                cout << "Invalid Arguments" << endl;
                work = false;
            }
            if (checkForLetter(first))
                work = false;
            if (work)
                flag = record.get_type(stol(first));
            if (work && flag == 'G')
            {
                bool check;
                check = record.addprojscore(stol(first), last, score);
                if (!check)
                { //check if score could be added
                    cout << "Could not add score.\n";
                }
            }
            if (!work || flag == 'i')
            {
                cout << "ID NOT FOUND" << endl;
                counter++;
            }
            if (counter == 0 && flag == 'U')
                cout << "Can't add pscore for student" << endl;
        }
        else if (command == "addscore") { //add score
            bool work = true;
            char flag;
            int counter = 0;
            if (first == "" || last == "" || score == "")
            {
                cout << "Invalid Arguments" << endl;
                counter++;
                work = false;
            }
            if (checkForLetter(first))
                work = false;
            if (work)
                flag = record.get_type(stol(first));
            if (work && flag == 'U')
            {
                bool check;
                check = record.addscore(stol(first), last, score);
                if (!check)
                { //check if score could be added
                    cout << "Could not add score.\n";
                }
            }
            if ((!work || flag == 'i') && !counter)
            {
                cout << "ID NOT FOUND" << endl;
                counter++;
            }
            if (counter == 0 && flag == 'G')
                cout << "Can't add score for grad" << endl;
        }
        else if (command == "delete") { //delete student  # A NEW FUNCTIONALITY ---------------------------------------------
            bool work = true;
            int check = 0;
            if (first == "" || last != "") {
                cout << "Invalid arguments.\n";
                work = false;
            }
            if (checkForLetter(first))
            {
                work = false;
            }
            else if ((record.checkID(stol(first)) && work))
            {
                work = false;
                if (check != 1)
                    cout << "No ID found" << endl;
            }

            if (work)
            {
                check = record.deletestudent(stol(first));

            }

        }
        else if (command == "addbonus") {
            bool work = true;
            if (first == "" || last == "") {
                cout << "Invalid Arguments" << endl;
                work = false;
            }
            if (record.checkID(stol(first))) {
                work = false;
                cout << "ID not found\n";
            }
            if (checkForLetter(first)) {
                work = false;
                cout << "Invalid ID/n";
            }
            if (checkForLetter(last)) {
                work = false;
                cout << "Invalid percentage to add\n";
            }
            if (work) {
                bool check;
                check = record.addbonus(stol(first), last);
                if (!check) //check if score could be added
                    cout << "Could not add score.\n";
            }
            else
            {
                cout << "Could not add score.\n";
            }

        }
        else if (command == "editscore") // edit an existing score in the database ------------------------
        {
            int c = 0;
            bool work = true;
            if (first == "" || last != "") {
                work = false;
                c++;
            }
            if (checkForLetter(first) && !c)
            {
                work = false;
                c++;
            }
            if (work)
                if (record.checkID(stol(first)))
                {
                    work = false;
                }

            if (work)
                record.editscore(stol(first));
            if (c)
                cout << "Invalid arguments." << endl;

        }
        else
            cout << "Invalid argument\n";
    }
}

void toLower(string& s)
{
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

bool checkForLetter(string& n) // check if there is a letter in the string
{
    for (int i = 0; i < n.length(); i++)
    {
        if (n[i] < '0' || n[i]>'9')
            return true;
    }
    return false;
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
