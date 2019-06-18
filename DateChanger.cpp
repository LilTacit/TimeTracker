#include "pch.h"
#include "DateChanger.h"

DateChanger::DateChanger(time_t date)
	: date(date)
{
}

time_t DateChanger::selectDateInWeek()
{
	DateTime dt = DateTime(date);
	int firstDay = dt.getRawWeekRange()[0];

	InputProcessor inputProcessor = InputProcessor();

	while (true)
	{
		string input;
		
		uiManager.drawSelectWeekDateHint();
		uiManager.drawWaitDayNumInput();
		cin >> input;
		cout << endl;

		int selectInt = inputProcessor.getNumberFromString(input);

		if (selectInt >= 1 && selectInt <= 7)
		{
			firstDay += (selectInt - 1) * 86400;
			break;
		}

		uiManager.drawIncorrectInput();
	}

	return firstDay;
}

time_t DateChanger::selectDateInMonth()
{
	DateTime dt = DateTime(date);
	int firstDay = dt.getRawFirstDayOfMonth();

	InputProcessor inputProcessor = InputProcessor();

	while (true)
	{
		string input;

		uiManager.drawSelectMonthDateHint();
		uiManager.drawWaitDayNumInput();
		cin >> input;
		cout << endl;

		int selectInt = inputProcessor.getNumberFromString(input);

		if (selectInt >= 1 && selectInt <= dt.getDaysInMonth())
		{
			firstDay += (selectInt - 1) * 86400;
			break;
		}

		uiManager.drawIncorrectInput();
	}

	return firstDay;
}
