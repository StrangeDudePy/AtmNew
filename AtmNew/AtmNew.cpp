#include <iostream>
#include <Windows.h>
#include "Logo.h"
#include "login.h"
#include "sqlite-amalgamation-3420000/sqlite3.h"




class MenuChoices {

    int decision( int chosen_) {
        switch (chosen_)
        {

        case 1:
            int login();

        case 2:



        case 3:

        default:
            break;
        }


    }


};


using namespace std;
int choie;

int main() {
    while (true) {
        system("Color 0B");
        writeLogo();
        cout << " " << endl;
        cout << " " << endl;
        cout << " " << endl;
        cout << "Enter your choice";
        cin >> choie;
        cout << " " << endl;

      

    }
}