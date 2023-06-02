#include "account.h"
#include <iostream>
#include <string>
#include <fstream>
#include "sqlite-amalgamation-3420000/sqlite3.h"
using namespace std;


class accountscheck {
public:
	int accountcheck(void) {
		sqlite3* db;
		int rc = sqlite3_open("accounts.db", &db);
		string createTableQuery = "CREATE TABLE Users ("
			"ID INTEGER PRIMARY KEY, "
			"FULL_NAME TEXT, "
			"PASSWORD TEXT);";
		char* errMsg;
		rc = sqlite3_exec(db, createTableQuery.c_str(), 0, 0, &errMsg);





	}
	};