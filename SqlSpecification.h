#pragma once
#ifndef H_SQL_SPECIFICATION
#define H_SQL_SPECIFICATION

#include<queue>

struct BreakRaund
{
	int date,
		startPoint,
		endPoint;
};

class SqlSpecification
{
public:
	//SELECT
	string selectSql(time_t t, string tableName);
	queue<string> selectSqlQuery(queue<int> dates, string tableName);
	string selectZeroEndPointSql(string tableName);

	//INSERT
	string insertSql(Raund r, string tableName);

	//UPDATE
	string updateEndPointSql(Raund r, string tableName);

	//DELETE
	string deleteSql(Raund r, string tableName);
	queue<string> deleteSqlQuery(vector<Raund>& raunds, string tableName);

	//Sub
	BreakRaund breakRaundToSqlFormat(Raund r);
};

#endif // !H_SQL_SPECIFICATION