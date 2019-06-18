#pragma once
#ifndef H_DAY_GRAPH_EDITOR
#define H_DAY_GRAPH_EDITOR

#include "CommandCenter.h"
#include "InputProcessor.h"

/**
  * Use for edit and delete raunds.
  *
  * Run loop inside FSM
  */
class DayGraphEditor
{
public:
	DayGraphEditor(time_t day);

private:
	const string BACK = "back";

	time_t date;
	CommandCenter commandCenter = CommandCenter();

	//General:
	void run();
	void choseEditAction(vector<Raund>& raunds);

	//Editing:
	void deleteAction(vector<Raund>& raunds);
};

#endif // !H_DAY_GRAPH_EDITOR
