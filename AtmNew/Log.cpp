#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>
#include "sqlite-amalgamation-3420000/sqlite3.h"
#include <algorithm>
#include "./login.h"
#include "Logo.h"
#include "sqlite-amalgamation-3420000/sqlite3.h"



using namespace std;

int ID, Pass, noftry;


string signupmenu::removeSpaces(const string& str) {
    string fname = str;
    fname.erase(0, fname.find_first_not_of(" "));
    fname.erase(fname.find_last_not_of(" ") + 1);
    return fname;
}

string signupmenu::formatName(const string& input) {
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

string signupmenu::getName() {
    string name;
    cout << "Enter Your Full Name: ";
    getline(cin, name);

    if (name.empty()) {
        cout << "Invalid Input!" << endl;
    }
    else {
        
    }

    return name;
}
  


bool signupmenu::is_digits(const string& str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

int signupmenu::getID() {
    string idString;

        cout << "Enter Your ID: ";
        getline(cin,idString);

        if (idString.length() != 8) {
            cout << "Invalid ID! ID Must Be 8 Characters Long" << endl;
        }
        else if (!is_digits(idString)) {
            cout << "Invalid ID! ID must contain only numeric characters" << endl;
        }
        else {
            
        }
    

    int id = stoi(idString);
    return id;
}

string signupmenu::getPassword() {
    string password, confirmPassword;

 
        cout << "Enter a password: ";
        getline(cin, password);

        password = removeSpaces(password);

        if (password.length() < 8) {
            cout << "Password must be at least 8 characters long." << endl;
            getPassword();
        }
        else if (password.length() > 16) {
            cout << "Password length cannot exceed 16 characters." << endl;
            getPassword();
        }
        else if (password[0] == ' ') {
            cout << "Password cannot start with a space." << endl;
            getPassword();
        }
        else {
            cout << "Confirm password: ";
            getline(cin, confirmPassword);

            confirmPassword = removeSpaces(confirmPassword);

            if (password == confirmPassword) {
                cout << "Password successfully set." << endl;

            }
            else {
                cout << "Passwords do not match. Please try again." << endl;
            }
        }

          return password;
    }




#include <iostream>
#include <vector>

int signupmenu::newuser() {
    int id = getID();
    string name = getName();
    string formattedName = formatName(name);
    string password = getPassword();

    sqlite3* db;
    int rc = sqlite3_open("accounts.db", &db);

    if (rc != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    string createTableQuery = "CREATE TABLE IF NOT EXISTS Users (ID INT PRIMARY KEY, FULL_NAME TEXT, PASSWORD TEXT);";

    char* errMsg;
    rc = sqlite3_exec(db, createTableQuery.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Failed to create table: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    string insertQuery = "INSERT INTO Users (ID, FULL_NAME, PASSWORD) VALUES (" + to_string(id) + ", '" + formattedName + "', '" + password + "');";

    rc = sqlite3_exec(db, insertQuery.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        if (string(errMsg).find("UNIQUE constraint failed: Users.ID") != string::npos) {
            cerr << "ID already exists." << endl;
        }
        else {
            cerr << "Failed to insert user: " << errMsg << endl;
            sqlite3_free(errMsg);
        }

        sqlite3_close(db);
        return 0;
    }

    cout << "User successfully created." << endl;

    // Tabloyu yazdýrma
    string selectQuery = "SELECT * FROM Users;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, selectQuery.c_str(), -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int userID = sqlite3_column_int(stmt, 0);
            const unsigned char* fullName = sqlite3_column_text(stmt, 1);
            const unsigned char* password = sqlite3_column_text(stmt, 2);

            cout << "User ID: " << userID << ", Full Name: " << fullName << ", Password: " << password << endl;
        }
    }
    else {
        cerr << "Failed to execute select query: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


signupmenu::signupmenu() {
   
}