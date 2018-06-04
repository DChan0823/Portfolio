#include <iostream>
#include <cstdlib>
#include <ctime>
#include "minesweeper.h"



int main() {
	MineSweeperGame msg;
	std::cout << "Welcome to MineSweeper!" << std::endl;
	msg.init();
	bool playing = true;
	while (playing) {
		msg.print();
		msg.player();
		if (msg.isWin()) {
			std::cout << "You Win!" << std::endl;
			playing = false;
		}
		else if (msg.isLose()) {
			std::cout << "You Lose!" << std::endl;
			playing = false;
		}

		if (!playing) {
			playing = msg.playNewGame();
			if (playing) {
				msg.init();
			}
		}
	}
	std::cout << "Exiting Minesweeper!" << std::endl;
	return 0;
}

