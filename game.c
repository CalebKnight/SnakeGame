#include <stdlib.h>
#include <stdio.h>
#include "random.h"
#include "board.h"
#include "snake.h"
#include "terminal.h"
/*Takes in the direction int variable defined in main and outputs an integer based on the keyboard input for use in later functions to determine the direction of the snake.*/
void getInput(int *direction)
{
    char input;
    scanf("%c", &input);
    switch (input)
    {
    case 'w':
        *direction = 1;
        break;
    case 'd':
        *direction = 2;
        break;
    case 's':
        *direction = 3;
        break;
    case 'a':
        *direction = 4;
        break;
    default:
        *direction = 0;
        break;
    }
}
/*Because of how the board clearing works the user needs to be verified as having read the message before continuing the loop*/
/*This function is utilised to stop the program until this verification occurs*/
void awaitingInput()
{
    char input = ' ';
    while (input == ' ')
    {
        printf("Press any key to continue \n");
        scanf("%c", &input);
    }
}

/*A function that calls most functions defined in Snake.C to allow the snake to move*/
void RunInputLoop(char **board, int rows, int cols, int snakeSize)
{
    int **tail;
    int **head;
    int direction = 1;
    /*Game status is initalised here, 0 means Game Over!, 1 means continue and 2 means the player has won*/
    int status = 1;
    /*previousMoves is an array of moves the snake has done to be utilised later as a way of determining where the tail should be placed*/
    int **previousMoves = (int **)malloc(sizeof(int *) * snakeSize);
    /*Allocates memory and the initial moves to create the snake which are all horizontal right*/
    /*Moves are stored as integers representing direction as shown in the switch case in getInput*/
    initPreviousMoves(previousMoves, cols, snakeSize);
    /*Snake is created here with snakeSize */
    createSnake(board, rows, cols, snakeSize);
    /*To keep track of the co-ordinate of the head and tail these values are initialised here as arrays of 2 integers*/
    tail = (int **)malloc(sizeof(int *) * 2);
    head = (int **)malloc(sizeof(int *) * 2);
    initCords(tail, head, cols, snakeSize);
    /*Places food on board as a win condition*/
    placeFood(board, rows, cols);
    while (status == 1)
    {
        /*Clear screen so it looks like an animating board*/
        system("clear");
        /*Clear the input stream incase user has been typing characters and also to get rid of characters in dialogue for invalid input*/
        fflush(stdin);
        printBoard(board, rows, cols);
        disableBuffer();
        getInput(&direction);
        if (direction == 0)
        {
            /*Awaits verification from user before continuing to ensure they have read the error message*/
            printf("Invalid input please use WASD\n");
            awaitingInput();
        }
        else
        {
            status = moveSnake(board, rows, cols, tail, head, direction, previousMoves, snakeSize);
        }
        enableBuffer();
        /*Changing status from moveSnake will kick the program out of this loop if a loss or win occurs*/
    }
    /*Freeing memory used to track snake and the board*/
    freePreviousMoves(previousMoves, cols, snakeSize);
    freeCordsMem(tail, head);
    freeBoard(board, rows);
}