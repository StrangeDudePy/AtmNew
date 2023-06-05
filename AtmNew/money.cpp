#include <iostream>
#include "money.h"
#include "./sqlite-amalgamation-3420000/sqlite3.h"
#include <string>
#include "login.h"
#include "Logo.h"
using namespace std;
int passing_id;
signupmenu tra;


int moneytra::withdraw() {
    sqlite3* db;
    int rc = sqlite3_open("accounts.db", &db);
    sqlite3_stmt* stmt_with;

    int idp, withdrawv;
    string tpass, psp;

    cout << "Enter Your ID:";
    cin >> idp;
    cout << "Enter Your Password:";
    cin >> tpass;

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
        sqlite3_finalize(stmt_with);
    }
    sqlite3_close(db);
}



int moneytra::depposit() {
    sqlite3* db;
    int rc_dep = sqlite3_open("accounts.db", &db);
    sqlite3_stmt* stmt_deposit;

    int depvalue, idp_dep;
    string tpas_dep, psp_dep;

    cout << "Enter Your ID: ";
    cin >> idp_dep;
    cout << "Enter Your Password: ";
    cin >> tpas_dep;

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
                        }
                    }
                    sqlite3_finalize(stmt_balance);
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
        sqlite3_finalize(stmt_deposit);
        sqlite3_close(db);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press enter to return to the main menu";
        cin.get();
        system("cls");
        return 1;
    }
}

 
int moneytra::useraccount() {
    int tid_user;
    int outcome = 0;
    int income = 0;
    int balance_user = 0;
    string tpass_user, psp_user;


    sqlite3* db;
    int rc_user = sqlite3_open("accounts.db", &db);
    sqlite3_stmt* stmt_user;
    cout << "Enter Your ID:";
    cin >> tid_user;
    cout << "Enter Your Password;";
    cin >> tpass_user;



    if (rc_user != SQLITE_OK) { //delete this later
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
            if (tid_user == id_user && tpass_user==psp_user) {
                sqlite3_stmt* stmt_income;
                string selectQuery_INCOME = "SELECT INCOME  FROM Users WHERE ID =" + to_string(tid_user) + ";";
                int rc_income = sqlite3_prepare_v2(db, selectQuery_INCOME.c_str(), -1, &stmt_income, 0);
                if (rc_income == SQLITE_OK) {
                    if (sqlite3_step(stmt_income) == SQLITE_ROW) {
                        int income = sqlite3_column_int(stmt_user, 0);

                    }
                    sqlite3_finalize(stmt_income);
                }
                sqlite3_stmt* stmt_outcome;
                string selectQuery_OUTCOME = "SELECT OUTCOME FROM Users WHERE ID =" + to_string(tid_user) + ";";
                int rc_outcome = sqlite3_prepare_v2(db, selectQuery_OUTCOME.c_str(), -1, &stmt_outcome, 0);
                if (rc_outcome == SQLITE_OK) {
                    if (sqlite3_step(stmt_outcome) == SQLITE_ROW) {
                        int outcome = sqlite3_column_int(stmt_outcome, 0);

                    }
                    sqlite3_finalize(stmt_outcome);
                }
                sqlite3_stmt* stmt_balance;
                string selectQuery_BALANCE = "SELECT BALANCE FROM User WHERE ID = " + to_string(tid_user) + ";";
                int rc_balance = sqlite3_prepare_v2(db, selectQuery_BALANCE.c_str(), -1, &stmt_balance, 0);
                if (rc_balance == SQLITE_OK) {
                    if (sqlite3_step(stmt_balance) == SQLITE_ROW) {
                        int balance_user = sqlite3_column_int(stmt_balance, 0);

                    }
                    sqlite3_finalize(stmt_balance);
                }


                cout << "ID          INCOME          OUTCOME          BALANCE" << endl;
                cout << tid_user << "          " << income << "          " << outcome << "          " << balance_user << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþi temizler
                cout << "Press enter to return to the main menu";
                cin.get(); // Bir tuþa basýlmasýný bekler
                system("cls");
                return 1;
            }
            
            else {
                cout << "Invalid ID or Password." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþi temizler
                cout << "Press enter to return to the main menu";
                cin.get(); // Bir tuþa basýlmasýný bekler
                system("cls");
                return 1;
               
            }

        }
    }
    
    sqlite3_finalize(stmt_user);
    sqlite3_close(db);
}



int moneytra::sentmoney() {
    sqlite3* db;
    int rc_transfer = sqlite3_open("accounts.db", &db);
    sqlite3_stmt* stmt_sent;

    int sent_id, transfer_sent, recid;
    string sent_pass, rec_pass, psp_sent;
    cout << "Enter Your ID: ";
    cin >> sent_id;
    cout << "Enter Your Password: ";
    cin >> sent_pass;
    if (rc_transfer != SQLITE_OK) { //delete this later
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
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþi temizler
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
                                            cout << "Transaciton Succesful,Money Sent!" <<endl;
                                            cout << "Current Balance: " << balance_sent_final << endl;
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþi temizler
                                            cout << "Press enter to return to the main menu";
                                            cin.get(); // Bir tuþa basýlmasýný bekler
                                            system("cls");
                                            return 1;
                                            
                                        }
                                    }
                                }
                                else {
                                    cout << "Recipient ID does not exist." << endl;
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Giriþi temizler
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
                cin.get(); // Bir tuþa basýlmasýný bekler
                system("cls");
                return 1;
            }
        }
    }

    sqlite3_finalize(stmt_sent);
    sqlite3_close(db);
   
 
}

