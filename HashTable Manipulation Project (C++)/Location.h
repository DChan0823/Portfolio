#ifndef LOCATION_H_INCLUDED
#define LOCATION_H_INCLUDED

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Location
{
private:
	string name;
	string address;
	double latitude;
	double longitude;

public:
	Location();
	Location(string nm, string addr, double lat, double lon);
	bool setName(string nm);
	string getName() const;
	string getAddress() const;
	double getLatitude() const;
	double getLongitude() const;
	bool operator==(const Location &right) const;
	bool operator!=(const Location &right) const;
	friend istream& operator>>(istream &is, Location &right);

};


Location::Location( )
{
	latitude=longitude=0.;
}

Location::Location(string nm, string addr, double lat, double lon)
{
	setName(nm);
	address = addr;
	latitude = lat;
	longitude = lon;
}

	bool Location::setName(string nm) // not required for the test
	{
		if (nm.length() ==0)
      		return false;
   		this->name = nm;
   		return true;
	}

	string Location::getName() const { return name; }
	string Location::getAddress() const { return address; }

	bool Location::operator==(const Location &right) const
	{
		return name==right.name && address==right.address;
	}

    bool Location::operator!=(const Location &right) const
	{
        return !(*this==right);
	}

	istream& operator>>(istream &is, Location &right)
	{
		getline(is, right.name);
		getline(is, right.address);
		is >> right.latitude >> right.longitude;
		is.ignore('\n', 10);
		return is;
	}

#endif // LOCATION_H_INCLUDED
