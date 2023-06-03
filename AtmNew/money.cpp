#include <iostream>
#include "money.h"
#include "./sqlite-amalgamation-3420000/sqlite3.h"
#include <string>
#include "login.h"
#include "Logo.h"
using namespace std;
int passing_id;
signupmenu id_;


moneytra:::withdraw() {

    sqlite3* db;
    int rc = sqlite3_open("accounts.db", &db);
    sqlite3_stmt* stmt;

    int idp, withdrawv;
    string tpass, psp;

    cout << "Enter Your ID:";
    cin >> idp;
    cout << "Enter Your Password:";
    cin >> tpass;

    if (rc != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    string selectQuery = "SELECT ID, PASSWORD FROM Users WHERE ID =" + to_string(idp) + ";";
    rc = sqlite3_prepare_v2(db, selectQuery.c_str(), -1, &stmt, 0);

    if (rc == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int dbId = sqlite3_column_int(stmt, 0);
            const unsigned char* passing = sqlite3_column_text(stmt, 1);
            psp = reinterpret_cast<const char*>(passing);

            if (idp == dbId && tpass == psp) {
                cout << "Enter the value of the money you want to withdraw from your account: ";
                cin >> withdrawv;

                string balanceQuery = "SELECT BALANCE FROM Users WHERE ID =" + to_string(idp) + ";";
                rc = sqlite3_prepare_v2(db, balanceQuery.c_str(), -1, &stmt, 0);

                if (rc == SQLITE_OK) {
                    if (sqlite3_step(stmt) == SQLITE_ROW) {
                        int curbalance = sqlite3_column_int(stmt, 5);
                        if (curbalance - withdrawv < 0) {
                            cout << "Transaction Failed, Insufficient Balance" << endl;
                        }
                        else {
                            int leftbalance = curbalance - withdrawv;
                            string updateQuery = "UPDATE Users SET BALANCE = " + to_string(leftbalance) + " WHERE ID = " + to_string(idp) + ";";
                            rc = sqlite3_exec(db, updateQuery.c_str(), 0, 0, 0);
                            if (rc == SQLITE_OK) {
                                cout << "Transaction Successful! Amount Withdrawn From Your Account: " << withdrawv << endl;
                                cout << "Remaining Balance: " << leftbalance << endl;
                            }
                            else {
                                cerr << "Failed to update balance: " << sqlite3_errmsg(db) << endl;
                            }
                        }
                    }
                }
            }
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);


    }
}