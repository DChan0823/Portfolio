/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

#include "board.h"

//init board to have 0, board is blank
Board::Board() {
	/*filled = false;
	xDim = 4;
	yDim = 4;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}*/
}

//board is given dimensions, takes a pattern array and inputs into board
Board::Board(int pattern[], int dimension) {
	filled = true;
	xDim = dimension;
	yDim = dimension;

	int count = 0;
	for (int i = 0; i < xDim; i++) {
		for (int j = 0; j < yDim; j++) {
			board[i][j] = pattern[count];
			count++;
		}
	}
};

Board::Board(vector<char> pattern, int dimension) {
	filled = true;
	xDim = dimension;
	yDim = dimension;
	
	//cout << "Im here" << endl;
	//cout << board.size();

	int count = 0;
	for (int i = 0; i < xDim; i++) {
		vector<char> temp;
		for (int j = 0; j < yDim; j++) {
			//cout << pattern[count] << endl;
			temp.push_back(pattern[count]);
			count++;
			//cout << pattern[count] << endl;
		}
		board.push_back(temp);
		//userBoard.push_back(temp);
	}


	/*for (int j = 0; j < board[0].size(); j++) {
		cout << board[1][j] << " ";
	}*/

	/*for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}*/
};

Board::Board(vector<char> pattern, vector<char> userPattern, int dimension) {
	filled = true;
	xDim = dimension;
	yDim = dimension;

	//cout << "Im here" << endl;
	//cout << board.size();

	int count = 0;
	for (int i = 0; i < xDim; i++) {
		vector<char> temp;
		for (int j = 0; j < yDim; j++) {
			//cout << pattern[count] << endl;
			temp.push_back(pattern[count]);
			count++;
			//cout << pattern[count] << endl;
		}
		board.push_back(temp);
	}

	int count2 = 0;
	for (int i = 0; i < xDim; i++) {
		vector<char> temp;
		for (int j = 0; j < yDim; j++) {
			//cout << pattern[count2] << endl;
			temp.push_back(userPattern[count2]);
			count2++;
			//cout << pattern[count] << endl;
		}
		userBoard.push_back(temp);
	}

	/*for (int j = 0; j < board[0].size(); j++) {
	cout << board[1][j] << " ";
	}*/

	/*for (int i = 0; i < board.size(); i++) {
	for (int j = 0; j < board[0].size(); j++) {
	cout << board[i][j] << " ";
	}
	cout << endl;
	}*/
};

//empties the board; init board back to 0's
void Board::emptyBoard() {
	if (filled == true) {
		for (int i = 0; i < xDim; i++) {
			for (int j = 0; j < yDim; j++) {
				board[i][j] = 0;
			}
		}
	}
	else
		return;
};

//prints the board array; not entire piece
void Board::printBoard() {
	for (int i = 0; i < xDim; i++) {
		for (int j = 0; j < yDim; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
};

//prints the entire board
void Board::printEntire(char entire[]) {
	int count = 0;
	int column = 0;
	int row = 0;
	int x = 0;
	int y = 0;
	do {
		if (entire[count] == 'Z') {
			if (board[x][y] == 1)
				cout << 'X';
			else
				cout << ' ';
			x++;
			if (x < 4) {
				x = 0;
				y++;
			}
		}
		else {
			cout << entire[count];
		}
		count++;
		column++;
		if (column == 12) {
			cout << endl;
			column = 0;
			row++;
		}
	} while (row < 11);

};

void Board::printUser() {
	int count = 0;
	//int x = 0;

	for (int i = 0; i < xDim; i++) {
		for (int j = 0; j < yDim; j++) {
			if (userBoard[i][j] == 'Z' || userBoard[i][j] == '0') {
				cout << " " << " ";
			}
			else {
				cout << userBoard[i][j] << " ";
			}
		}
		cout << endl;
	}
};

//compares 2 boards together; returns true is all elements from both arrays are same, false otherwise
bool Board::compare(const Board& board1) {
	bool compare = true;
	for (int i = 0; i < board1.xDim; i++) {
		for (int j = 0; j < board1.yDim; j++) {
			if (board[i][j] != board1.board[i][j])
				compare = false;
		}
	}
	return compare;
};

bool Board::compare() {
	bool compare = true;
	for (int i = 0; i < xDim; i++) {
		for (int j = 0; j < yDim; j++) {
			if (board[i][j] != userBoard[i][j])
				compare = false;
		}
	}
	return compare;
};

int Board::missCount(const Board& board1) {
	int count = 0;
	for (int i = 0; i < board1.xDim; i++) {
		for (int j = 0; j < board1.yDim; j++) {
			if (board[i][j] != board1.board[i][j])
				count++;
		}
	}
	return count;
};

int Board::missCount() {
	int count = 0;
	for (int i = 0; i < xDim; i++) {
		for (int j = 0; j < yDim; j++) {
			if (board[i][j] != userBoard[i][j])
				count++;
		}
	}
	return count;
}

//user inputs (x, y) coordinates to fill up one spot on the board
//if filled already, the spot will become empty
void Board::fillSpot(int row, int col) {
	if (board[row][col] == 0)
		board[row][col] = 1;
	else
		board[row][col] = 0;
};

void Board::fillElement(int row, int col) {
	//cout << row << col << endl;

	if (userBoard[row][col] == '0')
		userBoard[row][col] = 'X';
	else
		userBoard[row][col] = '0';
};

//user inputs "row" as string to indicate a filled row
//row variable indicates row number
//col variables indicate start and finish on row
//if filled already, the spot will become empty
void Board::fillRow(int row, int col1, int col2) {
	for (int i = col1; i <= col2; i++) {
		if (board[row][i] == 0)
			board[row][i] = 1;
		else
			board[row][i] = 0;
	}
};

//user inputs "col" as string to indicate a filled row
//col variable indicates column number
//row variables indicate start and finish on column
//if filled already, the spot will become empty
void Board::fillCol(int col, int row1, int row2) {
	for (int i = row1; i <= row2; i++) {
		if (board[i][col] == 0)
			board[i][col] = 1;
		else
			board[i][col] = 0;
	}
};