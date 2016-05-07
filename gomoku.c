#include <ncurses.h>
#include "gomoku.h"

int checkDiagonalLeft(int *boardData, int a) {
	int x = 1;
	if (boardData[a] == boardData[a-8]) {
		x++;
		if (boardData[a-8] == boardData[a-16]) {
			x++;
			if (boardData[a-16] == boardData[a-24]) {
				x++;
				if (boardData[a-24] == boardData[a-32]) {
					x++;
				}
			}
		}
	}
	if (boardData[a] == boardData[a+8]) {
		x++;
		if (boardData[a+8] == boardData[a+16]) {
			x++;
			if (boardData[a+16] == boardData[a+24]) {
				x++;
				if (boardData[a+24] == boardData[a+32]) {
					x++;
				}
			}
		}
	}
	if (x == 5) { return TRUE; }

	return FALSE;
}

int checkDiagonalRight(int *boardData, int a) {
	int x = 1;
	if (boardData[a] == boardData[a-10]) {
		x++;
		if (boardData[a-10] == boardData[a-20]) {
			x++;
			if (boardData[a-20] == boardData[a-30]) {
				x++;
				if (boardData[a-30] == boardData[a-40]) {
					x++;
				}
			}
		}
	}
	if (boardData[a] == boardData[a+10]) {
		x++;
		if (boardData[a+10] == boardData[a+20]) {
			x++;
			if (boardData[a+20] == boardData[a+30]) {
				x++;
				if (boardData[a+30] == boardData[a+40]) {
					x++;
				}
			}
		}
	}
	if (x == 5) { return TRUE; }

	return FALSE;
}

int checkHorizontal(int *boardData, int a) {
	int x = 1;
	if (boardData[a] == boardData[a-1]) {
		x++;
		if (boardData[a-1] == boardData[a-2]) {
			x++;
			if (boardData[a-2] == boardData[a-3]) {
				x++;
				if (boardData[a-3] == boardData[a-4]) {
					x++;
				}
			}
		}
	}
	if (boardData[a] == boardData[a+1]) {
		x++;
		if (boardData[a+1] == boardData[a+2]) {
			x++;
			if (boardData[a+2] == boardData[a+3]) {
				x++;
				if (boardData[a+3] == boardData[a+4]) {
					x++;
				}
			}
		}
	}
	if (x == 5) { return TRUE; }

	return FALSE;
}

int checkVertical(int *boardData, int a) {
	int x = 1;
	if (boardData[a] == boardData[a-9]) {
		x++;
		if (boardData[a-9] == boardData[a-18]) {
			x++;
			if (boardData[a-18] == boardData[a-27]) {
				x++;
				if (boardData[a-27] == boardData[a-36]) {
					x++;
				}
			}
		}
	}
	if (boardData[a] == boardData[a+9]) {
		x++;
		if (boardData[a+9] == boardData[a+18]) {
			x++;
			if (boardData[a+18] == boardData[a+27]) {
				x++;
				if (boardData[a+27] == boardData[a+36]) {
					x++;
				}
			}
		}
	}
	if (x == 5) { return TRUE; }

	return FALSE;
}

int checkWin(int *boardData, int x, int y) {
	int a = findBoardData(boardData, x, y);

	if (boardData[a] == boardData[a-9] || boardData[a] == boardData[a+9]) {
		//vertical
		if (checkVertical(boardData, a)) {
			return TRUE;
		}
	} else if (boardData[a] == boardData[a-10] || boardData[a] == boardData[a+10]) {
		//diagonal left to right
		if (checkDiagonalRight(boardData, a)) {
			return TRUE;
		}
	} else if (boardData[a] == boardData[a-8] || boardData[a] == boardData[a+8]) {
		//diagonal right to left
		if (checkDiagonalLeft(boardData, a)) {
			return TRUE;
		}
	} else if (boardData[a] == boardData[a-1] || boardData[a] == boardData[a+1]) {
		//horizontal
		if (checkHorizontal(boardData, a)) {
			return TRUE;
		}
	}

	return FALSE;
}

void drawBoard() {
	for (int i = 0; i <= 18; i++) {
		mvaddch(i, 0, '|');
		mvaddch(i, 4, '|');
		mvaddch(i, 8, '|');
		mvaddch(i, 12, '|');
		mvaddch(i, 16, '|');
		mvaddch(i, 20, '|');
		mvaddch(i, 24, '|');
		mvaddch(i, 28, '|');
		mvaddch(i, 32, '|');
		mvaddch(i, 36, '|');

		if (i % 2 == 0){
			for (int h = 0; h <= 36; h++) {
				mvaddch(i, h, '-');
			}
		}
		move(1,2);
	}
	refresh();
}

int findBoardData(int *boardData, int x, int y) {
	int a = 0;
	for (int i = 1; i <= 17; i += 2) {
		for (int ii = 2; ii <= 34; ii += 4) {
			a++;
			if (y == i && x == ii) {
				return a;
			}
		}
	}

	return FALSE;
}

void initBoard(int *boardData) {
	for (int i = 0; i <= 80; i++) {
		boardData[i] = i + 2;
	}
}

void initCurses() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
}

int playGame() {
	int boardData[81];
	int playerNum = 1;
	int inputChar;
	int x = 2, y = 1;
	int didWin = 0;
	int canWeMove = 0;
	int nMoves = 0;

	initBoard(boardData);

	mvprintw(20, 0, "It is Player 1's turn to place an (X)\nPress Q to quit.");
	move(y, x);
	refresh();

	while (inputChar != 'q') {
		if (nMoves == 81) {
			mvprintw(22, 0, "Tie game");
			inputChar = getch();
			erase();
			return 3;
		}
		inputChar = getch();

		if(inputChar != ' ') {
			switch (inputChar){
				case KEY_UP:
					if (y == 3 || y == 5 || y == 7 || y == 9 || y == 11 || y == 13 || y == 15 || y == 17) {
						move(y -= 2, x);
					}
					break;
				case KEY_DOWN:
					if (y == 1 || y == 3 || y == 5 || y == 7 || y == 9 || y == 11 || y == 13 || y == 15) {
						move(y += 2, x);
					}
					break;
				case KEY_LEFT:
					if (x == 6 || x == 10 || x == 14 || x == 18 || x == 22 || x == 26 || x == 30 || x == 34) {
						move(y, x -= 4);
					}
					break;
				case KEY_RIGHT:
					if(x == 2 || x == 6 || x == 10 || x == 14 || x == 18 || x == 22 || x == 26 || x == 30) {
						move(y, x += 4);
					}
					break;
			}
		} else if (playerNum == PLAYER_1 && inputChar == ' '){
			getyx(stdscr, y, x);
			canWeMove = updateBoardData(boardData, x, y, 1);

			if (canWeMove == OKAY) {
				mvaddch(y, x, 'X');
				didWin = checkWin(boardData, x, y);

				if (didWin){
					mvprintw(22,0, "Player 1 wins!");
					mvprintw(24,0, "Press any key to play again.");
					inputChar = getch();
					erase();
					return TRUE;
				}
				nMoves += 1;

				playerNum = 2;
				mvprintw(20, 0, "It is Player 2's turn to place an (O)");
				move(y, x);

			}
		} else if (playerNum == PLAYER_2 && inputChar == ' ') {
			getyx(stdscr, y, x);
			canWeMove = updateBoardData(boardData, x, y, 0);

			if(canWeMove == OKAY) {
				mvaddch(y, x, 'O');
				didWin = checkWin(boardData, x, y);

				if(didWin){
					mvprintw(22,0, "Player 2 wins!");
					mvprintw(24,0, "Press any key to play again.");
					inputChar = getch();
					erase();
					return TRUE;
				}
				nMoves += 1;

				playerNum = 1;
				mvprintw(20, 0, "It is Player 1's turn to place an (X)");
				move(y, x);
			}
		}
		refresh();
	}
	endwin();

	return FALSE;
}

int updateBoardData(int *boardData, int x, int y, int XorO) {
	int a = 0;
	for (int i = 1; i <= 17; i += 2) {
		for (int ii = 2; ii <= 34; ii += 4) {
			a++;
			if (y == i && x == ii) {
				if (boardData[a] != 0 || boardData[a] != 1) {
					boardData[a] = XorO;
					return OKAY;
				}
			}
		}
	}

	return FALSE;
}
