#pragma once
#ifndef H_DATE_TIME
#define H_DATE_TIME

#include <ctime>
#include <string>
#include <vector>
#include <queue>

/**
  @ Feutures:
  *
  * Sum / divide
  * check similar
  * delete / create / edit
  * export to database / convert from database
  * print
  */

using namespace std;

struct Date
{
	//day, month, year
	short d = (short)0,
		  m = (short)0,
		  y = (short)0;

	Date(short d = 0, short m = 0, short y = 0);
	Date(time_t t);
};

struct Time
{
	//hour, minute, second
	short h = (short)0,
		  m = (short)0,
		  s = (short)0;

	Time(short h = 0, short m = 0, short s = 0);
	Time(time_t t);
};

class DateTime
{
private:
	time_t rawtime = 0;
	Date date = Date{};
	Time dtTime = Time{};

public:
	DateTime(time_t t = 0);

	//Overload operators:
	bool operator== (time_t t);

	//Getters:
	int getRawTime();

	//Convert to string:
		//normal
	//dd/mm/yy
	string getDateStr();
	//hh:mm:ss
	string getTimeStr();
		//short
	//dd/mm
	string getShortDateStr();
	//hh:mm
	string getShortTimeStr();
	//[Month] [year], ex: "May 2019"
	string getMonthStr();

	//Seconds math:
		//return [hours], [minute], [second] amount
	Time convertSecondsToTime(int sec);
	string convertSecondsToTimeStr(int sec);
	string convertSecondsToShortTimeStr(int sec);
	string convertSecondsToShortDateStr(int sec);

	int convertRawDateToSqlFormat(int sec);

	//Calculations:
	int getWeekDay();
	int getDaysInMonth(time_t day);
	int getDaysInMonth();
	int getMonthDay();
	int getFirstWeekDayOfMonth();
	bool isCurrentDay(time_t day);
	bool isCurrentDay();
	vector<int> getRawWeekRange(time_t day);
	vector<int> getRawWeekRange();
	queue<int> getRawWeekDates(time_t day);
	queue<int> getRawMonthDates(time_t day);
	int getRawFirstDayOfMonth(time_t day);
	int getRawFirstDayOfMonth();

	//Corrects:
	int correctWeekDay(int wDay);

	//Sub methods:
	string getMonthNameByNum(int i);
};

#endif // !H_DATE_TIME
