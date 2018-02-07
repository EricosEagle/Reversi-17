/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>




/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define LENGTH 8
#define WIDTH 8
#define TRUE 1
#define FALSE 0


/*-------------------------------------------------------------------------
 Reversi-17
 -------------------------------------------------------------------------*/
 int currentRow, currentColumn;

 void welcome() // Greeting
 {
     printf("Welcome to Reversi-17!!!\n");
     printf("The winner is the first one to reach 17 disks.\n");
     printf("**********************************************\n");
 }

 void setBoard(char (*board)[LENGTH][WIDTH]) // Initializes the board
 {
     for (int i = 0; i < LENGTH; i++)
        for (int j = 0; j < WIDTH; j++)
            (*board)[i][j] = ' ';
     (*board)[3][3] = 'W';
     (*board)[4][4] = 'W';
     (*board)[3][4] = 'B';
     (*board)[4][3] = 'B';
 }

 void printBoard(char (*board)[LENGTH][WIDTH]) // Prints the board
 {
     printf(" |0|1|2|3|4|5|6|7|\n");
     for (int i = 0; i < LENGTH; i++)
     {
         printf("%d",i);
         for (int j = 0; j < WIDTH; j++)
            printf("|%c",(*board)[i][j]);
        printf("|%d\n",i);

     }
    printf(" |0|1|2|3|4|5|6|7|\n");
 }

 void printInfo(int black, int white, int counter) // Prints amount of pieces for both sides and which player's turn it is
 {
     char *player = counter % 2 == 0 ? "White":"Black";
     printf("Black disks: %d, White disks: %d\n",black,white);
     printf("Turn %d: %s player's turn.\n",counter,player);
 }

 int checkNum(char (*board)[LENGTH][WIDTH], char c) // Checks how many pieces there are of a certain color
 {
     int counter = 0;
     for (int i = 0; i < LENGTH; i++)
     {
         for (int j = 0; j < WIDTH; j++)
         {
             if ((*board)[i][j] == c)
                counter++;
         }
     }
     return counter;
 }

 void input(char (*board)[LENGTH][WIDTH], int counter) // Asks player to enter the value of the cell where they want to place their piece
 {
     int row,column;
     while(1)
     {
        printf("Please enter the indexes of the desired cell.\n");
        printf("Row index:\n");
        if (scanf("%d",&row) != 1)
        {
            printf("Error: Illegal input.\n");
            printf("Game over!\n");
            exit(1);
        }
        printf("Column index:\n");
        if (scanf("%d",&column) != 1)
        {
            printf("Error: Illegal input.\n");
            printf("Game Over!\n");
            exit(1);
        }
        if (row > 7 || row < 0 || column > 7 || column < 0)
            printf("Error: Indexes are out of bounds.\n");
        else if ((*board)[row][column] != ' ')
            printf("Error: Cell is not empty.\n");
        else
            break;
    }
    currentRow = row;
    currentColumn = column;
    (*board)[row][column] = counter % 2 == 0 ? 'W':'B';
 }

 void changeBoard(char (*board)[LENGTH][WIDTH], int counter) // Flips any of the second player's pieces that are between the first player's pieces
 {
     char border = counter % 2 == 0 ? 'W':'B';
     char toFlip = counter % 2 == 1 ? 'W':'B';
     for (int i = -1; i <= 1; i++)
     {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            if ((*board)[currentRow + i][currentColumn + j] == toFlip)
            {
                int flag = FALSE;
                int x = currentRow + i;
                int y = currentColumn + j;
                while (x <= 7 && x >= 0 && y <= 7 && y >= 0)
                {
                    if ((*board)[x][y] == border)
                    {
                        flag = TRUE;
                        break;
                    }
                    else if ((*board)[x][y] == ' ')
                        break;
                    x += i;
                    y += j;
                }
                x = currentRow + i;
                y = currentColumn + j;
                if (flag)
                {
                    while ((*board)[x][y] != border)
                    {
                        (*board)[x][y] = border;
                        x += i;
                        y += j;
                    }
                }
            }
        }
    }

 }


 void finish(int black, int white) //Prints end results
 {
     char *winner = black > white ? "Black":"White";
     printf("Black disks: %d, White disks: %d\n",black,white);
     printf("The winner is: %s player.",winner);
 }


int main()
{
    char board[LENGTH][WIDTH]; // SPACE for no disc, B for black, W for white
    char (*point)[LENGTH][WIDTH] = &board; //This pointer lets me change the board in other functions
    int turnCounter = 1;
    welcome();
    setBoard(point);
    int whiteNum = checkNum(point,'W');
    int blackNum = checkNum(point,'B');
    do {
        printBoard(point);
        printInfo(blackNum,whiteNum,turnCounter);
        input(point,turnCounter);
        changeBoard(point,turnCounter);
        turnCounter++;
        whiteNum = checkNum(point,'W');
        blackNum = checkNum(point,'B');
    } while((whiteNum < 17 && blackNum < 17) && (whiteNum != 0 && blackNum != 0));

    printBoard(point);
    finish(blackNum,whiteNum);

  return 0;
}
