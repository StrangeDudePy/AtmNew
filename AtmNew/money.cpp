#include <iostream>
#include "money.h"
#include "./sqlite-amalgamation-3420000/sqlite3.h"
#include <string>
#include "login.h"
#include "Logo.h"
#include <limits>
using namespace std;
int passing_id;
signupmenu tra;
moneytra objec;


int moneytra::withdraw() {
    sqlite3* db;
    int rc = sqlite3_open("accounts.db", &db);
    sqlite3_stmt* stmt_with;

    int idp, withdrawv,stationw;
    string tpass, psp;

    cout << "Enter Your ID:";
    cin >> idp;
    cout << "Enter Your Password:";
    cin >> tpass;
    stationw=tra.blockcheck(idp);


    if (stationw == 1) {
        cout << "You Have Been Blocked From Banking Services.Contact With Us For Further Information" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþi temizler
        cout << "Press enter to return to the main menu";
        cin.get(); // Bir tuþa basýlmasýný bekler
        system("cls");
        return 1;

    }


    else {
       
        if (rc != SQLITE_OK) { //delete this later
            cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
            return 0;
        }

        string selectQuery = "SELECT ID, PASSWORD FROM Users WHERE ID =" + to_string(idp) + ";";
        rc = sqlite3_prepare_v2(db, selectQuery.c_str(), -1, &stmt_with, 0);

        if (rc == SQLITE_OK) {
            if (sqlite3_step(stmt_with) == SQLITE_ROW) {
                int dbId = sqlite3_column_int(stmt_with, 0);
                const unsigned char* passing = sqlite3_column_text(stmt_with, 1);
                psp = reinterpret_cast<const char*>(passing);

                if (idp == dbId && tpass == psp) {
                    cout << "Enter the value of the money you want to withdraw from your account: ";
                    cin >> withdrawv;

                    string balanceQuery = "SELECT BALANCE FROM Users WHERE ID =" + to_string(idp) + ";";
                    sqlite3_stmt* stmt_balance_;
                    rc = sqlite3_prepare_v2(db, balanceQuery.c_str(), -1, &stmt_balance_, 0);

                    if (rc == SQLITE_OK) {
                        if (sqlite3_step(stmt_balance_) == SQLITE_ROW) {
                            int curbalance = sqlite3_column_int(stmt_balance_, 0);
                            if (curbalance - withdrawv < 0) {
                                cout << "Transaction Failed, Insufficient Balance" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþ tamamýný temizler
                                cout << "Press enter to return to the main menu";
                                cin.get(); // Bir tuþa basýlmasýný bekler
                                system("cls");
                                return 1;
                            }
                            else {
                                int leftbalance = curbalance - withdrawv;
                                string updateQuery = "UPDATE Users SET BALANCE = " + to_string(leftbalance) + ", OUTCOME = " + to_string(withdrawv) + " WHERE ID = " + to_string(idp) + ";";
                                int rc_update = sqlite3_exec(db, updateQuery.c_str(), 0, 0, 0);
                                if (rc_update == SQLITE_OK) {
                                    cout << "Transaction Successful! Amount Withdrawn From Your Account: " << withdrawv << endl;
                                    cout << "Remaining Balance: " << leftbalance << endl;
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþ tamamýný temizler
                                    cout << "Press enter to return to the main menu";
                                    cin.get(); // Bir tuþa basýlmasýný bekler
                                    system("cls");
                                    return 1;
                                }
                                else {
                                    cerr << "Failed to update balance: " << sqlite3_errmsg(db) << endl;
                                }
                                sqlite3_finalize(stmt_balance_);
                                sqlite3_close(db);
                            }
                        }
                    }
                    sqlite3_finalize(stmt_balance_);
                }
                else {
                    cout << "Invalid ID or Password." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþ tamamýný temizler
                    cout << "Press enter to return to the main menu";
                    cin.get(); // Bir tuþa basýlmasýný bekler
                    system("cls");
                    return 1;
                }
            }
           
        }
        
    }
    sqlite3_finalize(stmt_with);
    sqlite3_close(db);
}



int moneytra::depposit() {
    sqlite3* db;
    int rc_dep = sqlite3_open("accounts.db", &db);
    sqlite3_stmt* stmt_deposit;

    int depvalue, idp_dep,station_dep;
    string tpas_dep, psp_dep;

    cout << "Enter Your ID: ";
    cin >> idp_dep;
    cout << "Enter Your Password: ";
    cin >> tpas_dep;
    station_dep=tra.blockcheck(idp_dep);

    if(station_dep==1){
        cout << "You Have Been Blocked From Banking Services.Contact With Us For Further Information" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþi temizler
        cout << "Press enter to return to the main menu";
        cin.get(); // Bir tuþa basýlmasýný bekler
        system("cls");
        return 1;
    }
    
    
    else {
        if (rc_dep != SQLITE_OK) {
            cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
            return 0;
        }

        string selectQuery_dep = "SELECT ID, PASSWORD FROM Users WHERE ID =" + to_string(idp_dep) + ";";
        rc_dep = sqlite3_prepare_v2(db, selectQuery_dep.c_str(), -1, &stmt_deposit, 0);
        if (rc_dep == SQLITE_OK) {
            if (sqlite3_step(stmt_deposit) == SQLITE_ROW) {
                int id_dep = sqlite3_column_int(stmt_deposit, 0);
                const unsigned char* passing_dep = sqlite3_column_text(stmt_deposit, 1);
                psp_dep = reinterpret_cast<const char*>(passing_dep);

                if (idp_dep == id_dep && tpas_dep == psp_dep) {
                    cout << "Enter the Amount You Want To Deposit Into Your Account: ";
                    cin >> depvalue;
                    if (depvalue > 10000) {
                        cout << "You Cannot Deposit More Than 10000 At A Time" << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Press enter to return to the main menu";
                        cin.get();
                        system("cls");
                        return 1;
                    }

                    if (depvalue < 0) {
                        cout << "Invalid Value" << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Press enter to return to the main menu";
                        cin.get();
                        system("cls");
                        return 1;
                    }

                    else {
                        string balanceQuery_dep = "SELECT BALANCE FROM Users WHERE ID =" + to_string(idp_dep) + ";";
                        sqlite3_stmt* stmt_balance;
                        rc_dep = sqlite3_prepare_v2(db, balanceQuery_dep.c_str(), -1, &stmt_balance, 0);

                        if (rc_dep == SQLITE_OK) {
                            if (sqlite3_step(stmt_balance) == SQLITE_ROW) {
                                int curbalance_dep = sqlite3_column_int(stmt_balance, 0);
                                int lastbalance_dep = curbalance_dep + depvalue;
                                string updateQuery = "UPDATE Users SET BALANCE = " + to_string(lastbalance_dep) + ", INCOME = " + to_string(depvalue) + " WHERE ID = " + to_string(idp_dep) + ";";
                                int execResult = sqlite3_exec(db, updateQuery.c_str(), 0, 0, 0);
                                if (execResult == SQLITE_OK) {
                                    cout << "Transaction Successful! Money Deposited to Your Account: " << depvalue << endl;
                                    cout << "Current Balance: " << lastbalance_dep << endl;
                                }
                                sqlite3_finalize(stmt_balance);
                                sqlite3_close(db);
                            }
                        }
                     
                    }
                }
                else {
                    cout << "Invalid ID or Password." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Press enter to return to the main menu";
                    cin.get();
                    system("cls");
                    return 1;
                }
            }
   
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press enter to return to the main menu";
            cin.get();
            system("cls");
            return 1;
        }
        
       
    }
}

 
int moneytra::useraccount() {
    int tid_user;
    int outcome = 0;
    int income = 0;
    int balance_user = 0;
    int station_user;
    string tpass_user, psp_user;

    sqlite3* db;
    int rc_user = sqlite3_open("accounts.db", &db);
    sqlite3_stmt* stmt_user;
    cout << "Enter Your ID:";
    cin >> tid_user;
    cout << "Enter Your Password:";
    cin >> tpass_user;
    station_user = tra.blockcheck(tid_user);

    if (station_user == 1) {
        cout << "You Have Been Blocked From Banking Services. Contact Us For Further Information" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press enter to return to the main menu";
        cin.get();
        system("cls");
        return 1;
    }
    else {
        if (rc_user != SQLITE_OK) {
            cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
            return 0;
        }

        string selectQuery_user = "SELECT ID, PASSWORD FROM Users WHERE ID =" + to_string(tid_user) + ";";
        rc_user = sqlite3_prepare_v2(db, selectQuery_user.c_str(), -1, &stmt_user, 0);
        if (rc_user == SQLITE_OK) {
            if (sqlite3_step(stmt_user) == SQLITE_ROW) {
                int id_user = sqlite3_column_int(stmt_user, 0);
                const unsigned char* passing_user = sqlite3_column_text(stmt_user, 1);
                psp_user = reinterpret_cast<const char*>(passing_user);
                if (tid_user == id_user && tpass_user == psp_user) {
                    sqlite3_stmt* stmt_income;
                    string selectQuery_INCOME = "SELECT INCOME  FROM Users WHERE ID =" + to_string(tid_user) + ";";
                    int rc_income = sqlite3_prepare_v2(db, selectQuery_INCOME.c_str(), -1, &stmt_income, 0);
                    if (rc_income == SQLITE_OK) {
                        if (sqlite3_step(stmt_income) == SQLITE_ROW) {
                            income = sqlite3_column_int(stmt_income, 0);
                        }
                        sqlite3_finalize(stmt_income);
                    }
                    sqlite3_stmt* stmt_outcome;
                    string selectQuery_OUTCOME = "SELECT OUTCOME FROM Users WHERE ID =" + to_string(tid_user) + ";";
                    int rc_outcome = sqlite3_prepare_v2(db, selectQuery_OUTCOME.c_str(), -1, &stmt_outcome, 0);
                    if (rc_outcome == SQLITE_OK) {
                        if (sqlite3_step(stmt_outcome) == SQLITE_ROW) {
                            outcome = sqlite3_column_int(stmt_outcome, 0);
                        }
                        sqlite3_finalize(stmt_outcome);
                    }
                    sqlite3_stmt* stmt_balance;
                    string selectQuery_BALANCE = "SELECT BALANCE FROM User WHERE ID = " + to_string(tid_user) + ";";
                    int rc_balance = sqlite3_prepare_v2(db, selectQuery_BALANCE.c_str(), -1, &stmt_balance, 0);
                    if (rc_balance == SQLITE_OK) {
                        if (sqlite3_step(stmt_balance) == SQLITE_ROW) {
                            balance_user = sqlite3_column_int(stmt_balance, 0);
                        }
                        sqlite3_finalize(stmt_balance);
                    }

                    cout << "ID          INCOME          OUTCOME          BALANCE" << endl;
                    cout << tid_user << "          " << income << "          " << outcome << "          " << balance_user << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Press enter to return to the main menu";
                    cin.get();
                    system("cls");
                    sqlite3_finalize(stmt_user);
                    sqlite3_close(db);
                    return 1;
                }
                else {
                    cout << "Invalid ID or Password." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Press enter to return to the main menu";
                    cin.get();
                    system("cls");
                    sqlite3_finalize(stmt_user);
                    sqlite3_close(db);
                    return 1;
                }
            }
        }
    }

    sqlite3_finalize(stmt_user);
    sqlite3_close(db);
    return 0;
}



int moneytra::sentmoney() {
    sqlite3* db;
    int rc_transfer = sqlite3_open("accounts.db", &db);
    sqlite3_stmt* stmt_sent;

    int sent_id, transfer_sent, recid,station_sent;
    string sent_pass, rec_pass, psp_sent;
    cout << "Enter Your ID: ";
    cin >> sent_id;
    cout << "Enter Your Password: ";
    cin >> sent_pass;
    station_sent=tra.blockcheck(sent_id);
    if (station_sent == 1) {
        cout << "You Have Been Blocked From Banking Services. Contact Us For Further Information" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press enter to return to the main menu";
        cin.get();
        system("cls");
        sqlite3_close(db);
        return 1;
    }
    else {
        if (rc_transfer != SQLITE_OK) {
            cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
            return 0;
        }
        string selectQuery_dep = "SELECT ID, PASSWORD FROM Users WHERE ID = " + to_string(sent_id) + ";";
        rc_transfer = sqlite3_prepare_v2(db, selectQuery_dep.c_str(), -1, &stmt_sent, 0);
        if (rc_transfer == SQLITE_OK) {
            if (sqlite3_step(stmt_sent) == SQLITE_ROW) {
                int id_sent = sqlite3_column_int(stmt_sent, 0);
                const unsigned char* passing_transfer = sqlite3_column_text(stmt_sent, 1);
                psp_sent = reinterpret_cast<const char*>(passing_transfer);
                if (sent_pass == psp_sent && sent_id == id_sent) {
                    sqlite3_stmt* stmt_sentmoney;
                    string selectQuery_BALANCE = "SELECT BALANCE FROM Users WHERE ID = " + to_string(sent_id) + ";";
                    int rc_sentbalance = sqlite3_prepare_v2(db, selectQuery_BALANCE.c_str(), -1, &stmt_sentmoney, 0);
                    if (rc_sentbalance == SQLITE_OK) {
                        if (sqlite3_step(stmt_sentmoney) == SQLITE_ROW) {
                            int balance_sent = sqlite3_column_int(stmt_sentmoney, 0);

                            cout << "Enter Amount Of Money You Want To Transfer: ";
                            cin >> transfer_sent;
                            cout << "Enter the ID of the Recipient: ";
                            cin >> recid;
                            if (balance_sent - transfer_sent < 0) {
                                cout << "Insufficient Balance, Transaction Failed" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Press enter to return to the main menu";
                                cin.get(); // Bir tuþa basýlmasýný bekler
                                system("cls");
                                return 1;
                            }
                            else {
                                sqlite3_stmt* stmt_rec;
                                string selectQuery_RECBALANCE = "SELECT BALANCE FROM Users WHERE ID = " + to_string(recid) + ";";
                                int rc_balance = sqlite3_prepare_v2(db, selectQuery_RECBALANCE.c_str(), -1, &stmt_rec, 0);
                                if (rc_balance == SQLITE_OK) {
                                    if (sqlite3_step(stmt_rec) == SQLITE_ROW) {
                                        int balance_rec = sqlite3_column_int(stmt_rec, 0);
                                        int balance_rec_final = balance_rec + transfer_sent;
                                        int balance_sent_final = balance_sent - transfer_sent;
                                        string updateQuerysent = "UPDATE Users SET BALANCE = " + to_string(balance_rec_final) + " WHERE ID = " + to_string(recid) + ";";
                                        rc_balance = sqlite3_exec(db, updateQuerysent.c_str(), 0, 0, 0);
                                        if (rc_balance == SQLITE_OK) {
                                            string updateQuerysent_balance = "UPDATE Users SET BALANCE = " + to_string(balance_sent_final) + ",OUTCOME = " + to_string(balance_sent) + " WHERE ID = " + to_string(sent_id) + ";";
                                            rc_balance = sqlite3_exec(db, updateQuerysent_balance.c_str(), 0, 0, 0);
                                            if (rc_balance == SQLITE_OK) {
                                                cout << "Transaciton Succesful,Money Sent!" << endl;
                                                cout << "Current Balance: " << balance_sent_final << endl;
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                cout << "Press enter to return to the main menu";
                                                cin.get(); // Bir tuþa basýlmasýný bekler
                                                system("cls");
                                                return 1;

                                            }
                                        }
                                    }
                                    else {
                                        cout << "Recipient ID does not exist." << endl;
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "Press enter to return to the main menu";
                                        cin.get(); // Bir tuþa basýlmasýný bekler
                                        system("cls");
                                        return 1;
                                    }
                                }
                                sqlite3_finalize(stmt_rec);
                                
                            }
                        }
                    }
                }
                else {
                    cout << "Invalid ID or Password." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþi temizler
                    cout << "Press enter to return to the main menu";
                    cin.get();
                    system("cls");
                    return 1;
                }
            }
        }

        sqlite3_finalize(stmt_sent);
        sqlite3_close(db);

    }
}


int moneytra::blockuser() {

    sqlite3* db;
    int rc_admin = sqlite3_open("accounts.db", &db);
    int id_B = 0;
   
      



    if (rc_admin != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    char* errMsg;
    string blockQuery = "CREATE TABLE IF NOT EXISTS BLOCKED_USERS (BLOCKED_ID PRIMARY KEY);";
    rc_admin = sqlite3_exec(db, blockQuery.c_str(), 0, 0, &errMsg);


    if (rc_admin != SQLITE_OK) {
        cerr << "System Error " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    cout << "Enter ID Of User You Want The Block From Banking Services:";
    cin >> id_B;
    string addblockedQuery("INSERT INTO BLOCKED_USERS (BLOCKED_ID) VALUES (" + to_string(id_B) + ");");
    rc_admin = sqlite3_exec(db, addblockedQuery.c_str(), 0, 0, 0);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Press enter to return to the main menu";
    cin.get(); // Bir tuþa basýlmasýný bekler
    system("cls");
    return 1;


   }


int moneytra::unblockuser() {
    sqlite3* db;
    int rc_UBadmin = sqlite3_open("accounts.db", &db);
    int id_UB = 0;
   

    if (rc_UBadmin != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }
    cout << "Enter An ID";
    cin >> id_UB;

    



    sqlite3_stmt* bidfind_stmt;
    string UBFindQuerry="SELECT BLOCKED_ID FROM BLOCKED_USERS WHERE BLOCKED_ID =" + to_string(id_UB) + ";";
    int rc_unb = sqlite3_prepare_v2(db, UBFindQuerry.c_str(), -1, &bidfind_stmt, 0);
    if(rc_unb==SQLITE_OK)
    {
        if (sqlite3_step(bidfind_stmt) == SQLITE_ROW) {
            string DeleteQuerry = "UPDATE BLOCKED_USERS SET BLOCKED_ID=NULL WHERE BLOCKED_ID=" + to_string(id_UB) + ";";
            sqlite3_exec(db, DeleteQuerry.c_str(), 0, 0, 0);
            cout << "User Succesfuly Unblocked!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press enter to return to the main menu";
            cin.get(); // Bir tuþa basýlmasýný bekler
            system("cls");
            return 1;

        }
        else {
            cout << "User Doesn't Exists Or User Not Blocked" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press enter to return to the main menu";
            cin.get(); // Bir tuþa basýlmasýný bekler
            system("cls");
            return 1;

        }
        
        }
    
    
    
    
    }


int moneytra::deleteuser(){
    sqlite3* db;
    int rc_deladmin = sqlite3_open("accounts.db", &db);
    int id_del = 0;
    int id_delcheck = 1;

    if (rc_deladmin != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    cout << "Enter the ID value of the User you want to delete from the system." << endl;
    cin >> id_del;
    cout << "Enter ID Againt To Confirm";
    cin >> id_delcheck;
    if (id_del == id_delcheck) {
           string DeleteUserQuery = "DELETE FROM Users WHERE ID=" + to_string(id_del) + ";";
           sqlite3_exec(db, DeleteUserQuery.c_str(), 0, 0, 0);
           cout << "User Deleted Succesfuly";
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
           cout << "Press enter to return to the main menu";
           cin.get(); // Bir tuþa basýlmasýný bekler
           system("cls");
           return 1;
    }


    else {
        cout << "IDs Dont Match"<<endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press enter to return to the main menu";
        cin.get(); // Bir tuþa basýlmasýný bekler
        system("cls");
        return 1;
    }
        
    }



    

void moneytra::adminactions() {
    int selected;



    cout << "--- ADMIN PANEL ---"<<endl;
    cout << "1-Block User"<<endl;
    cout << "2-Unblock User"<<endl;
    cout << "3-Delete User" << endl;
    cout << "Choose An Action:" << endl;
    cin >> selected;
    switch (selected)
    {

    case 1:
        objec.blockuser();
        break;

    
    case 2:
        objec.unblockuser();
        break;

    case 3:
        objec.deleteuser();
        break;

    default:
        break;
    }

}