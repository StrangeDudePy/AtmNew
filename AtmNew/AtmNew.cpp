#include <iostream>
#include <Windows.h>
#include "Logo.h"
#include "login.h"
#include "sqlite-amalgamation-3420000/sqlite3.h"

signupmenu obj;

class MenuChoices {
public:
    int decision(int chosen_, signupmenu& menu) {
        switch (chosen_) {
        case 1:
            break;
        case 2:
        menu.newuser();
        break;
        case 3:
            break;
        default:
            break;
        }
    
        return 0;
    }

};

using namespace std;
int choie;

int main() {
    system("Color 0B");
    writeLogo();
    cout << " " << endl;
    cout << " " << endl;
    cout << " " << endl;
    cout << "Enter your choice: ";
    cin >> choie;
    cin.ignore();
    MenuChoices choc;
    choc.decision(choie, obj);

   
}