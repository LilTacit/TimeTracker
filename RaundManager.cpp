#include "pch.h"
#include "RaundManager.h"

/*
	Time points:
*/
DateTime RaundManager::buildEndPoint(Raund raund)
{
	int endPoint = raund.dateTime.getRawTime() + raund.duration;
	return DateTime{ endPoint };
}

/*
	Convert to string:
*/
//Raunds:
string RaundManager::getShortRaundStr(Raund raund)
{
	string s = raund.dateTime.getShortTimeStr() + " - " +
		(raund.duration > 0 ? buildEndPoint(raund).getShortTimeStr() : "...") +
		"\;     \t" +
		(raund.duration > 0 ? raund.dateTime.convertSecondsToTimeStr(raund.duration) : "");

	return s;
}

string RaundManager::getRaundStr(Raund raund)
{
	return string();
}

string RaundManager::getExtendedRaundStr(Raund raund)
{
	return string();
}

//Date:
string RaundManager::getDateStr(Raund raund)
{
	return raund.dateTime.getDateStr();
}
