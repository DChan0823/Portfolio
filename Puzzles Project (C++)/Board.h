/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   board.h
* Author: Brandon
*
* Created on January 9, 2018, 12:03 PM
*/

/*
* File: board.h
* Project 2: Modification for Dynamic Array and File Support
* Author: Derek Chan
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board {

private:

	//int board[4][4];
	vector<vector<char>> board;
	vector<vector<char>> userBoard;
	int xDim; //x dimensions
	int yDim; //y dimensions
	bool filled; //bool variable to determine if user input anything into board

public:
	Board();
	Board(int pattern[], int dimension);
	Board(vector<char> pattern, int dimension);
	Board(vector<char> pattern, vector<char> userPattern, int dimension);
	void emptyBoard();
	void printBoard();
	void printEntire(char entire[]);
	void printUser();
	bool compare(const Board& board);
	bool compare();
	int missCount(const Board& board);
	int missCount();
	void fillSpot(int row, int col);
	void fillElement(int row, int col);
	void fillRow(int row, int col1, int col2);
	void fillCol(int col, int row1, int row2);

};

#endif /* BOARD_H */