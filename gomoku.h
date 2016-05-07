#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define PLAYER_1 1
#define PLAYER_2 2

#define OKAY 5

int checkDiagonalLeft(int *boardData, int a);
int checkDiagonalRight(int *boardData, int a);
int checkHorizontal(int *boardData, int a);
int checkVertical(int *boardData, int a);
int checkWin(int *boardData, int x, int y);
void drawBoard();
int findBoardData(int *boardData, int x, int y);
void initBoard(int *boardData);
void initCurses();
int playGame();
int updateBoardData(int *boardData, int x, int y, int XorO);
