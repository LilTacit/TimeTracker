#pragma once
#ifndef H_DB_MANAGER
#define H_DB_MANAGER

#include <iostream>
#include <sqlite3.h>
#include <random>

class DbManager
{
	using Record = vector<string>;
	using Records = vector<Record>;

private:
	sqlite3* db;
	const string KEY_DB = "raunds.db";
	const int KEY_OK = 0;

	int openDb();

	//Dev
	void dev_fillVectorWithRaunds(queue<string> &query, int date, int variant);

public:
	DbManager();

	const string KEY_TABLE = "RAUNDS";

	void createTable();
	vector<vector<string>> selectValues(string sql);
	vector<vector<string>> selectValuesQuery(queue<string> sqlQuery);

	int sqliteExec(string sql);
	int sqliteExecQuery(queue<string> sqlQuery);

	//LOG
	void logAllValues();

	//Dev
	void dev_randomFillDatabase();
	int dev_rng(int fromI, int toI);
};

#endif // !H_DB_MANAGER
