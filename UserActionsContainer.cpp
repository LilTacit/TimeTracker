#include "pch.h"
#include "UserActionsContainer.h"

string UserActionsContainer::convertStateToString(State state)
{
	string str = "";

	for (pair<State, string> pair : actionNames)
	{
		if (pair.first == state)
		{
			str = pair.second;
			break;
		}
	}

	return str;
}

vector<State> UserActionsContainer::getActionsByState(State state)
{
	vector<State> actions = vector<State>();

	map<State, vector<State>>::const_iterator it = actionsMap.find(state);
	actions = it->second;

	return actions;
}

vector<string> UserActionsContainer::getActionsNamesByState(State state)
{
	vector<string> names = vector<string>();
	vector<State> actions = getActionsByState(state);

	for (State s : actions)
		names.push_back(convertStateToString(s));

	return names;
}
