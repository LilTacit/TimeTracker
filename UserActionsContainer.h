#pragma once
#ifndef H_USER_ACTIONS_CONTAINER
#define H_USER_ACTIONS_CONTAINER

#include <map>
#include <vector>
#include <iostream>

using namespace std;

enum State
{
	MAIN_MENU,
	MAIN_MENU_EXTENDED,
	CYCLE_DAY_GRAPH_NEXT,
	CYCLE_DAY_GRAPH_CLEAR,
	CYCLE_DAY_GRAPH_PREV,
	PUT_TIME_POINT,
	EDIT_RAUNDS,
	CHANGE_VIEW,
	SHOW_WEEK_GRAPH,
	SHOW_WEEK_GRAPH_EXTENDED,
	CYCLE_WEEK_GRAPH_NEXT,
	CYCLE_WEEK_GRAPH_CLEAR,
	CYCLE_WEEK_GRAPH_PREV,
	SHOW_MONTH_GRAPH,
	SHOW_MONTH_GRAPH_EXTENDED,
	CYCLE_MONTH_GRAPH_NEXT,
	CYCLE_MONTH_GRAPH_CLEAR,
	CYCLE_MONTH_GRAPH_PREV,
	CHANGE_DATE_FROM_WEEK,
	CHANGE_DATE_FROM_MONTH,
	QUICK_DAY_VIEW,
	SETTINGS,
	DEV_OPTIONS,
	DEV_RANDOM_FILL_DATABASE,
	DEV_CLEAR_DATABASE,
	EXIT,
	BACK
};

//STATISTIC,

class UserActionsContainer
{
public:
	const map<State, vector<State>> actionsMap = map<State, vector<State>> {
		{ MAIN_MENU,					vector<State>({PUT_TIME_POINT, CYCLE_DAY_GRAPH_NEXT, CYCLE_DAY_GRAPH_PREV, EDIT_RAUNDS, CHANGE_VIEW, SETTINGS, EXIT}) },
		{ MAIN_MENU_EXTENDED,			vector<State>({PUT_TIME_POINT, CYCLE_DAY_GRAPH_NEXT, CYCLE_DAY_GRAPH_CLEAR, CYCLE_DAY_GRAPH_PREV, EDIT_RAUNDS, CHANGE_VIEW, SETTINGS, EXIT}) },
		{ SHOW_WEEK_GRAPH,				vector<State>({CYCLE_WEEK_GRAPH_NEXT, CYCLE_WEEK_GRAPH_PREV, CHANGE_DATE_FROM_WEEK, MAIN_MENU, BACK}) },
		{ SHOW_WEEK_GRAPH_EXTENDED,		vector<State>({CYCLE_WEEK_GRAPH_NEXT, CYCLE_WEEK_GRAPH_CLEAR, CYCLE_WEEK_GRAPH_PREV, CHANGE_DATE_FROM_WEEK, MAIN_MENU}) },
		{ SHOW_MONTH_GRAPH,				vector<State>({CYCLE_MONTH_GRAPH_NEXT, CYCLE_MONTH_GRAPH_PREV, CHANGE_DATE_FROM_MONTH, MAIN_MENU, BACK}) },
		{ SHOW_MONTH_GRAPH_EXTENDED,	vector<State>({CYCLE_MONTH_GRAPH_NEXT, CYCLE_MONTH_GRAPH_CLEAR, CYCLE_MONTH_GRAPH_PREV, CHANGE_DATE_FROM_MONTH, MAIN_MENU}) },
		{ EDIT_RAUNDS,					vector<State>({BACK}) },
		{ CHANGE_VIEW,					vector<State>({SHOW_WEEK_GRAPH, SHOW_MONTH_GRAPH, BACK}) },
		{ CHANGE_DATE_FROM_WEEK,		vector<State>({MAIN_MENU}) },
		{ CHANGE_DATE_FROM_MONTH,		vector<State>({MAIN_MENU}) },
		{ QUICK_DAY_VIEW,				vector<State>({EDIT_RAUNDS, BACK}) },
		{ SETTINGS,						vector<State>({DEV_OPTIONS, BACK}) },
		{ DEV_OPTIONS,					vector<State>({DEV_RANDOM_FILL_DATABASE, DEV_CLEAR_DATABASE, BACK}) }
	};

	//{ MAIN_MENU, vector<State>({ PUT_TIME_POINT, CYCLE_DAY_GRAPH_NEXT, CYCLE_DAY_GRAPH_PREV, EDIT_RAUNDS, CHANGE_VIEW, STATISTIC, SETTINGS, EXIT }) },
	//{ MAIN_MENU_EXTENDED,			vector<State>({PUT_TIME_POINT, CYCLE_DAY_GRAPH_NEXT, CYCLE_DAY_GRAPH_CLEAR, CYCLE_DAY_GRAPH_PREV, EDIT_RAUNDS, CHANGE_VIEW, STATISTIC, SETTINGS, EXIT}) },

	const map<State, string> actionNames = map<State, string> {
		{ MAIN_MENU,					"Main menu" },
		{ MAIN_MENU_EXTENDED,			"Main menu" },
		{ CYCLE_DAY_GRAPH_NEXT,			"Next day" },
		{ CYCLE_DAY_GRAPH_CLEAR,		"Current day" },
		{ CYCLE_DAY_GRAPH_PREV,			"Prev day" },
		{ SHOW_WEEK_GRAPH,				"Week graph" },
		{ SHOW_WEEK_GRAPH_EXTENDED,		"Week graph" },
		{ CYCLE_WEEK_GRAPH_NEXT,		"Next week" },
		{ CYCLE_WEEK_GRAPH_CLEAR,		"Current week" },
		{ CYCLE_WEEK_GRAPH_PREV,		"Prev week" },
		{ SHOW_MONTH_GRAPH,				"Month graph" },
		{ SHOW_MONTH_GRAPH_EXTENDED,	"Month graph" },
		{ CYCLE_MONTH_GRAPH_NEXT,		"Next month" },
		{ CYCLE_MONTH_GRAPH_CLEAR,		"Current month" },
		{ CYCLE_MONTH_GRAPH_PREV,		"Prev month" },
		{ PUT_TIME_POINT,				"Put time point" },
		{ EDIT_RAUNDS,					"Edit" },
		{ CHANGE_VIEW,					"Change view" },
		{ CHANGE_DATE_FROM_WEEK,		"Select day" },
		{ CHANGE_DATE_FROM_MONTH,		"Select day" },
		{ SETTINGS,						"Settings" },
		{ DEV_OPTIONS,					"Dev options" },
		{ DEV_RANDOM_FILL_DATABASE,		"Random fill database" },
		{ DEV_CLEAR_DATABASE,			"Clear database" },
		{ EXIT,							"Exit" },
		{ BACK,							"Back" }
	};

	//{ STATISTIC,					"Statistic" },

	string convertStateToString(State state);
	vector<State> getActionsByState(State state);
	vector<string> getActionsNamesByState(State state);
};

#endif // !H_USER_ACTIONS_CONTAINER
