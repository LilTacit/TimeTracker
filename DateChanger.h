#pragma once
#ifndef H_DATE_CHANGER
#define H_DATE_CHANGER

#include "UiManager.h"
#include "InputProcessor.h"

/**
  * Start loop for manually change date
  */
class DateChanger
{
private:
	UiManager uiManager = UiManager();
	time_t date;

public:
	DateChanger(time_t date);

	time_t selectDateInWeek();
	time_t selectDateInMonth();
};

#endif // !H_DATE_CHANGER
