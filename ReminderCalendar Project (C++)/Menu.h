#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <map>
//#include "HashTable.h"
#include "Event.h"

using namespace std;

typedef multimap<string, Event> mmap;
typedef pair<string, Event> mmap_pair;

class Menu
{
private:
	mmap container;
public:
	Menu(mmap newContainer);
	~Menu();
	void start();
};

