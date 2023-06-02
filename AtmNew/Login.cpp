#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>

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
    string convertToTitleCase(const string& input) {
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

    string removeSpaces(const string& str) {
        string result = str;
        result.erase(0, result.find_first_not_of(" "));
        result.erase(result.find_last_not_of(" ") + 1);
        return result;
    }

    int newuser(string(*function)(const string& input)) {
        int telno, id;
        string name, password, confirmPassword, idString;
        cin.ignore();

        while (true) {
            cout << "Enter Your  Full Name: ";
            getline(cin, name);

            if (name.empty()) {
                cout << "Invalid Input!" << endl;
                continue;
            }

            string convertedName = function(name);
            break;
        }

        while (true) {
            cout << "Enter Your ID: ";
            cin >> id;
            cin.ignore();
            idString = to_string(id);

            if (idString.length() != 11) {
                cout << "Invalid ID! ID Must Be 11 Characters Long" << endl;
                continue;
            }

            break;
        }

        while (true) {
            cout << "Enter a password: ";
            getline(cin, password);

            password = removeSpaces(password);

            if (password.length() < 8) {
                cout << "Password must be at least 8 characters long." << endl;
                continue;
            }
            else if (password.length() > 16) {
                cout << "Password length cannot exceed 16 characters." << endl;
                continue;
            }
            else if (password[0] == ' ') {
                cout << "Password cannot start with a space." << endl;
                continue;
            }

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

        ofstream MyFile(idString.append(".txt"), ios::out);
        MyFile << name << "-" << id << "-" << password << endl;

        return 0;



    }


};



