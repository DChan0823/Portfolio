/******************************************************************************************
Name of Program: HW_5
Programmers Name: Derek Chan
Current Date: 3/13/2015
Computer Operating System and Compiler: Windows 7 and Visual Studio 2013
Description: Program that tests and manipulates Color data (hexidecimal number and string name)
stored inside a Hash Table of Seperate Chaining and a Hash Table of Quadratic Probing.
******************************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <crtdbg.h>
#include "HashQP.h"
#include "HashSC.h"
#include "HashTable.h"
#include "Color.h"
using namespace std;

typedef Color* PTR_COLOR;

bool openInputFile(ifstream &ifs);
int HashColorCode(const PTR_COLOR &pcolor);
int HashColorName(const PTR_COLOR &pcolor);
int compareColorNames(const PTR_COLOR &left, const PTR_COLOR &right);
int compareColorCodes(const PTR_COLOR &left, const PTR_COLOR &right);
int HashString(const string & key);
int Hash(int key);
void testHashTable(HashTable<PTR_COLOR>*hashTable, vector<PTR_COLOR> *pcolorVect);

int main()
{
	{HashTable<PTR_COLOR> *linkHash = new HashSC<PTR_COLOR>(HashColorCode, compareColorCodes, 0);
	HashTable<PTR_COLOR> *openHash = new HashQP<PTR_COLOR>(HashColorName, compareColorNames, 0);
	vector<PTR_COLOR> *vect = new vector<PTR_COLOR>();

	ifstream inFile;
	long colorCode;
	string colorName;

	//openInputFile(inFile);

	//inFile >> hex >> colorCode;
	//cout << hex << colorCode << endl;
	//inFile >> colorName;
	//cout << colorName << endl;

	if (!openInputFile(inFile))
	{
		cout << "Could not Open File" << endl;
	}
	else
	{
		while (inFile >> hex >> colorCode)
		{
			getline(inFile, colorName);

			Color* newColor = new Color(colorCode, colorName);

			//linkHash->insert(newColor);
			openHash->insert(newColor);
			vect->push_back(newColor);
		}

		//linkHash->displayStatistics();
		openHash->displayStatistics();

		//cout << "Testing HashSC (Chaining)" << endl;
		//testHashTable(linkHash, vect);
		//linkHash->makeEmpty();

		cout << endl << "Testing Hash Open Addr (Offset)\n";
		testHashTable(openHash, vect);
		openHash->makeEmpty();
	}

	inFile.close();
	delete linkHash;
	delete openHash;
	
	for (int i = 0; i < vect->size(); i++)
	{
		delete &vect[i];
	}

	cout << endl;

	}cout << (_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Leak\n");

	system("pause");
	return 0;
}

bool openInputFile(ifstream &ifs)
{
	string filename;

	cout << "Enter the input filename: ";
	getline(cin, filename);
	ifs.open(filename.c_str());
	return ifs.is_open();
}

int HashColorCode(const PTR_COLOR &pcolor)
{
	return Hash(pcolor->getColorCode());
}

int HashColorName(const PTR_COLOR &pcolor)
{
	return HashString(pcolor->getColorName());
}

int compareColorNames(const PTR_COLOR &left, const PTR_COLOR &right)
{
	if (left->getColorName() < right->getColorName())
		return -1;
	if (left->getColorName() > right->getColorName())
		return 1;
	return 0;
}

int compareColorCodes(const PTR_COLOR &left, const PTR_COLOR &right)
{
	return left->getColorCode() - right->getColorCode();
}

int HashString(const string & key) // USE THIS OR YOUR OWN
{
	unsigned int k, retVal = 0;

	for (k = 0; k < key.length(); k++)
		retVal = 37 * retVal + key[k];


	return retVal;
}

int Hash(int key) // USE THIS OR YOUR OWN
{
	return key;
}

void testHashTable(HashTable<PTR_COLOR>*hashTable, vector<PTR_COLOR> *pcolorVect)
{
	long first, last, middle;
	Color nonColor(0xFFFFFFF, "None");
	vector<PTR_COLOR> localVect;

	first = 0;
	last = pcolorVect->size() - 1;
	middle = last / 2;
	localVect.push_back(pcolorVect->at(first));
	localVect.push_back(pcolorVect->at(last));
	localVect.push_back(pcolorVect->at(middle));
	localVect.push_back(&nonColor);
	for (int i = 0; i < localVect.size(); ++i)
	{
		if (hashTable->contains(localVect[i]))
			cout << "Found " << hex << localVect[i]->getColorCode()
			<< ": " << localVect[i]->getColorName() << endl;
		else
			cout << "Didn't find " << hex << localVect[i]->getColorCode()
			<< ": " << localVect[i]->getColorName() << endl;
	} // end for
	for (int i = 0; i < localVect.size(); ++i)
	{
		if (hashTable->remove(localVect[i]))
			cout << "Removed " << hex << localVect[i]->getColorCode()
			<< ": " << localVect[i]->getColorName() << endl;
		else
			cout << "Couldn't remove " << hex << localVect[i]->getColorCode()
			<< ": " << localVect[i]->getColorName() << endl;
	} // end for
	Color *pfoundColor;
	for (int i = 0; i < localVect.size(); ++i)
	{
		if (hashTable->getEntry(localVect[i], pfoundColor))
			cout << "Found (wasn't removed) " << hex << pfoundColor->getColorCode()
			<< ": " << pfoundColor->getColorName() << endl;
		else
			cout << "Didn't find (was removed) " << hex << localVect[i]->getColorCode()
			<< ": " << localVect[i]->getColorName() << endl;
	} // end for

	// test one that still should be there:
	if (hashTable->getEntry(pcolorVect->at(1), pfoundColor))
		cout << "Found (wasn't removed) " << hex << pfoundColor->getColorCode()
		<< ": " << pfoundColor->getColorName() << endl;
	else
		cout << "Didn't find (was removed) " << hex << pcolorVect->at(1)->getColorCode()
		<< ": " << pcolorVect->at(1)->getColorName() << endl;

}

/********************************************************************
OUTPUT:
Enter the input filename: HW5 Test Input1.txt


In the Hash SC class:
Load factor = 0.185567
Number of collisions = 3
Longest Linked List = 2



In the Hash Offset class:
Load factor = 0.185567
Number of collisions = 18
Longest Collision Path = 0

Testing HashSC (Chaining)
Found ff0000:  Red
Found 808000:  Olive
Found ff00ff:  Magenta
Didn't find fffffff: None
Removed ff0000:  Red
Removed 808000:  Olive
Removed ff00ff:  Magenta
Couldn't remove fffffff: None
Didn't find (was removed) ff0000:  Red
Didn't find (was removed) 808000:  Olive
Didn't find (was removed) ff00ff:  Magenta
Didn't find (was removed) fffffff: None
Found (wasn't removed) ffff:  Cyan

Testing Hash Open Addr (Offset)
Found ff0000:  Red
Found 808000:  Olive
Found ff00ff:  Magenta
Didn't find fffffff: None
Removed ff0000:  Red
Removed 808000:  Olive
Removed ff00ff:  Magenta
Couldn't remove fffffff: None
Didn't find (was removed) ff0000:  Red
Didn't find (was removed) 808000:  Olive
Didn't find (was removed) ff00ff:  Magenta
Didn't find (was removed) fffffff: None
Found (wasn't removed) ffff:  Cyan

No Leak
Press any key to continue . . .
********************************************************************/