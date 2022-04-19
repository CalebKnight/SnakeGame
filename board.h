#ifndef BOARD_H
#define BOARD_H
char **initBoard(int rows, int cols);
char **createBoard(int rows, int cols);
void printBoard(char **board, int rows, int cols);
void freeBoard(char **board, int rows);
void createBorder(char **board, int rows, int cols);
void placeFood(char **board, int rows, int cols);
#endif