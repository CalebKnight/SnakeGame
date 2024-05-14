#ifndef SNAKE_H
#define SNAKE_H
void printStateInfoInJson(char **board, int rows, int cols, int **tail, int **head, int direction, int **previousMoves, int snakeSize);
void FindFruit(char **board, int rows, int cols, int *fruit_x, int *fruit_y);
void getDimensions(int *rows, int *cols);
void getInput(int *direction);
void createSnake(char **board, int rows, int cols, int snakeSize);
void displayCords(int **tail, int **head);
void freeCordsMem(int **tail, int **head);
void initCords(int **tail, int **head, int cols, int snakeSize);
void getNewTail(int **tail, char **board, int rows, int cols, int **previousMoves);
char getHeadDirection(int direction);
void shufflePreviousMovesDown(int **previousMoves, int cols, int direction, int snakeSize, int isEating);
void placeBodyBehindHead(char **board, int **head, int direction);
int moveSnake(char **board, int rows, int cols, int **tail, int **head, int direction, int **previousMoves, int snakeSize);
void freePreviousMoves(int **previousMoves, int rows, int cols);
void initPreviousMoves(int **previousMoves, int rows, int cols, int snakeSize);
int isBackwards(int **previousMoves, int direction, int snakeSize);
#endif
#ifdef UNBEATABLE
#define UNBEATABLE 1
#else
#define UNBEATABLE 0
#endif