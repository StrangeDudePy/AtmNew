#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>
#include "sqlite-amalgamation-3420000/sqlite3.h"
#include <algorithm>

using namespace std;
int ID, Pass, noftry;


class loginmenu {
public:
    int  login(void) {

        cout << "ID: ";
        cin >> ID;
        cout << "Password:  ";
        cin >> Pass;




    }


    int logcheck(int A, int B) {
        return 0;
    }

    int forgotpass(int a, int b) {

    }




};





class signupmenu {
public:
    string removeSpaces(const string& str) {
        string fname = str;
        fname.erase(0, fname.find_first_not_of(" "));
        fname.erase(fname.find_last_not_of(" ") + 1);
        return fname;
    }

    string formatName(const string& input) {
        istringstream iss(input);
        string word, result;

        while (iss >> word) {
            if (!result.empty()) {
                result += " ";
            }

            if (!word.empty()) {
                word[0] = toupper(word[0]);
                result += word;
            }
        }

        return result;
    }

    string getName() {
        string name;

        while (true) {
            cout << "Enter Your Full Name: ";
            getline(cin, name);

            if (name.empty()) {
                cout << "Invalid Input!" << endl;
            }
            else {
                break;
            }
        }

        return name;
    }

    bool is_digits(const string& str) {
        return all_of(str.begin(), str.end(), ::isdigit);
    }
    int getID() {
        string idString;

        while (true) {
            cout << "Enter Your ID: ";
            getline(cin, idString);

            if (idString.length() != 11) {
                cout << "Invalid ID! ID Must Be 11 Characters Long" << endl;
            }
            else if (!is_digits(idString)) {
                cout << "Invalid ID! ID must contain only numeric characters" << endl;
            }
            else {
                break;
            }
        }

        int id = stoi(idString);
        return id;
    }

    string getPassword() {
        string password, confirmPassword;

        while (true) {
            cout << "Enter a password: ";
            getline(cin, password);

            password = removeSpaces(password);

            if (password.length() < 8) {
                cout << "Password must be at least 8 characters long." << endl;
            }
            else if (password.length() > 16) {
                cout << "Password length cannot exceed 16 characters." << endl;
            }
            else if (password[0] == ' ') {
                cout << "Password cannot start with a space." << endl;
            }
            else {
                cout << "Confirm password: ";
                getline(cin, confirmPassword);

                confirmPassword = removeSpaces(confirmPassword);

                if (password == confirmPassword) {
                    cout << "Password successfully set." << endl;
                    break;
                }
                else {
                    cout << "Passwords do not match. Please try again." << endl;
                }
            }
        }

        return password;
    }

    int newuser() {
        string name = getName();
        string formattedName = formatName(name);
        int id = getID();
        string password = getPassword();

        sqlite3* db;
        int rc = sqlite3_open("database.db", &db);
        string insertQuery = "INSERT INTO Users (ID, FULL_NAME, PASSWORD) VALUES (" + to_string(id) + ", '" + formattedName + "', '" + password + "');";

        char* errMsg;
        rc = sqlite3_exec(db, insertQuery.c_str(), 0, 0, &errMsg);

        if (rc != SQLITE_OK) {
            if (string(errMsg).find("UNIQUE constraint failed: Users.ID") != string::npos) {
                cerr << "ID already exists." << endl;
            }
            sqlite3_close(db);
            return 0;
        }
    }
};