#pragma once
#ifndef H_UI_MANAGER
#define H_UI_MANAGER

#include "RaundManager.h"
#include "UserActionsContainer.h"
#include <string>

using namespace std;

/**
  * Using for out information in console or in future out in GUI
  * All outing in programm happens in this class
  */
class UiManager
{
private:
	RaundManager raundManager = RaundManager();
	UserActionsContainer actionsContainer = UserActionsContainer();

public:
	//Raunds & Graphs:
	void drawRaund(Raund raund);
	void drawExtendedRaund(Raund raund);
	void drawDayGraph(vector<Raund> &dayGraph, time_t day);
	void drawExtendedDayGraph(vector<Raund> &dayGraph, time_t day);
	void drawWeekGraph(vector<vector<Raund>> &weekGraph, time_t day);
	void drawMonthGraph(vector<Raund> &monthGraph, time_t day);

	//Common:
	void drawSpace();
	void drawBackAction();
	void drawList(vector<string> list);
		//MON, TUE, WED, THU, FRI, SAT, SUN
	string convertWeekDayNumToString(int wDay = 0);

	//By state:
	void drawActionsByState(State state);
	void drawTitleByState(State state);

	//Input:
	void drawWaitNumInput();
	void drawWaitRaundsNumHint();
	void drawWaitRaundsNumInput();
	void drawWaitDayNumInput();

	//Edit:
	void drawEditHint();
	void drawEditActions();

	//Select date:
	void drawSelectWeekDateHint();
	void drawSelectMonthDateHint();

	//Errors:
	void drawIncorrectInput();
};

#endif // !H_UI_MANAGER
