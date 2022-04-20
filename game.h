#ifndef GAME_H
#define GAME_H
void getInput(int *direction);
void awaitingInput();
void RunInputLoop(char **board, int rows, int cols, int snakeSize);
#endif