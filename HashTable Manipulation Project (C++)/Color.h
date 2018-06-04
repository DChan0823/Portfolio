#pragma once
#include <string>
using namespace std;

class Color
{
private:
	long colorCode;
	string colorName;
public:

	Color()
	{
		colorCode = 0;
		colorName = "";
	}

	Color(long code, string name)
	{
		setColorCode(code);
		setColorName(name);
	}

	~Color()
	{
	}

	void setColorCode(long c)
	{
		if (c >= 0)
			colorCode = c;
		else
			colorCode = 0;
	}

	void setColorName(string n)
	{
		if (n.length() >= 0)
			colorName = n;
		else
			colorName = "";
	}

	long getColorCode() const
	{
		return colorCode;
	}

	string getColorName() const
	{
		return colorName;
	}

	ostream& write(ostream& out)
	{
		out << hex << getColorCode() << " " << getColorName() << endl;

		return out;
	}
};

