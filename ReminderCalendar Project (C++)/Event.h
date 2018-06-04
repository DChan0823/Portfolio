#pragma once
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

enum MONTH {January, February, March, April, May, June, July, August, September, October, November, December};

class Event
{
private:
	string title;
	tm date;
	string description;
public:
	Event();
	~Event();
	Event(string title, int day, MONTH month, int year, int hour, int minutes, string descript);

	void displayEvent();
	void editTitle(string newTitle);
	void editDate(int day, MONTH month, int year, int hour, int minutes);
	void editDescript(string descript);
	string getTitle();
	string getDescription();
	tm getDate();
        bool notSimilar(Event e);
        void insert(Event e);
};

