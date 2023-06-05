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
       
            system("cls");
            cout << "Welcome" << ::endl;
            cout << "1-Withdraw Money" << endl;
            cout << "2-Deposit Money" << endl;
            cout << "3-Account Information" << endl;
            cout << "4-Sent Money" << endl;
            cout << "  " << endl;
            cout << "Select A Transaction: ";
            cin >> dec;
            if (dec == 1) {
                obj2.withdraw();
                
                
            }

            if (dec == 2) {
                obj2.depposit();
               
              
               
            }

            if (dec == 3) {
                obj2.useraccount();
               
               
            }

            if (dec == 4) {
                obj2.sentmoney();
                
               
            }
            break;
        case 3:
            
             cout << "Enter Admin Password:";
             cin >> admin_pass;
             if (enteredpass == admin_pass) {
                 obj.readUsersFromDatabase("accounts.db");
                 

             }

             else {
                 cout << "Access Denied";
                 return 0;
             }
          
             break;
        default:
            break;
        }
    
       
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
    
    while (true) {
        runMenu();
    }

   
}