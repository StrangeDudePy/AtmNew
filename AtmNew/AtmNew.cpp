#include <iostream>
#include "Logo.h"
#include "login.h"
#include "sqlite-amalgamation-3420000/sqlite3.h"
#include "money.h"
moneytra obj2;

signupmenu obj;
using namespace std;

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
             cin >> enteredpass;
             if (enteredpass == admin_pass) {
                 obj2.adminactions();
                 

             }

             else {
                 cout << "Access Denied"<<endl;
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 cout << "Press enter to return to the main menu";
                 cin.get();
                 system("cls");
                 return 1;
                 
             }
          
             break;
        default:
            cout << "Invalid Input"<<endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþi temizler
            cout << "Press enter to return to the main menu";
            cin.get(); 
            system("cls");
            return 1;
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