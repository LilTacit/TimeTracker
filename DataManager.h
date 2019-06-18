#pragma once
#ifndef H_DATA_MANAGER
#define H_DATA_MANAGER

#include "Raund.h"
#include "DbManager.h"
#include "SqlSpecification.h"
#include <vector>

class DataManager
{
private:
	DbManager dbManager = DbManager();
	SqlSpecification sqlSpecification = SqlSpecification();

	//Raw Data:
	vector<Raund> convertRawDataToRaunds(vector<vector<string>> rawData);
	//vector<vector<vector<string>>> sortRawDataToWeekGraph(vector<vector<string>> rawData);

public:
	//Manage:
	void createRaund(Raund raund);
	void deleteRaund(Raund raund);
	void deleteRaund(vector<Raund>& raunds);
	void editEndPointRaund(Raund raund);

	//Get:
	Raund getTrackedRaund();
	vector<Raund> getDayGraph(time_t day);
	vector<vector<Raund>> getWeekGraph(time_t day);
	vector<Raund> getMonthGraph(time_t day);

	//Dev:
	void dev_randomFillDatabase();
	void dev_clearDatabase();
};

#endif // !H_DATA_MANAGER
