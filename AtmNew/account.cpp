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
		int result = sqlite3_open("accounts.db", &db);
		const char* createTableQuery = "CREATE TABLE users (id INTEGER PRIMARY KEY, full_name TEXT, password TEXT);";




	}
	};