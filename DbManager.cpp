#include "pch.h"
#include "DbManager.h"

using Record = vector<string>;
using Records = vector<Record>;

DbManager::DbManager()
{
	createTable();
}

int print_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
	int i;
	fprintf(stderr, "%s: ", (const char*)p_data);

	for (int i = 0; i < num_fields; i++)
		printf("%s = %s\n", p_col_names[i], p_fields[i] ? p_fields[i] : "NULL");

	printf("\n");

	return 0;
}

int record_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
	Records* records = static_cast<Records*>(p_data);
	try {
		records->emplace_back(p_fields, p_fields + num_fields);
	}
	catch (...) {
		// abort select on failure, don't let exception propogate thru sqlite3 call-stack
		return 1;
	}

	return 0;
}

int DbManager::openDb()
{
	int exit = sqlite3_open(KEY_DB.c_str(), &db);
	if (exit != SQLITE_OK)
	{
		cerr << "Can't open database." << endl;
		return 1;
	}

	return KEY_OK;
}

void DbManager::createTable()
{
	string sql =	"CREATE TABLE IF NOT EXISTS " + KEY_TABLE + "("
					"start_point	INT			NOT NULL, "
					"end_point		INT			, "
					"date			INT			NOT NULL, "
					"title			TEXT		, "
					"description	TEXT		);";

	int exit = openDb();
	
	char* errMsg;
	exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);

	if (exit != SQLITE_OK)
		fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));

	sqlite3_close(db);
}

vector<vector<string>> DbManager::selectValues(string sql)
{
	vector<vector<string>> vv;
	Records records;

	if (openDb() == KEY_OK)
	{
		char *errMsg;
		int exit = sqlite3_exec(db, sql.c_str(), record_callback, &records, &errMsg);
		if (exit != SQLITE_OK)
			std::cerr << "Error in select statement " << sql << "[" << errMsg << "]\n";

		sqlite3_close(db);
	}

	for (auto& row : records)
		vv.push_back(row);

	return vv;
}

vector<vector<string>> DbManager::selectValuesQuery(queue<string> sqlQuery)
{
	vector<vector<string>> vv;
	Records records;

	if (openDb() == KEY_OK)
	{
		char *errMsg;

		while(sqlQuery.size() > 0)
		{
			char *errMsg;
			int exit = sqlite3_exec(db, sqlQuery.front().c_str(), record_callback, &records, &errMsg);
			if (exit != SQLITE_OK)
			{
				std::cerr << "Error in select statement " << sqlQuery.front() << "[" << errMsg << "]\n";
				break;
			}

			sqlQuery.pop();
		}

		sqlite3_close(db);
	}

	for (auto& row : records)
		vv.push_back(row);

	return vv;
}

//INSERT, UPDATE, DELETE
int DbManager::sqliteExec(string sql)
{
	char* errMsg;
	int exit = openDb();

	if (exit != KEY_OK)
		return 1;

	exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);

	if (exit != SQLITE_OK)
	{
		fprintf(stderr, "Sql request: %s. Error: %s\n", sql, sqlite3_errmsg(db));
		return 1;
	}

	sqlite3_close(db);

	return KEY_OK;
}

int DbManager::sqliteExecQuery(queue<string> sqlQuery)
{
	char* errMsg;
	int exit = openDb();

	if (exit != KEY_OK)
		return 1;

	while (sqlQuery.size() > 0)
	{
		exit = sqlite3_exec(db, sqlQuery.front().c_str(), NULL, 0, &errMsg);

		if (exit != SQLITE_OK)
		{
			fprintf(stderr, "Sql request: %s. Error: %s\n", sqlQuery.front(), sqlite3_errmsg(db));
			return 1;
		}

		sqlQuery.pop();
	}

	sqlite3_close(db);

	return KEY_OK;
}

/*
	LOG
*/
void DbManager::logAllValues()
{
	if (openDb() == KEY_OK)
	{
		string sql = "SELECT * FROM " + KEY_TABLE + ";";
		char *errMsg;
		int exit = sqlite3_exec(db, sql.c_str(), print_callback, NULL, &errMsg);
		if (exit != SQLITE_OK)
			std::cerr << "Error in select statement " << sql << "[" << errMsg << "]\n";
	}
}

/*
	Dev
*/
void DbManager::dev_randomFillDatabase()
{
	queue<string> query;
	queue<string> sqlQuery;

	DateTime dt = DateTime(time(0));
	int rawD = 86400,
		dCurrent = dt.convertRawDateToSqlFormat(dt.getRawFirstDayOfMonth()),
		dPrev = dt.convertRawDateToSqlFormat(dt.getRawFirstDayOfMonth(dCurrent - rawD)),
		dNext = dt.convertRawDateToSqlFormat(dt.getRawFirstDayOfMonth(dCurrent + dt.getDaysInMonth() * rawD));
		
	//fill current 
	for (int i = 0; i < dt.getDaysInMonth(dCurrent); i++)
	{
		if (dev_rng(1, 10) > 3)
			dev_fillVectorWithRaunds(query, dCurrent + rawD * i, dev_rng(1, 6) - 1);
	}

	//fill prev
	for (int i = 0; i < dt.getDaysInMonth(dPrev); i++)
	{
		if (dev_rng(1, 20) > 7)
			dev_fillVectorWithRaunds(query, dPrev + rawD * i, dev_rng(1, 6) - 1);
	}

	//fill next
	for (int i = 0; i < dt.getDaysInMonth(dNext); i++)
	{
		if (dev_rng(1, 6) > 2)
			dev_fillVectorWithRaunds(query, dNext + rawD * i, dev_rng(1, 6) - 1);
	}

	while (query.size() > 0)
	{
		sqlQuery.push("INSERT INTO " + KEY_TABLE + " VALUES(" + query.front() + ");");
		query.pop();
	}

	sqliteExecQuery(sqlQuery);
}

int DbManager::dev_rng(int fromI, int toI)
{
	int i;

	srand((int)time(NULL));
	i = (rand() % toI) + fromI;
	srand((int)time(NULL));

	if (((rand() % toI) + fromI) == i)
	{
		default_random_engine generator;
		uniform_int_distribution<int> distribution(fromI, toI);
		generator.seed(time(NULL));

		i = distribution(generator);
		generator.seed(time(NULL));

		if (distribution(generator) == i)
		{
			random_device rd;
			mt19937 mt(rd());
			uniform_real_distribution<double> dist(fromI, toI);

			i = dist(mt);
		}
	}

	return i;
}

void DbManager::dev_fillVectorWithRaunds(queue<string> &query, int date, int variant)
{
	int d = 3600;
	string dot = ", ",
			q = "'";

	vector<vector<vector<int>>> raundCombinations;
	
	vector<vector<int>> comb1 = {
		{ d * 8,				d * 9 + 60 * 9 },		//8:00 - 9:09
		{ d * 9 + 60 * 36,		d * 10 + 60 * 44 },		//9:36 - 10:44
		{ d * 12 + 60 * 12,		d * 12 + 60 * 44 }		//12:12 - 12:44
	};
	raundCombinations.push_back(comb1);

	vector<vector<int>> comb2 = {
		{ d * 10,				d * 11 },				//10:00 - 11:00
		{ d * 11 + 60 * 15,		d * 11 + 60 * 30 },		//11:15 - 11:30
		{ d * 12 + 60 * 3,		d * 14 },				//12:03 - 14:00
		{ d * 15 + 60 * 39,		d * 17 + 60 * 32 }		//15:39 - 17:32
	};
	raundCombinations.push_back(comb2);

	vector<vector<int>> comb3 = {
		{ d * 17,				d * 18 + 60 * 10 },		//17:00 - 18:10
		{ d * 18 + 60 * 50,		d * 22 + 60 * 22 }		//18:50 - 22:22
	};
	raundCombinations.push_back(comb3);

	vector<vector<int>> comb4 = {
		{ d * 7 + 60 * 30,		d * 9 + 60 * 45 },		//7:30 - 9:45
		{ d * 10 + 60 * 10,		d * 10 + 60 * 55 },		//10:10 - 10:55
		{ d * 12,				d * 13 + 60 * 10 },		//12:00 - 13:10
		{ d * 14 + 60 * 14,		d * 16 + 60 * 50 }		//14:14 - 16:50
	};
	raundCombinations.push_back(comb4);

	vector<vector<int>> comb5 = {
		{ d * 9,				d * 10 + 60 * 2 },		//9:00 - 10:02
		{ d * 10 + 60 * 20,		d * 12 },				//10:20 - 12:00
		{ d * 14 + 60 * 34,		d * 16 + 60 * 40 },		//14:34 - 16:40
		{ d * 17 + 60 * 32,		d * 18 + 60 * 3 },		//17:32 - 18:03
		{ d * 18 + 60 * 30,		d * 20 + 60 * 22 }		//18:30 - 20:22
	};
	raundCombinations.push_back(comb5);

	vector<vector<int>> comb6 = {
		{ d * 11 + 60 * 20,		d * 12 + 60 * 30 },		//11:20 - 12:30
		{ d * 12 + 60 * 48,		d * 14 + 60 * 48 },		//12:48 - 14:48
		{ d * 16 + 60 * 1,		d * 17 + 60 * 34 },		//16:01 - 17:34
		{ d * 18 + 60 * 45,		d * 21 }				//18:45 - 21:00
	};
	raundCombinations.push_back(comb6);

	//fill
	if (!(variant >= 0 && variant <= 5))
		variant == 4;

	for (vector<int> pair : raundCombinations[variant])
		query.push((to_string(pair[0]) + dot + to_string(pair[1]) + dot + to_string(date) + dot + q + q + dot + q + q));
}

void dbManagerLogAll()
{
	DbManager dbManager = DbManager();
	dbManager.logAllValues();
}
