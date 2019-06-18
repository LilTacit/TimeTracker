#include "pch.h"
#include "InputProcessor.h"

vector<int> InputProcessor::getNumbersFromString(string str)
{
	vector<int> numbers;
	vector<string> numberStrings;

	bool isNumber = false;

	for (char c : str)
	{
		if (isdigit(c))
		{
			if (!isNumber)
			{
				numberStrings.push_back(string() + c);
				isNumber = true;
			}
			else
				numberStrings[numberStrings.capacity() - 1] += c;
		}
		else
			isNumber = false;
	}

	for (string s : numberStrings)
		numbers.push_back(stoi(s));

	return numbers;
}

int InputProcessor::getNumberFromString(string str)
{
	bool is = true;
	int i = -1;

	for (char c : str)
	{
		if (!isdigit(c))
		{
			is = false;
			break;
		}
	}

	if (is)
		i = stoi(str);

	return i;
}
