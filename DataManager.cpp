#include "pch.h"
#include "DataManager.h"

#include <deque>
#include <queue>

/*
	Raw Data:
*/
vector<Raund> DataManager::convertRawDataToRaunds(vector<vector<string>> rawData)
{
	vector<Raund> raunds;

	for (vector<string> row : rawData)
	{
		DateTime dt = DateTime(0);
		int duration = stoi(row[1]) - stoi(row[0]);
		duration = duration < 0 ? 0 : duration;
		int date = stoi(row[2]);

		raunds.push_back(Raund{ DateTime(date + stoi(row[0])), duration, row[3], row[4] });
	}

	return raunds;
}

/*
	Manage:
*/
void DataManager::createRaund(Raund raund)
{
	string sql = sqlSpecification.insertSql(raund, dbManager.KEY_TABLE);
	dbManager.sqliteExec(sql);
}

void DataManager::deleteRaund(Raund raund)
{
	string sql = sqlSpecification.deleteSql(raund, dbManager.KEY_TABLE);
	dbManager.sqliteExec(sql);
}

void DataManager::deleteRaund(vector<Raund>& raunds)
{
	queue<string> sqlQuery = sqlSpecification.deleteSqlQuery(raunds, dbManager.KEY_TABLE);
	dbManager.sqliteExecQuery(sqlQuery);
}

void DataManager::editEndPointRaund(Raund raund)
{
	string sql = sqlSpecification.updateEndPointSql(raund, dbManager.KEY_TABLE);
	dbManager.sqliteExec(sql);
}

/*
	Get:
*/
Raund DataManager::getTrackedRaund()
{
	string sql = sqlSpecification.selectZeroEndPointSql(dbManager.KEY_TABLE);
	vector<vector<string>> rawData = dbManager.selectValues(sql);

	vector<Raund> dayGraph = vector<Raund>();
	dayGraph = convertRawDataToRaunds(rawData);

	if (dayGraph.capacity() > 0)
		return dayGraph[0];

	return Raund{};
}

vector<Raund> DataManager::getDayGraph(time_t day)
{
	vector<Raund> dayGraph = vector<Raund>();

	string sql = sqlSpecification.selectSql(day, dbManager.KEY_TABLE);
	vector<vector<string>> rawData = dbManager.selectValues(sql);

	dayGraph = convertRawDataToRaunds(rawData);

	return dayGraph;
}

vector<vector<Raund>> DataManager::getWeekGraph(time_t day)
{
	queue<int> rawWeekDates = DateTime().getRawWeekDates(day);
	queue<string> sqlQuery = sqlSpecification.selectSqlQuery(rawWeekDates, dbManager.KEY_TABLE);
	vector<vector<Raund>> weekGraph;

	vector<vector<vector<string>>> rawWeekGraph;

	while (sqlQuery.size() > 0)
	{
		vector<vector<string>> rawData = dbManager.selectValues(sqlQuery.front());
		rawWeekGraph.push_back(rawData);
		sqlQuery.pop();
	}

	for (vector<vector<string>> vv : rawWeekGraph)
		weekGraph.push_back(convertRawDataToRaunds(vv));

	return weekGraph;
}

vector<Raund> DataManager::getMonthGraph(time_t day)
{
	queue<int> rawMonthDates = DateTime().getRawMonthDates(day);
	queue<string> sqlQuery = sqlSpecification.selectSqlQuery(rawMonthDates, dbManager.KEY_TABLE);
	vector<vector<Raund>> fullMonthGraph;
	vector<Raund> monthGraph;
	vector<vector<vector<string>>> rawMonthGraph;

	while (sqlQuery.size() > 0)
	{
		vector<vector<string>> rawData = dbManager.selectValues(sqlQuery.front());
		rawMonthGraph.push_back(rawData);
		sqlQuery.pop();
	}

	for (vector<vector<string>> vv : rawMonthGraph)
		fullMonthGraph.push_back(convertRawDataToRaunds(vv));

	for (vector<Raund> &dayGraph : fullMonthGraph)
	{
		if (dayGraph.capacity() > 0)
		{
			int duration = 0;

			for (Raund &r : dayGraph)
				duration += r.duration;

			Raund day = Raund{ DateTime(dayGraph[0].dateTime.getRawTime()), duration };
			monthGraph.push_back(day);
		}
	}

	return monthGraph;
}

/*
	Dev:
*/
void DataManager::dev_randomFillDatabase()
{
	dbManager.dev_randomFillDatabase();
}

void DataManager::dev_clearDatabase()
{
	dbManager.sqliteExec("DROP TABLE " + dbManager.KEY_TABLE + ";");
	dbManager.createTable();
}
