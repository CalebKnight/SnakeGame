#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include "game.h"


/* A python ML model will be using this game to play, as such we want to print info about the game state to the model*/

void printStateInfoInJson(char **board, int rows, int cols, int **tail, int **head, int direction, int **previousMoves, int snakeSize){
    int i = 0;
    int j = 0;
    int *fruit_x = (int *)malloc(sizeof(int));
    int *fruit_y = (int *)malloc(sizeof(int));
    printf("{\n");
    printf("\"board\": [");
    for(i = 0; i < rows; i++){
        printf("[");
        for(j = 0; j < cols; j++){
            printf("\"%c\"", board[i][j]);
            if(j != cols - 1){
                printf(",");
            }
        }
        printf("]");
        if(i != rows - 1){
            printf(",");
        }
    }
    printf("],\n");
    printf("\"snakeSize\": %d,\n", snakeSize);
    printf("\"rows\": %d,\n", rows);
    printf("\"cols\": %d,\n", cols);
    printf("\"head\": [%d, %d],\n", *head[0], *head[1]);
    printf("\"tail\": [%d, %d],\n", *tail[0], *tail[1]);
    printf("\"previousMoves\": [");
    for(i = 0; i < snakeSize; i++){
        printf("%d", *previousMoves[i]);
        if(i != snakeSize - 1){
            printf(",");
        }
    }
    printf("],\n");
    printf("direction: %d,\n", direction);
    FindFruit(board, rows, cols, fruit_x, fruit_y);
    printf("\"fruit\": [%d, %d]\n", *fruit_x, *fruit_y);
    free(fruit_x);
    free(fruit_y);
    printf("}\n");
}

void FindFruit(char **board, int rows, int cols, int *fruit_x, int *fruit_y)
{
    int i;
    int j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (board[i][j] == '&')
            {
                *fruit_x = j;
                *fruit_y = i;
                return;
            }
        }
    }
}
 


/*Function was utilised in testing but could be used to take the input of rows and columns instead of using them as arguments in the terminal*/
void getDimensions(int *rows, int *cols)
{
    printf("Enter the number of rows: ");
    scanf("%d", rows);
    printf("Enter the number of columns: ");
    scanf("%d", cols);
}

/*Creates a snake as #-> with the amount of - defined by the size of the snake given by snakeSize*/
void createSnake(char **board, int rows, int cols, int snakeSize)
{
    int j;
    /*Place tail*/
    board[2][1] = '#';
    for (j = 2; j < snakeSize; j++)
    {
        /*Place body*/
        board[2][j] = '-';
    }
    /*Place head*/
    board[2][j] = '>';
}

/*Initialises the co-ordinates of the head and tail of the snake as int arrays with 2 integers*/
/*Stored as [x][y] however when applying this to the board since the board is stored as [rows][cols] these values need to be flipped as [y][x] since rows are actually y and cols are x*/
void initCords(int **tail, int **head, int cols, int snakeSize)
{
    /*Allocate memory for cords*/
    tail[0] = (int *)malloc(sizeof(int));
    tail[1] = (int *)malloc(sizeof(int));
    head[0] = (int *)malloc(sizeof(int));
    head[1] = (int *)malloc(sizeof(int));
    /*Column 1 row 2*/
    *tail[0] = 1;
    *tail[1] = 2;
    /*Column is the length of the snake, row is the same as the snake is placed horizontally*/
    *head[0] = snakeSize;
    *head[1] = 2;
}

/*In order to determine where the snake has been to move the tail a queue system is created in the form of an array of integers*/
/*The array is the length of the snake and is initialised with all horizontal moves as the snake starts as horizontal*/
void initPreviousMoves(int **previousMoves, int rows, int cols, int snakeSize)
{
    int i;
    int boardSize = rows * cols;
    printf("Board size: %d\n", boardSize);
    /*Allocate memory*/
    for (i = 0; i < boardSize; i++)
    {
        previousMoves[i] = (int *)malloc(sizeof(int));
    }
    /*Set moves to horizontal right*/
    for (i = 0; i < boardSize; i++)
    {
        *previousMoves[i] = 2;
        
    }
}

/*Frees memory allocated to previousMoves*/
void freePreviousMoves(int **previousMoves, int rows, int cols)
{
    int i;
    int boardSize = rows * cols;
    for (i = 0; i < boardSize; i++)
    {
        free(previousMoves[i]);
    }
    free(previousMoves);
}

/*Frees memory allocated to head and tail*/
/*Could also be done with for loop but isn't necessary since it's always an array of size 2*/
void freeCordsMem(int **tail, int **head)
{
    free(tail[0]);
    free(tail[1]);
    free(tail);
    free(head[0]);
    free(head[1]);
    free(head);
}

/*This function was generally used while testing but displays where the current heads and tail co-ordinate is*/
void displayCords(int **tail, int **head)
{
    printf("Tail: %d, %d\n", tail[0][0], tail[1][0]);
    printf("Head: %d, %d\n", head[0][0], head[1][0]);
}

/*The main function responsible for movement of the snake across the board*/
/*Takes in board ,rows ,cols ,tail ,head ,direction ,previousMoves and the size of the snake as all this information is necessary to calculate both head and tail movement*/
int moveSnake(char **board, int rows, int cols, int **tail, int **head, int direction, int **previousMoves, int snakeSize)
{

    /*Store tail and head co-ordinates in variables for easy access to values*/
    int tail_x = *tail[0];
    int tail_y = *tail[1];
    int head_x = *head[0];
    int head_y = *head[1];
    /*Store temporary variable for the new head co-ordinate to be used later*/
    int new_head_x = head_x;
    int new_head_y = head_y;
    /*Get new head co-ordinate based on direction*/
    switch (direction)
    {
    case 1:
        new_head_y = head_y - 1;
        break;
    case 2:
        new_head_x = head_x + 1;
        break;
    case 3:
        new_head_y = head_y + 1;
        break;
    case 4:
        new_head_x = head_x - 1;
        break;
    default:
        break;
    }
    /*If the new head co-ordinate is the fruit the game ends and the user has won*/
    if (board[new_head_y][new_head_x] == '&')
    {
        shufflePreviousMovesDown(previousMoves, cols, direction, snakeSize + 1, 1);
        /*  Simply append the new head to the snake*/
        /*  Place the new head*/
        placeBodyBehindHead(board, head, direction);
        board[new_head_y][new_head_x] = getHeadDirection(direction);
        /* We don't place a new tail because we can just leave it there and move the head */
        *head[0] = new_head_x;
        *head[1] = new_head_y;
        return 2;
    }
    /*If the new head co-ordinate is the border then the user has lost or if the co-ordinate passes through the snake*/
    if (new_head_x < 1 || new_head_x >= cols - 1 || new_head_y < 1 || new_head_y >= rows - 1 || board[new_head_y][new_head_x] != ' ')
    {
        /*If the new co-ordinate is the border or is backwards don't move the snake and fire a warning message*/
        if (isBackwards(previousMoves, direction, snakeSize) == 1)
        {
            printf("You can't move backwards!\n");
            awaitingInput();
            return 1;
        }
        if (new_head_x < 1 || new_head_x >= cols - 1 || new_head_y < 1 || new_head_y >= rows - 1)
        {
            printf("Cannot escape the map\n");
            awaitingInput();
            return 0;
        }
        /*If it's not unbeatable then end the game*/
        if (UNBEATABLE != 1)
        {
            printf("Game over!\n");
            return 0;
        }
    }
    /*Make current tail empty space*/
    board[tail_y][tail_x] = ' ';
    /*Shuffle the previous moves down so that the new move can be placed at the top e.g*/
    /*[1][2][3] => [2][3][4]*/
    shufflePreviousMovesDown(previousMoves, cols, direction, snakeSize, 0);
    /*Get the new tail location based on previousMoves*/
    getNewTail(tail, board, rows, cols, previousMoves);
    /*Make the new head a >^<v based on the current direction*/
    board[new_head_y][new_head_x] = getHeadDirection(direction);
    /*Place a - or | behind the head based on the direction*/
    placeBodyBehindHead(board, head, direction);
    /*Place new tail*/
    board[*tail[1]][*tail[0]] = '#';
    /*Update cords with new values*/
    *head[0] = new_head_x;
    *head[1] = new_head_y;
    return 1;
}
/* Checks to see if the input direction is backwards and returns 1 for true and 0 for false */
int isBackwards(int **previousMoves, int direction, int snakeSize)
{
    switch (*previousMoves[snakeSize - 1])
    {
    case 1:
        if (direction == 3)
        {
            return 1;
        }
        break;
    case 2:
        if (direction == 4)
        {
            return 1;
        }
        break;
    case 3:
        if (direction == 1)
        {
            return 1;
        }
        break;
    case 4:
        if (direction == 2)
        {
            return 1;
        }
        break;
    default:
        break;
    }
    return 0;
}

/*Takes in the direction and places - or | for the body behind the head based on the direction switch defined in getInput in game.c*/
void placeBodyBehindHead(char **board, int **head, int direction)
{
    switch (direction)
    {
    case 1:
        board[*head[1]][*head[0]] = '|';
        break;
    case 2:
        board[*head[1]][*head[0]] = '-';
        break;
    case 3:
        board[*head[1]][*head[0]] = '|';
        break;
    case 4:
        board[*head[1]][*head[0]] = '-';
        break;
    default:
        break;
    }
}
/*Shuffle the previous moves down so that the new move can be placed at the top e.g */
/*[1][2][3] => [2][3][4]*/
void shufflePreviousMovesDown(int **previousMoves, int cols, int direction, int snakeSize, int isEating)
{
    int i;
    /*While less than the size of the snake shuffle down the moves*/
    for (i = 0; i < snakeSize; i++)
    {
        if (i == snakeSize - 1)
        {
            /*Once at the end add the new move to the array*/
            *previousMoves[i] = direction;
            break;
        }

        
        if(isEating != 1){
            *previousMoves[i] = *previousMoves[i + 1];
        }
        
    }
}

/*Get the new tail co-ordinate based on previousMoves*/
/*The [0] index of previousMoves is the oldest move in the queue and thus the next location that the tail should move*/
void getNewTail(int **tail, char **board, int rows, int cols, int **previousMoves)
{
    int x = *tail[0];
    int y = *tail[1];
    /*Utilise the direction stored to determine whether or not the tail co-ordinate moves up, right, down or left*/
    switch (*previousMoves[0])
    {
    case (1):
        *tail[1] = y - 1;
        break;
    case (2):
        *tail[0] = x + 1;
        break;
    case (3):
        *tail[1] = y + 1;
        break;
    case (4):
        *tail[0] = x - 1;
        break;
    };
}

/*Return a character for the head based on what direction the snake is moving ^ or < or > or v*/
char getHeadDirection(int direction)
{
    switch (direction)
    {
    case 1:
        return '^';
    case 2:
        return '>';
    case 3:
        return 'v';
    case 4:
        return '<';
    default:
        return ' ';
    }
}
