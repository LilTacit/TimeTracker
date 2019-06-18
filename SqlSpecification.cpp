#include "pch.h"
#include "SqlSpecification.h"

/*
	SELECT
*/
string SqlSpecification::selectSql(time_t t, string tableName)
{
	int date = DateTime().convertRawDateToSqlFormat(t);

	return "SELECT * FROM " + tableName + " WHERE DATE='" + to_string(date) + "';";
}

queue<string> SqlSpecification::selectSqlQuery(queue<int> dates, string tableName)
{
	DateTime dt = DateTime();
	queue<string> sqlQueue;

	while (dates.size() > 0)
	{
		sqlQueue.push("SELECT * FROM " + tableName + " WHERE DATE='" + to_string(dt.convertRawDateToSqlFormat(dates.front())) + "';");
		dates.pop();
	}

	return sqlQueue;
}

string SqlSpecification::selectZeroEndPointSql(string tableName)
{
	return "SELECT * FROM " + tableName + " WHERE end_point = 0;";
}

/*
	INSERT
*/
string SqlSpecification::insertSql(Raund r, string tableName)
{
	BreakRaund br = breakRaundToSqlFormat(r);

	string sql = "INSERT INTO " + tableName + " VALUES("
				 + to_string(br.startPoint) + ", "				//start_point
				 + to_string(br.endPoint) + ", "				//end_point
				 + to_string(br.date) + ", "					//date
				 + "'" + r.title + "'" + ", "					//title
				 + "'" + r.description + "'" + ");";			//description

	return sql;
}

/*
	UPDATE
*/
string SqlSpecification::updateEndPointSql(Raund r, string tableName)
{
	BreakRaund br = breakRaundToSqlFormat(r);

	string sql = "UPDATE " + tableName +
				 " SET end_point = " + to_string(br.endPoint) +
				 " WHERE date = " + to_string(br.date) + " AND start_point = " + to_string(br.startPoint) + ";";

	return sql;
}

/*
	DELETE
*/
string SqlSpecification::deleteSql(Raund r, string tableName)
{
	BreakRaund br = breakRaundToSqlFormat(r);

	string sql = "DELETE FROM " + tableName +
				 " WHERE date = " + to_string(br.date) +
				 " AND start_point = " + to_string(br.startPoint) + ";";

	return sql;
}

queue<string> SqlSpecification::deleteSqlQuery(vector<Raund>& raunds, string tableName)
{
	queue<string> sqlQueue;

	for (Raund r : raunds)
	{
		BreakRaund br = breakRaundToSqlFormat(r);
		sqlQueue.push("DELETE FROM " + tableName +
					  " WHERE date = " + to_string(br.date) + 
					  " AND start_point = " + to_string(br.startPoint) + ";");
	}

	return sqlQueue;
}

/*
	Sub
*/
BreakRaund SqlSpecification::breakRaundToSqlFormat(Raund r)
{
	int date = r.dateTime.convertRawDateToSqlFormat(r.dateTime.getRawTime()),
		startPoint = r.dateTime.getRawTime() - date,
		endPoint = r.duration > 0 ? startPoint + r.duration : 0;

	return BreakRaund{date, startPoint, endPoint};
}
