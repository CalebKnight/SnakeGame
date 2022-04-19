#ifndef SNAKE_H
#define SNAKE_H
void getDimensions(int *rows, int *cols);
void getInput(int *direction);
void createSnake(char **board, int rows, int cols, int snakeSize);
void displayCords(int **tail, int **head);
void freeCordsMem(int **tail, int **head);
void initCords(int **tail, int **head, int cols, int snakeSize);
void getNewTail(int **tail, char **board, int rows, int cols, int **previousMoves);
char getHeadDirection(int direction);
void shufflePreviousMovesDown(int **previousMoves, int cols, int direction, int snakeSize);
void placeBodyBehindHead(char **board, int **head, int direction, int **previousMoves);
int moveSnake(char **board, int rows, int cols, int **tail, int **head, int direction, int **previousMoves, int snakeSize);
void freePreviousMoves(int **previousMoves, int cols, int snakeSize);
void initPreviousMoves(int **previousMoves, int cols, int snakeSize);
int isBackwards(int **previousMoves, int direction);
#endif
#ifdef UNBEATABLE
#define UNBEATABLE 1
#else
#define UNBEATABLE 0
#endif