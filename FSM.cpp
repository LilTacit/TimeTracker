#include "pch.h"
#include "FSM.h"

using namespace std;

FSM::FSM()
{
	date = time(0);
	stateCache.push_back(MAIN_MENU);
	update();
}

/*
	Lifetime loop:
*/
void FSM::update()
{
	commandCenter.uiManager.drawTitleByState(state);
	activateState();
	commandCenter.uiManager.drawActionsByState(state);

	vector<State> statements = actionsContainer.getActionsByState(state);
	changeStateByNumInput(statements);
	
	if (state != EXIT)
		update();
}

void FSM::activateState()
{
	switch (state)
	{
	case MAIN_MENU:
	{
		clearDate();
		clearCache();
		commandCenter.validateTimePoint();
		commandCenter.showDayGraph(date);
		break;
	}
	case MAIN_MENU_EXTENDED:
	{
		commandCenter.showDayGraph(date);
		break;
	}
	case PUT_TIME_POINT:
	{
		commandCenter.putTimePoint();
		changeState(MAIN_MENU);

		activateState();
		break;
	}
	case EDIT_RAUNDS:
	{
		DayGraphEditor dgEditor = DayGraphEditor(date);

		changeState(stateCache.back());
		activateState();
		break;
	}
	case CHANGE_VIEW:
	{
		clearDate();
		break;
	}
	case CHANGE_DATE_FROM_WEEK:
	{
		date = DateChanger(date).selectDateInWeek();

		changeState(QUICK_DAY_VIEW);
		activateState();
		break;
	}
	case CHANGE_DATE_FROM_MONTH:
	{
		date = DateChanger(date).selectDateInMonth();

		changeState(QUICK_DAY_VIEW);
		activateState();
		break;
	}
	case QUICK_DAY_VIEW:
	{
		commandCenter.showDayGraph(date);
		break;
	}
	case SHOW_WEEK_GRAPH: 
	{
		clearDate();
		commandCenter.showWeekGraph(date);
		break;
	}
	case SHOW_WEEK_GRAPH_EXTENDED:
	{
		commandCenter.showWeekGraph(date);
		break;
	}
	case SHOW_MONTH_GRAPH:
	{
		clearDate();
		commandCenter.showMonthGraph(date);
		break;
	}
	case SHOW_MONTH_GRAPH_EXTENDED:
	{
		commandCenter.showMonthGraph(date);
		break;
	}
	case CYCLE_DAY_GRAPH_NEXT:
	{
		if (!moveDateOnDay(true))
			changeState(MAIN_MENU_EXTENDED);
		else
			changeState(MAIN_MENU);

		activateState();
		break;
	}
	case CYCLE_DAY_GRAPH_PREV:
	{
		if (!moveDateOnDay(false))
			changeState(MAIN_MENU_EXTENDED);
		else
			changeState(MAIN_MENU);

		activateState();
		break;
	}
	case CYCLE_WEEK_GRAPH_NEXT:
	{
		if (!moveDateOnWeek(true))
			changeState(SHOW_WEEK_GRAPH_EXTENDED);
		else
			changeState(SHOW_WEEK_GRAPH);

		activateState();
		break;
	}
	case CYCLE_WEEK_GRAPH_PREV:
	{
		if (!moveDateOnWeek(false))
			changeState(SHOW_WEEK_GRAPH_EXTENDED);
		else
			changeState(SHOW_WEEK_GRAPH);

		activateState();
		break;
	}
	case CYCLE_MONTH_GRAPH_NEXT:
	{
		if (!moveDateOnMonth(true))
			changeState(SHOW_MONTH_GRAPH_EXTENDED);
		else
			changeState(SHOW_MONTH_GRAPH);

		activateState();
		break;
	}
	case CYCLE_MONTH_GRAPH_PREV:
	{
		if (!moveDateOnMonth(false))
			changeState(SHOW_MONTH_GRAPH_EXTENDED);
		else
			changeState(SHOW_MONTH_GRAPH);

		activateState();
		break;
	}
	case CYCLE_DAY_GRAPH_CLEAR:
	case CYCLE_WEEK_GRAPH_CLEAR:
	case CYCLE_MONTH_GRAPH_CLEAR:
	{
		clearDate();
		changeState(BACK);
		activateState();
		break;
	}
	case SETTINGS:
		break;
	case DEV_OPTIONS:
		break;
	case DEV_RANDOM_FILL_DATABASE:
	{
		commandCenter.dev_randomFillDatabase();

		clearDate();
		changeState(DEV_OPTIONS);
		activateState();
		break;
	}
	case DEV_CLEAR_DATABASE:
	{
		commandCenter.dev_clearDatabase();

		clearDate();
		changeState(DEV_OPTIONS);
		activateState();
		break;
	}
	default:
		break;
	}

	//case STATISTIC:
	//	break;
}

/*
	Change statements:
*/
void FSM::changeState(State s, bool isCache)
{
	if (s != BACK)
	{
		state = s;

		if (isCache && checkStateOnCacheable(s) && !isCompareLastState(s))
			stateCache.push_back(s);
	}
	else
	{
		stateCache.pop_back();
		state = stateCache.back();
	}
}

void FSM::changeStateByNumInput(vector<State> statements)
{
	InputProcessor inputProcessor = InputProcessor();

	while (true)
	{
		string input = "";

		commandCenter.uiManager.drawWaitNumInput();
		cin >> input;
		cout << endl;

		int convertedInt = inputProcessor.getNumberFromString(input);

		if (convertedInt >= 0)
		{
			if (convertedInt >= 1 && convertedInt <= statements.capacity())
			{
				changeState(statements[convertedInt - 1]);
				break;
			}
		}

		commandCenter.uiManager.drawIncorrectInput();
	}
}

bool FSM::checkStateOnCacheable(State s)
{
	bool is = true;

	for (State notS : notCacheableStates)
	{
		if (s == notS)
		{
			is = false;
			break;
		}
	}

	return is;
}

bool FSM::isCompareLastState(State s)
{
	return stateCache.back() == s;
}

/*
	Change date:
*/
//if date = current date - return true
bool FSM::moveDate(int sec, bool isNext)
{
	if (isNext)
		date += sec;
	else
		date -= sec;

	DateTime dt = DateTime(date);
	return dt.isCurrentDay();
}

bool FSM::moveDateOnDay(bool isNext)
{
	return moveDate(86400, isNext);
}

bool FSM::moveDateOnWeek(bool isNext)
{
	return moveDate(86400 * 7, isNext);
}

bool FSM::moveDateOnMonth(bool isNext)
{
	return moveDate(86400 * 31, isNext);
}

void FSM::clearDate()
{
	date = time(0);
}

/*
	Cache
*/
void FSM::clearCache()
{
	while (stateCache.size() > 1)
		stateCache.pop_back();
}
