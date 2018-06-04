#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <map>
#include "Event.h"
#include "Menu.h"

using namespace std;

int main() {
	//typedef multimap<string, Event> mmap;
	typedef pair<string, Event> mmap_pair;

	int thisMonth, thisDay, thisYear;

	//mmap container;

	ifstream fin;

	cout << "Welcome to REMINDER!" << endl;
	cout << "What is today's day?" << endl;
	cout << "Today's Month: ";
	cin >> thisMonth;
	cout << "\nToday's Day: ";
	cin >> thisDay;
	cout << "\nToday's Year: ";
	cin >> thisYear;

	fin.open("savedEvents.txt");

	cout << "\nTODAYS REMINDERS!" << endl;

	while (!fin.eof()) {
		string title, description;
		int hour, minute, month, day, year;

		fin >> title;
		fin >> description;
		fin >> hour;
		fin >> minute;
		fin >> month;
		fin >> day;
		fin >> year;

		if ((month == thisMonth) && (day == thisDay) && (year == thisYear)) {
			cout << title << endl << description << endl;
		}

		Event newEvent = Event(title, day, MONTH(month), year, hour, minute, description);

		container.insert(mmap_pair(title, newEvent));
	}
	
	system("pause");
	return 0;
}