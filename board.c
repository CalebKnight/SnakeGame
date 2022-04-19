#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "random.h"

/*Creates an empty board as an array of chars*/
char **createBoard(int rows, int cols)
{
    /*Initialise the char array in memory*/
    char **board = (char **)malloc(rows * sizeof(char *));
    int i;
    for (i = 0; i < rows; i++)
    {
        board[i] = (char *)malloc(cols * sizeof(char));
    }

    /*Initialise the board to all ' '*/
    for (i = 0; i < rows; i++)
    {
        int j = 0;
        for (j = 0; j < cols; j++)
        {
            board[i][j] = ' ';
        }
    }

    return board;
}

/*Displays the board*/
void printBoard(char **board, int rows, int cols)
{
    int i;
    int j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

/*Frees any memory dedicated to the board*/
void freeBoard(char **board, int rows)
{
    int i = 0;
    for (i = 0; i < rows; i++)
    {
        free(board[i]);
    }
    free(board);
}

/*Takes in the board and creates a border of - and | for the outline*/
void createBorder(char **board, int rows, int cols)
{
    int i;
    int j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            /*Top*/
            if (i == 0)
            {
                board[i][j] = '*';
            }
            /*Bottom*/
            else if (i == rows - 1)
            {
                board[i][j] = '*';
            }
            /*Left*/
            else if (j == 0)
            {
                board[i][j] = '*';
            }
            /*Right*/
            else if (j == cols - 1)
            {
                board[i][j] = '*';
            }
        }
    }
}
/*Places a food in a random position inside of the playable area using the random function*/
void placeFood(char **board, int rows, int cols)
{
    /*rows - 2 and cols - 2 ensure that food is placed in the playable area*/
    int i = random(1, rows - 2);
    int j = random(1, cols - 2);
    /*Make sure it isn't placed where the snake is*/
    if (board[i][j] == ' ')
    {
        board[i][j] = '&';
    }
    else
    {
        /*Call the function again if the position is incorrect to try placing food again*/
        placeFood(board, rows, cols);
    }
}
/*Wrapper function for the creation of the board*/
/*Returns the board*/
char **initBoard(int rows, int cols)
{
    char **board = createBoard(rows, cols);
    createBorder(board, rows, cols);
    return board;
}