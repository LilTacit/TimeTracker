#pragma once
#ifndef H_COMMAND_CENTERD
#define H_COMMAND_CENTERD

#include "UiManager.h"
#include "DataManager.h"

class CommandCenter
{
private:
	DataManager dataManager = DataManager();

public:
	UiManager uiManager = UiManager();

	//Tracking : put start / end time of round
	void putTimePoint();
	void validateTimePoint();

	//Show graphs
	void showDayGraph(time_t day);
	vector<Raund> showAndGetDayGraph(time_t day);
	void showWeekGraph(time_t day);
	void showMonthGraph(time_t day);
		//Out day rounds with titles & descriptions
	void showExtendedDayGraph(time_t day);

	//Cycle graphs : Quick move(next or prev) graphs
	void cycleDayGraph(bool isNext);

	//Edit:
	void deleteRaund(Raund raund);
	void deleteRaund(vector<Raund>& raunds);

	//Statistic:
	//TODO: agregate data & return useful statistic

	//Dev:
	void dev_randomFillDatabase();
	void dev_clearDatabase();
};

#endif // !H_COMMAND_CENTER
