#include "pch.h"
#include "UiManager.h"

/*
	Raunds & Graphs:
*/
void UiManager::drawRaund(Raund raund)
{
	/**
	  @ Raund:
	  * @Start - @end		@Duration
	  */
	cout << raundManager.getShortRaundStr(raund) << endl;
}

void UiManager::drawExtendedRaund(Raund raund)
{
}

void UiManager::drawDayGraph(vector<Raund> &dayGraph, time_t day)
{
	//Date
	cout << raundManager.getDateStr(Raund{ DateTime(day) }) << endl;

	if (dayGraph.capacity() > 0)
	{
		int counter = 1,
			totalDuration = 0;
		char dot = '.',
			space = ' ';
		string totalDurationStr = "Total duration: ";

		//Raunds list
		cout << endl;

		for (Raund &r : dayGraph)
		{
			cout << counter << dot << space;
			drawRaund(r);

			totalDuration += r.duration;

			counter++;
		}

		//Total duration.
		cout << endl;
		cout << totalDurationStr << DateTime().convertSecondsToTimeStr(totalDuration) << endl;
	}
}

void UiManager::drawExtendedDayGraph(vector<Raund> &dayGraph, time_t day)
{
}

void UiManager::drawWeekGraph(vector<vector<Raund>> &weekGraph, time_t day)
{
	DateTime dt = DateTime(day);

	int rawTotalTime = 0,
		workDays = 0;

	struct tmpDayItem
	{
		int rawDayTime = 0,
			raundsAmount = 0;
	};

	tmpDayItem days[7];

	//Parse dayGraphs
	for (vector<Raund> dayGraph : weekGraph)
	{
		if (dayGraph.size() > 0)
		{
			int rawDayTime = 0,
				raundsAmount = 0,
				weekDay = dayGraph[0].dateTime.getWeekDay();

			for (Raund r : dayGraph)
			{
				rawDayTime += r.duration;
				raundsAmount++;
			}

			rawTotalTime += rawDayTime;
			days[weekDay] = tmpDayItem{ rawDayTime, raundsAmount };

			workDays++;
		}
		
	}

	//Draw
	vector<int> rawWeekRange = dt.getRawWeekRange();
	cout << dt.convertSecondsToShortDateStr(rawWeekRange[0]) << " - " << dt.convertSecondsToShortDateStr(rawWeekRange[1]);
	drawSpace();

	for (int i = 0; i < 7; i++)
	{
		cout << convertWeekDayNumToString(i) << "  ";

		if (days[i].rawDayTime == 0)
			cout << "-" << endl;
		else
		{
			tmpDayItem item = days[i];

			cout << dt.convertSecondsToTimeStr(item.rawDayTime) << "\t" << "(" << item.raundsAmount <<
				(item.raundsAmount > 1 ? " raunds)" : " raund)") << endl;
		}
	}

	//Total:
	cout << endl <<
		"Total: " << dt.convertSecondsToTimeStr(rawTotalTime) << endl <<
		workDays << " work " << (workDays > 1 ? "days" : "day") << endl;
}

void UiManager::drawMonthGraph(vector<Raund> &monthGraph, time_t day)
{
	DateTime dt = DateTime(day);
	int rawTotalTime = 0,
		workDays = monthGraph.capacity();

	vector<Raund> fullMonthGraph = vector<Raund>(dt.getDaysInMonth());

	for (Raund r : monthGraph)
	{
		rawTotalTime += r.duration;
		fullMonthGraph[r.dateTime.getMonthDay() - 1] = r;
	}

	//Draw date:
	cout << dt.getMonthStr() << endl;
	drawSpace();

	//Draw month:
	int wDay = dt.getFirstWeekDayOfMonth();

	for (int i = 0; i < wDay; i++)
		cout << "           ";

	for (int i = 0; i < fullMonthGraph.capacity(); i++)
	{
		Raund &r = fullMonthGraph[i];

		string str;
		str.append(to_string(i + 1));

		if (r.duration > 0)
			str.append("(" + r.dateTime.convertSecondsToShortTimeStr(r.duration) + ")");
		else
			str.append("   ");

		while (str.length() < 9)
			str.append(" ");

		cout << str << "  ";

		wDay++;
		
		if (wDay >= 7)
		{
			wDay = 0;
			drawSpace();
		}
	}

	//Total:
	drawSpace();
	drawSpace();

	cout << "Total:" << endl << endl;
	cout << "* hours:\t" << dt.convertSecondsToTimeStr(rawTotalTime) << endl;
	cout << "* work days:\t" << workDays << endl;
}

/*
	Common:
*/
void UiManager::drawSpace()
{
	cout << endl << endl;
}

void UiManager::drawBackAction()
{
	cout << "'back', for return." << endl;
}

void UiManager::drawList(vector<string> list)
{
	int i = 1;
	for (string s : list)
	{
		cout << i << ". " << s << endl;
		i++;
	}
}

string UiManager::convertWeekDayNumToString(int wDay)
{
	string str = "MON";

	switch (wDay)
	{
	case 1: str = "TUE";
		break;
	case 2: str = "WED";
		break;
	case 3: str = "THU";
		break;
	case 4: str = "FRI";
		break;
	case 5: str = "SAT";
		break;
	case 6: str = "SUN";
		break;
	default:
		break;
	}

	return str;
}

/*
	By actions:
*/
void UiManager::drawActionsByState(State state)
{
	cout << endl <<
		"____________" <<
		endl << endl;

	vector<string> actions = actionsContainer.getActionsNamesByState(state);
	drawList(actions);
}

void UiManager::drawTitleByState(State state)
{
	string title = "";

	switch (state)
	{
	case MAIN_MENU_EXTENDED:
	case CYCLE_DAY_GRAPH_NEXT:
	case CYCLE_DAY_GRAPH_PREV:
	case CYCLE_DAY_GRAPH_CLEAR:
	case PUT_TIME_POINT:
	case MAIN_MENU: title = "MAIN MENU";
		break;
	case EDIT_RAUNDS: title = "EDIT";
		break;
	case CHANGE_VIEW: title = "CHANGE VIEW";
		break;
	case QUICK_DAY_VIEW: title = "DAY";
		break;
	case CYCLE_WEEK_GRAPH_NEXT:
	case CYCLE_WEEK_GRAPH_PREV:
	case CYCLE_WEEK_GRAPH_CLEAR:
	case SHOW_WEEK_GRAPH_EXTENDED:
	case SHOW_WEEK_GRAPH: title = "WEEK GRAPH";
		break;
	case CYCLE_MONTH_GRAPH_NEXT:
	case CYCLE_MONTH_GRAPH_PREV:
	case CYCLE_MONTH_GRAPH_CLEAR:
	case SHOW_MONTH_GRAPH_EXTENDED:
	case SHOW_MONTH_GRAPH: title = "MONTH GRAPH";
		break;
	case SETTINGS: title = "SETTINGS";
		break;
	case DEV_OPTIONS: title = "DEV OPTIONS";
		break;
	case EXIT: title = "EXIT";
		break;
	default:
		break;
	}

	//case STATISTIC: title = "STATISTIC";
	//	break;

	drawSpace();
	cout << "  " << title << endl;
	cout << endl;
}

/*
	Input:
*/
void UiManager::drawWaitNumInput()
{
	cout << endl;
	cout << "Action (num): ";
}

void UiManager::drawWaitRaundsNumHint()
{
	cout << endl;
	cout << "Write raund numbers through ','" << endl;
	drawBackAction();
}

void UiManager::drawWaitRaundsNumInput()
{
	cout << endl;
	cout << "Raunds: ";
}

void UiManager::drawWaitDayNumInput()
{
	cout << endl;
	cout << "Day: ";
}

void UiManager::drawEditHint()
{
	cout << "Chose edit action." << endl;
	drawBackAction();
}

void UiManager::drawEditActions()
{
	cout << "1. Delete" << endl;
}

/*
	Select date:
*/
void UiManager::drawSelectWeekDateHint()
{
	cout << endl;
	cout << "Write day between: 1 - 7." << endl;
}

void UiManager::drawSelectMonthDateHint()
{
	cout << endl;
	cout << "Write month day number." << endl;
}

/*
	Errors:
*/
void UiManager::drawIncorrectInput()
{
	cout << "Incorrect input, try again." << endl;
}
