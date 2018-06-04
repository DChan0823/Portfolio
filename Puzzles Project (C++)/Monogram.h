#pragma once

#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "board.h"

class Monogram
{
private:
	//Board board;
	//Board userBoard;

	//whole board; Z represents the pattern needed from the pattern array
	/*char entire[300] = { ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', '1', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', '3', ' ', '1', ' ', '1', ' ', '3', ' ',
		' ', ' ', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-',
		' ', ' ', '2', '|', 'Z', '|', 'Z', '|', 'Z', '|', 'Z', '|',
		' ', ' ', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-',
		'1', ' ', '1', '|', 'Z', '|', 'Z', '|', 'Z', '|', 'Z', '|',
		' ', ' ', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-',
		' ', ' ', '4', '|', 'Z', '|', 'Z', '|', 'Z', '|', 'Z', '|',
		' ', ' ', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-',
		'1', ' ', '1', '|', 'Z', '|', 'Z', '|', 'Z', '|', 'Z', '|',
		' ', ' ', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-' };*/
public:
	Monogram();
	~Monogram();
	void startGame();
	vector<string> tokenize(string str, char c);
};

