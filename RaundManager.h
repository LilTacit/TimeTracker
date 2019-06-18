#pragma once
#ifndef H_RAUND_MANAGER
#define H_RAUND_MANAGER

#include "Raund.h"

class RaundManager
{
public:
	//Time points:
	DateTime buildEndPoint(Raund raund);

	//Convert to string:
		//Raunds:
	string getShortRaundStr(Raund raund);
	string getRaundStr(Raund raund);
	string getExtendedRaundStr(Raund raund);
		//Date:
	string getDateStr(Raund raund);
};

#endif // !H_RAUND_MANAGER
