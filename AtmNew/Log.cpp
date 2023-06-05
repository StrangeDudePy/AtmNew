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

string signupmenu::convertToLowerCase(string name) {
    string lowercaseName;
    string::size_type length = name.length();
    bool newWord = true;

    for (string::size_type i = 0; i < length; i++) {
        if (isalpha(name[i])) {
            if (newWord) {
                lowercaseName += toupper(name[i]);
                newWord = false;
            }
            else {
                lowercaseName += tolower(name[i]);
            }
        }
        else {
            lowercaseName += name[i];
            newWord = true;
        }
    }

    return lowercaseName;
}


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
    bool nameValid = false;

    while (!nameValid) {
        cout << "Enter Your Full Name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Invalid Input!" << endl;
        }
        else {
            nameValid = true;
        }
    }

    return name;
}
  


bool signupmenu::is_digits(const string& str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

int signupmenu::getID() {
    string idString;
    bool idValid = false;

    while (!idValid) {
        cout << "Enter Your ID (ID Must Be 8 Characters Long): ";
        getline(cin, idString);

        if (idString.length() != 8) {
            cout << "Invalid ID! ID Must Be 8 Characters Long" << endl;
        }
        else if (!is_digits(idString)) {
            cout << "Invalid ID! ID must contain only numeric characters" << endl;
        }
        else {
            idValid = true;
        }
    }

    int id = stoi(idString);
    return id;
}



string signupmenu::getPassword() {
    string password, confirmPassword;
    bool passwordValid = false;

    while (!passwordValid) {
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
                cout << "" << endl;
                passwordValid = true;
            }
            else {
                cout << "Passwords do not match. Please try again." << endl;
            }
        }
    }

    return password;
}



int signupmenu::newuser() {
    int idn = getID();
    string name = getName();
    string formattedName = formatName(name);
    string lastversion = convertToLowerCase(formattedName);
    string password = getPassword();

    sqlite3* db;
    int rc = sqlite3_open("accounts.db", &db);

    if (rc != SQLITE_OK) { 
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    string createTableQuery = "CREATE TABLE IF NOT EXISTS Users (ID INT PRIMARY KEY, FULL_NAME TEXT, PASSWORD TEXT, INCOME INT DEFAULT 0, OUTCOME INT DEFAULT 0, BALANCE INT DEFAULT 0);";

    char* errMsg;
    rc = sqlite3_exec(db, createTableQuery.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "System Error " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    string selectQuery = "SELECT ID FROM Users WHERE ID = " + to_string(idn) + ";";
    sqlite3_stmt* stmt_select;

    rc = sqlite3_prepare_v2(db, selectQuery.c_str(), -1, &stmt_select, 0);
    if (rc == SQLITE_OK) {
        if (sqlite3_step(stmt_select) == SQLITE_ROW) {
            cout << "ID already exists." << endl;
            sqlite3_finalize(stmt_select);
            sqlite3_close(db);
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþi temizler
            cout << "Press enter to return to the main menu";
            cin.get(); // Bir tuþa basýlmasýný bekler
            system("cls");
            return 1;
            
        }
    }
  

    sqlite3_finalize(stmt_select);

    string insertQuery = "INSERT INTO Users (ID, FULL_NAME, PASSWORD, INCOME, OUTCOME, BALANCE) VALUES (" + to_string(idn) + ", '" + lastversion + "', '" + password + "', 0, 0, 0);";

    rc = sqlite3_exec(db, insertQuery.c_str(), 0, 0, &errMsg);

    cout << "Registration Successful" << endl;

    sqlite3_close(db);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþi temizler
    cout << "Press enter to return to the main menu";
    cin.get(); // Bir tuþa basýlmasýný bekler
    system("cls");
    return 1;
    

}


signupmenu::signupmenu() {
   
}

void signupmenu::readUsersFromDatabase(const string& databasePath) {
    sqlite3* db;
    int rc = sqlite3_open(databasePath.c_str(), &db);
    if (rc != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    string selectQuery = "SELECT ID, INCOME, OUTCOME, BALANCE, PASSWORD, FULL_NAME FROM Users;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, selectQuery.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cerr << "Failed to execute select query: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int userID = sqlite3_column_int(stmt, 0);
        int income = sqlite3_column_int(stmt, 1);
        int outcome = sqlite3_column_int(stmt, 2);
        int balance = sqlite3_column_int(stmt, 3);
        const unsigned char* password = sqlite3_column_text(stmt, 4);
        const unsigned char* fullName = sqlite3_column_text(stmt, 5);

        cout << "User ID: " << userID
            << ", Income: " << income
            << ", Outcome: " << outcome
            << ", Balance: " << balance
            << ", Password: " << password
            << ", Full Name: " << fullName
            << endl;
            
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}



