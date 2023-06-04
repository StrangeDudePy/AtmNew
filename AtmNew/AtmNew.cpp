#include <iostream>
#include <Windows.h>
#include "Logo.h"
#include "login.h"
#include "sqlite-amalgamation-3420000/sqlite3.h"
#include "money.h"
moneytra obj2;

signupmenu obj;

class MenuChoices {
public:
    int decision(int chosen_, signupmenu& menu) {
        int dec;
        string admin_pass = "ATMAdmin";
        string enteredpass;
        switch (chosen_) {
       
        case 1:
        menu.newuser();
        break;
        
        case 2:
            cout << "Welcome" << ::endl;
            cout << "Select A Transaction" << endl;
            cout << "1-Withdraw Money" << endl;
            cout << "2-Deposit Money" << endl;
            cout << "3-Account Information" << endl;
            cout << "4-Sent Money" << endl;;
            cin >> dec;
            if (dec == 1) {
                obj2.withdraw();
                cout << "Press enter to return to the main menu";
                cin.get();
                system("cls");
                writeLogo();
            }

            if (dec == 2) {
                obj2.depposit();
                cout << "Press enter to return to the main menu";
                cin.get();
                system("cls");
                writeLogo();
            }

            if (dec == 3) {
                obj2.useraccount();
                cout << "Press enter to return to the main menu";
                cin.get();
                system("cls");
                writeLogo();
            }

            if (dec == 4) {
                obj2.sentmoney();
                cout << "Press enter to return to the main menu";
                cin.get();
                system("cls");
                writeLogo();
            }
            
        case 3:
            
             cout << "Enter Admin Password:";
             cin >> admin_pass;
             if (enteredpass == admin_pass) {
                 obj.readUsersFromDatabase("accounts.db");
                 cout << "Press enter to return to the main menu";
                 cin.get();
                 system("cls");
                 writeLogo();
             }

             else {
                 cout << "Access Denied";
                 return 0;
             }
          
        default:
            break;
        }
    
        return 0;
    }

};

using namespace std;
int choie;

void runMenu() {
    system("Color 0B");
    writeLogo();
    cout << " " << endl;
    cout << " " << endl;
    cout << " " << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    MenuChoices choc;
    choc.decision(choice, obj);
}

int main() {
    runMenu();

   
}