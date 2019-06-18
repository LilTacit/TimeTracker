#include "pch.h"
#include "DateTime.h"

/*
	Date:
*/
Date::Date(short d, short m, short y) :
	d(d), m(m), y(y)
{
}

Date::Date(time_t t)
{
	struct tm *ltm = localtime(&t);

	if (ltm != nullptr)
	{
		this->d = ltm->tm_mday;
		this->m = ltm->tm_mon + 1;
		this->y = ltm->tm_year - 100;
	}
}

/*
	Time:
*/
Time::Time(short h, short m, short s)
	: h(h), m(m), s(s)
{
}

Time::Time(time_t t)
{
	struct tm *ltm = localtime(&t);

	this->h = ltm->tm_hour;
	this->m = ltm->tm_min;
	this->s = ltm->tm_sec;
}

DateTime::DateTime(time_t t)
{
	this->rawtime = t;
	this->date = Date{ t };
	this->dtTime = Time{ t };
}

/*
	Overload operators:
*/
bool DateTime::operator==(time_t t)
{
	return (rawtime == t);
}

/*
	Getters:
*/
int DateTime::getRawTime()
{
	return rawtime;
}

/*
	Convert to string:
*/
string DateTime::getDateStr()
{
	char dot = '/';
	string s = to_string(date.d) + dot +
		to_string(date.m) + dot +
		to_string(date.y);

	return s;
}

string DateTime::getTimeStr()
{
	char dot = ':';
	string s = to_string(dtTime.h) + dot +
		to_string(dtTime.m) + dot +
		to_string(dtTime.s);

	return s;
}

string DateTime::getShortDateStr()
{
	char dot = '/';
	string s = to_string(date.d) + dot +
		to_string(date.m);

	return s;
}

string DateTime::getShortTimeStr()
{
	char dot = ':';
	string s = to_string(dtTime.h) + dot +
		to_string(dtTime.m);

	return s;
}

string DateTime::getMonthStr()
{
	struct tm *ltm = localtime(&rawtime);
	return getMonthNameByNum(ltm->tm_mon) + " " + to_string(ltm->tm_year + 1900);
}

/*
	Seconds math:
*/
Time DateTime::convertSecondsToTime(int sec)
{
	Time t = Time{};

	const int secondsInHour = 3600,
		secondsInMin = 60;
	int h, m, s,
		remainingSec = sec;

	//hour
	h = remainingSec / secondsInHour;
	remainingSec -= h * secondsInHour;

	//minute
	m = remainingSec / secondsInMin;
	remainingSec -= m * secondsInMin;

	//second
	s = remainingSec;

	//fill
	t.h = h;
	t.m = m;
	t.s = s;

	return t;
}

string DateTime::convertSecondsToTimeStr(int sec)
{
	char dot = ':';
	Time t = convertSecondsToTime(sec);

	string s = to_string(t.h) + dot + to_string(t.m) + dot + to_string(t.s);

	return s;
}

string DateTime::convertSecondsToShortTimeStr(int sec)
{
	string str = convertSecondsToTimeStr(sec);
	str.erase(str.length() - 2);

	return str;
}

string DateTime::convertSecondsToShortDateStr(int sec)
{
	time_t t = sec;
	Date d = Date(t);

	return string(to_string(d.d) + '/' + to_string(d.m));
}

int DateTime::convertRawDateToSqlFormat(int sec)
{
	time_t t = sec;
	struct tm* ltm = localtime(&t);

	int	m = ltm->tm_min,
		h = ltm->tm_hour,
		s = ltm->tm_sec;

	sec -= m * 60;
	sec -= h * 3600;
	sec -= s;

	return sec;
}

/*
	Calculations:
*/
int DateTime::getWeekDay()
{
	struct tm *ltm = localtime(&rawtime);
	return correctWeekDay(ltm->tm_wday);
}

int DateTime::getDaysInMonth(time_t day)
{
	struct tm *ltm = localtime(&day);
	int mDay = ltm->tm_mday,
		month = ltm->tm_mon,
		tmpRawTime = day;

	if (mDay < 28)
	{
		tmpRawTime += (28 - mDay) * 86400;
		mDay = 28;
	}

	while (mDay < 31)
	{
		tmpRawTime += 86400;
		time_t t = tmpRawTime;
		ltm = localtime(&t);

		if (month == ltm->tm_mon)
			mDay++;
		else
			break;
	}

	return mDay;
}

int DateTime::getDaysInMonth()
{
	return getDaysInMonth(rawtime);
}

int DateTime::getMonthDay()
{
	struct tm *ltm = localtime(&rawtime);
	int mDay = 1;
	mDay = ltm->tm_mday;
	return mDay;
}

int DateTime::getFirstWeekDayOfMonth()
{
	//CALENDAR FORMAT BUG
	struct tm *ltm = localtime(&rawtime);
	int mDay = ltm->tm_mday;
	int firstDayRaw = rawtime;

	if (mDay != 1)
		firstDayRaw -= (86400 * mDay);

	time_t t = firstDayRaw;
	ltm = localtime(&t);

	return correctWeekDay(ltm->tm_wday);
}

bool DateTime::isCurrentDay(time_t day)
{
	Date d = Date(day);
	time_t currentT = time(0);
	Date currentDate = Date(currentT);

	return (d.d == currentDate.d && d.m == currentDate.m && d.y == currentDate.y);
}

bool DateTime::isCurrentDay()
{
	return isCurrentDay(rawtime);
}

vector<int> DateTime::getRawWeekRange(time_t day)
{
	vector<int> v = vector<int>(2);
	struct tm *ltm = localtime(&day);

	v[0] = day - (86400 * correctWeekDay(ltm->tm_wday));
	v[1] = v[0] + (86400 * 6);

	return v;
}

vector<int> DateTime::getRawWeekRange()
{
	return getRawWeekRange(rawtime);
}

queue<int> DateTime::getRawWeekDates(time_t day)
{
	queue<int> q;
	struct tm *ltm = localtime(&day);

	q.push( day - (86400 * correctWeekDay(ltm->tm_wday)) );
	
	for (int i = 0; i < 6; i++)
		q.push(q.back() + 86400);

	return q;
}

queue<int> DateTime::getRawMonthDates(time_t day)
{
	queue<int> q;
	struct tm *ltm = localtime(&day);

	q.push(day - (86400 * (ltm->tm_mday - 1)));

	for (int i = 0; i < getDaysInMonth(day); i++)
		q.push(q.back() + 86400);

	return q;
}

int DateTime::getRawFirstDayOfMonth(time_t day)
{
	struct tm *ltm = localtime(&day);
	return day - (86400 * (ltm->tm_mday - 1));
}

int DateTime::getRawFirstDayOfMonth()
{
	return getRawFirstDayOfMonth(rawtime);
}

/*
	Corrects:
*/
int DateTime::correctWeekDay(int wDay)
{
	int i = wDay - 1;
	return i >= 0 ? i : 6;
}

/*
	Sub methods:
*/
string DateTime::getMonthNameByNum(int i)
{
	string month = "";

	if (i >= 0 && i < 12)
	{
		string months[12] = {
		"January", "February",
		"March", "April", "May",
		"June", "July", "August",
		"September", "October", "November",
		"December"
		};

		month = months[i];
	}

	return month;
}
