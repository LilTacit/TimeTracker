#include "pch.h"
#include "DayGraphEditor.h"

DayGraphEditor::DayGraphEditor(time_t day) :
	date(day)
{
	run();
}

/*
	General
*/
void DayGraphEditor::run()
{
	vector<Raund> dayGraph = commandCenter.showAndGetDayGraph(date);

	commandCenter.uiManager.drawWaitRaundsNumHint();

	while (true)
	{
		string input = "";

		commandCenter.uiManager.drawWaitRaundsNumInput();
		cin >> input;
		cout << endl;

		if (input == BACK)
			break;
		else
		{
			vector<int> numbers = InputProcessor().getNumbersFromString(input);
			
			if (numbers.capacity() > 0)
			{
				bool isValidNumbers = true;

				for (int i : numbers)
				{
					if (!(i > 0 && i <= dayGraph.capacity()))
					{
						isValidNumbers = false;
						break;
					}
				}

				if (isValidNumbers)
				{
					vector<Raund> raundsForEdit;
					for (int pos : numbers)
						raundsForEdit.push_back(dayGraph[pos - 1]);

					choseEditAction(raundsForEdit);
					break;
				}
			}
		}

		commandCenter.uiManager.drawIncorrectInput();
	}
}

void DayGraphEditor::choseEditAction(vector<Raund>& raunds)
{
	InputProcessor inputProcessor = InputProcessor();

	while (true)
	{
		string input;

		commandCenter.uiManager.drawEditHint();
		commandCenter.uiManager.drawEditActions();
		commandCenter.uiManager.drawWaitNumInput();

		cin >> input;
		cout << endl;

		if (input == BACK)
		{
			run();
			break;
		}
		else
		{
			vector<int> action = inputProcessor.getNumbersFromString(input);

			if (action.capacity() > 0 && action.capacity() <= 1)
			{
				if (action[0] == 1)
				{
					deleteAction(raunds);
					break;
				}
			}
		}

		commandCenter.uiManager.drawIncorrectInput();
	}
}

/*
	Editing:
*/
void DayGraphEditor::deleteAction(vector<Raund>& raunds)
{
	if (raunds.capacity() == 1)
		commandCenter.deleteRaund(raunds[0]);
	else
		commandCenter.deleteRaund(raunds);
}
