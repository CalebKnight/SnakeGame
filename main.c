#include <stdio.h>
#include <stdlib.h>
#include "random.h"
#include "board.h"
#include "snake.h"
#include "terminal.h"
#include "game.h"

int main(int argc, char const *argv[])
{

    /* code */

    int rows;
    int cols;
    int snakeSize;
    char **board;

    /* If the arguments are entered incorrectly tells the user the correct syntax so they can type it in again*/
    if (argc != 4)
    {
        printf("Please enter the number of rows, columns and snake size\n");
        return 0;
    }
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    snakeSize = atoi(argv[3]);
    /*If the snake is too big to fit in the map this exits the program as it would result in an instant fail or a memory issue*/
    if (snakeSize > cols - 2)
    {
        printf("The snake size is too big\n");
        return 0;
    }
    if (snakeSize < 3)
    {
        printf("The snake size is too small\n");
        return 0;
    }
    /* It should not be possible for this to return true due to the limitations on snake size above */
    if (rows < 5 || cols < 5)
    {
        printf("The map is too small\n");
        return 0;
    }

    /*Initialise board with height of rows and width of columns*/
    board = initBoard(rows, cols);
    initRandom();
    /*This Loop calls all the functions related to generation of the snake and it's movement in a seperate file for readability in main*/
    RunInputLoop(board, rows, cols, snakeSize);
    return 0;
}
