#include "Event.h"


Event::Event()
{
    title = "null";
    date.tm_mday = -1;
    date.tm_mon = January;
    date.tm_year = -1;
    date.tm_hour = -1;
    date.tm_min = -1;
    description = "null";
}


Event::~Event()
{
}

Event::Event(string newTitle, int day, MONTH month, int year, int hour, int minutes, string descript) {
	title = newTitle;
	date.tm_mday = day;
	date.tm_mon = month;
	date.tm_year = year;
	date.tm_hour = hour;
	date.tm_min = minutes;
	description = descript;
}

void Event::displayEvent() {
	cout << "Event: " << title << endl;
	cout << "Date: " << MONTH(date.tm_mon) << " " << date.tm_mday << ", " << date.tm_year << endl;
	cout << "Time: " << date.tm_hour << ":" << date.tm_min << endl;
	cout << "Description: " << description << endl;
}

void Event::editTitle(string newTitle) {
	title = newTitle;
}

void Event::editDate(int day, MONTH month, int year, int hour, int minutes) {
	date.tm_mday = day;
	date.tm_mon = month;
	date.tm_year = year;
	date.tm_hour = hour;
	date.tm_min = minutes;
}

void Event::editDescript(string descript) {
	description = descript;
}

string Event::getTitle() {
	return title;
}

string Event::getDescription() {
	return description;
}

tm Event::getDate() {
	return date;
}

bool Event::notSimilar(Event e){
    if(title != e.title && description != e.description && date.tm_mon != e.getDate().tm_mon
            && date.tm_mday != e.getDate().tm_mday && date.tm_year != e.getDate().tm_year 
            && date.tm_hour != e.getDate().tm_hour && date.tm_min != e.getDate().tm_min)
        return true;
    else 
        return false;
}

void Event::insert(Event e){
    title = e.title;
    date.tm_mday = e.getDate().tm_mday;
    date.tm_mon = e.getDate().tm_mon;
    date.tm_year = e.getDate().tm_year;
    date.tm_hour = e.getDate().tm_hour;
    date.tm_min = e.getDate().tm_min;
    description = e.description;
}
