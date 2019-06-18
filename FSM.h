#pragma once
#ifndef H_FSM
#define H_FSM

#include "DayGraphEditor.h"
#include "DateChanger.h"
#include <string>
#include <queue>

/**
  @ Pipeline:
  1. perform @state command in CommandCenter
  2. wait user input (more often - user select command from @UserActionsContainer taken by current @state)
  3. change @state
  *
  *
  @ Input details:
  * give vector<State> to state function( ex: mainMenu() ) -> out this list -> wait select item by user )
  * more often - via changeStateByNumInput(vector<State> statements), input num = item num in statements
  *
  *
  @ MAIN MENU:
  *
  1. Put time point
  2. Cycle day graph
  3. Change view
  	3.1. week graph
  	3.2. month graph
  	3.3. cycle graphs
  4. Settings
  5. Statistic
  6. Exit
  */

class FSM
{
public:
	FSM();

private:
	time_t date;
	CommandCenter commandCenter = CommandCenter();
	UserActionsContainer actionsContainer = UserActionsContainer();
	State state = MAIN_MENU;
	deque<State> stateCache;

	const State notCacheableStates[15] = {
		PUT_TIME_POINT,
		CYCLE_DAY_GRAPH_NEXT,
		CYCLE_DAY_GRAPH_PREV,
		CYCLE_DAY_GRAPH_CLEAR,
		CYCLE_WEEK_GRAPH_NEXT,
		CYCLE_WEEK_GRAPH_PREV,
		CYCLE_WEEK_GRAPH_CLEAR,
		CYCLE_MONTH_GRAPH_NEXT,
		CYCLE_MONTH_GRAPH_PREV,
		CYCLE_MONTH_GRAPH_CLEAR,
		EDIT_RAUNDS,
		CHANGE_DATE_FROM_WEEK,
		CHANGE_DATE_FROM_MONTH,
		DEV_RANDOM_FILL_DATABASE,
		DEV_CLEAR_DATABASE
	};

	//General
		//lifetime loop
	void update();
	void activateState();

	//Change statements:
	void changeState(State s, bool isCache = true);
	void changeStateByNumInput(vector<State> statements);
	bool checkStateOnCacheable(State s);
	bool isCompareLastState(State s);

	//Change date:
	bool moveDate(int raw, bool isNext);
	bool moveDateOnDay(bool isNext);
	bool moveDateOnWeek(bool isNext);
	bool moveDateOnMonth(bool isNext);
	void clearDate();

	//Cache
	void clearCache();
};

#endif // !H_FSM
