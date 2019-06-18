#pragma once
#ifndef H_RAUND
#define H_RAUND

#include "DateTime.h"

using namespace std;

/**
  @ Example:
  *
  * 1.	13:2 - 13:2     2:4:48
  * 	05/21/19
  * 
  * StartPoint - EndPoint	duration
  * startPoint.date
  *
  * @dateTime - Start time point + date
  * @End time point - build from duration and Start point
  */
struct Raund
{
	DateTime dateTime = DateTime();
	int duration = 0;
	string title = "", description = "";
};

#endif // !H_RAUND
