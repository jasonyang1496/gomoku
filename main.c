#include <ncurses.h>
#include "gomoku.h"

int main() {
	do {
		initCurses();
		drawBoard();
	} while (playGame());
	endwin();

	return 0;
}
