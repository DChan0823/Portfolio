#pragma once
#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <iostream>
#include<cstdlib>
#include<ctime>

class MineSweeperGame {
private:
	int x;
	int y;
	int DIMX = 6;
	int DIMY = 6;
	int MINES = 6;
	int MINE = -1;
	char COVERED = 'X';
	char UNCOVERED = ' ';
	char FLAG = 'F';
	int state[6][6];
	char display[6][6];
public:
	void init(); // initialize game states
	int countSorroundingMines(int x, int y); // helper function used by init
	void reveal(int x, int y);
	void player(); // handle player input
	void setFlag();
	void uncover();
	void print(); // print the minefield
	void cheat(); // print out the mines
	bool isWin();
	bool isLose();
	bool playNewGame();
};

#endif // !MINESWEEPER_H

