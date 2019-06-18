#include "pch.h"
#include "CommandCenter.h"

using namespace std;

/*
	Tracking:
*/
void CommandCenter::putTimePoint()
{
	Raund trackedRaund = dataManager.getTrackedRaund();

	if (trackedRaund.duration == 0 && trackedRaund.dateTime.getRawTime() != 0)
	{
		// end
		trackedRaund.duration = time(0) - trackedRaund.dateTime.getRawTime();
		dataManager.editEndPointRaund(trackedRaund);
	}
	else
	{
		// start	
		Raund newRaund = Raund{ DateTime(time(0)) };
		dataManager.createRaund(newRaund);
	}
}

void CommandCenter::validateTimePoint()
{
	Raund trackedRaund = dataManager.getTrackedRaund();

	if (!trackedRaund.dateTime.isCurrentDay())
	{
		int rawTime = trackedRaund.dateTime.getRawTime(),
			startDay = trackedRaund.dateTime.convertRawDateToSqlFormat(rawTime);

		trackedRaund.duration = 86399 - (rawTime - startDay);
		dataManager.editEndPointRaund(trackedRaund);
	}
}

/*
	Graphs:
*/
void CommandCenter::showDayGraph(time_t day)
{
	vector<Raund> dayGraph = dataManager.getDayGraph(day);
	uiManager.drawDayGraph(dayGraph, day);
}

vector<Raund> CommandCenter::showAndGetDayGraph(time_t day)
{
	vector<Raund> dayGraph = dataManager.getDayGraph(day);
	uiManager.drawDayGraph(dayGraph, day);

	return dayGraph;
}

void CommandCenter::showWeekGraph(time_t day)
{
	vector<vector<Raund>> graph = dataManager.getWeekGraph(day);
	uiManager.drawWeekGraph(graph, day);
}

void CommandCenter::showMonthGraph(time_t day)
{
	vector<Raund> graph = dataManager.getMonthGraph(day);
	uiManager.drawMonthGraph(graph, day);
}

void CommandCenter::showExtendedDayGraph(time_t day)
{
}

/*
	Cycle graphs:
*/
void CommandCenter::cycleDayGraph(bool isNext)
{
	time_t t = time(0);

	if (isNext)
		t += 86400;
	else
		t -= 86400;

	showDayGraph(t);
}

/*
	Edit:
*/
void CommandCenter::deleteRaund(Raund raund)
{
	dataManager.deleteRaund(raund);
}

void CommandCenter::deleteRaund(vector<Raund>& raunds)
{
	dataManager.deleteRaund(raunds);
}

/*
	Dev:
*/
void CommandCenter::dev_randomFillDatabase()
{
	dev_clearDatabase();
	dataManager.dev_randomFillDatabase();
}

void CommandCenter::dev_clearDatabase()
{
	dataManager.dev_clearDatabase();
}
