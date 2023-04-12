#include<stdio.h> // manipulation des flux de caractères
#include <ctype.h> //propose un ensemble de fonction de traitement de caractères
#include <time.h> //permettant la représentation d'informations temporelles sous différents formats.
#include<string.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef _WIN32
    #define OS "nt"
#elif __unix__
    #define OS "posix"
#endif
#define TRUE 1
#define FALSE 0

char boards[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

void board(char x, char o, unsigned char *u1, unsigned char *u2, char *a); // 2D Graphics on CLI
void rules(); // Prints rule page on CLI
int checkforwin(char *a); // Checks wether a player won
bool decision(char *x, char *o, unsigned char *u1); // points player to mark X or mark 0
int main()
{
    char winner = ' ';
    char response = ' ';
    FILE *p;
    char x,o;
    p=fopen("score.txt","a+");
    fclose(p);
    char a[9]={'1','2','3','4','5','6','7','8','9'};
    char u1[50],u2[50];
    int player=1;
    int choice,score=-1;
    char symbol,re;
    char start,dec;
    int s;
    if (OS=="nt")
        system("color 09");
    rules();
    printf("\n\nType 1 to start the game between two people:-\nType 2 to start the game with computer:-\nType 3 to view leader board:-\n");
    scanf("%d",&s);
    switch(s) {
        case 1:
            do {
                p=fopen("score.txt", "a+");
                printf("\nEnter name of player1: ");
                scanf("%s",u1);
                fprintf(p,"\n%s",u1);
                printf("Enter name of player2: ");
                scanf("%s",u2);
                fprintf(p,"\t%s",u2);
                fclose(p);
                !strcmp(u1,u2) ? printf("Enter names of different players!\n\n") : FALSE;
            } while(!strcmp(u1,u2));
            decision(&x, &o, u1);
            if (OS=="nt")
                system("color fc");
            board(x,o, u1, u2, a);
            do {
                player=((player%2)?1:2);
                if(player==1)
                    printf("%s Type any digit from 1-9 to fill your response:- ",u1);
                else
                    printf("%s Type any digit from 1-9 to fill your response:- ",u2);
                scanf("%d",&choice);
                symbol=((player==1)?x:o);
                if(choice==1 && a[0]=='1')
                    a[0]=symbol;
                else if(choice==2 && a[1]=='2')
                    a[1]=symbol;
                else if(choice==3 && a[2]=='3')
                    a[2]=symbol;
                else if(choice==4 && a[3]=='4')
                    a[3]=symbol;
                else if(choice==5 && a[4]=='5')
                    a[4]=symbol;
                else if(choice==6 && a[5]=='6')
                    a[5]=symbol;
                else if(choice==7 && a[6]=='7')
                    a[6]=symbol;
                else if(choice==8 && a[7]=='8')
                    a[7]=symbol;
                else if(choice==9 && a[8]=='9')
                    a[8]=symbol;
                else {
                        printf("Wrong Selection\n");
                        player--;
                }
                score=checkforwin(a);
                player++;
                board(x, o, u1, u2, a);
            } while(score == -1);
            p=fopen("score.txt","a+");
            if(score==1) {
                if(player==2){
                    printf("\n\nPlayer1 %s Wins!\n\n",u1);
                    fprintf(p,"\t%s",u1);
                    getchar();
                    printf("*Thanks for playing!*\n");
                }
                else {
                    printf("\n\nPlayer2 %s Wins!\n\n",u2);fprintf(p,"\t%s",u2);
                    getchar();
                    printf("*Thanks for playing!*\n");
                }
                fclose(p);
            }
            else {
                printf("\n\nGame Draws!\n\n");fprintf(p,"\t%s","DRAW");
                getchar();
                printf("*Thanks for playing!*\n");

            }break;


        case 2:
            do
             {
               winner = ' ';
               response = ' ';
               resetBoard();

               while(winner == ' ' && checkFreeSpaces() != 0)
               {
                printBoard();

                playerMove();
                winner = checkWinner();
                if(winner != ' ' || checkFreeSpaces() == 0)
                {
                break;
                }

                computerMove();
                winner = checkWinner();
                if(winner != ' ' || checkFreeSpaces() == 0)
                {
                 break;
                 }
                }

                 printBoard();
                 printWinner(winner);

                 printf("\nWould you like to play again? (Y/N): ");
                 scanf("%c");
                 scanf("%c", &response);
                 response = toupper(response);
                 } while (response == 'Y');

                printf("Thanks for playing!");break;


        case 3:
            if (OS=="nt")
                system("cls");
            if (OS=="posix")
                system("clear");
            printf("\n\n");
            printf("\tLEADERBOARD\n\n");
            char c;
            p=fopen("score.txt","r");
            while((c=getc(p))!=EOF) {
                printf("%c",c);
            }
            fclose(p);
            getchar();
            break;



        default:
            printf("\n\nShould have typed 1 to play the game!\nHope to see you back soon!\n\n");
            getchar();
            break;
    }
}
int checkforwin(char *a)
{
    if(a[0]==a[1] && a[1]==a[2])
        return 1;
    else if(a[3]==a[4] && a[4]==a[5])
        return 1;
    else if(a[6]==a[7] && a[7]==a[8])
        return 1;
    else if(a[0]==a[3] && a[3]==a[6])
        return 1;
    else if(a[1]==a[4] && a[4]==a[7])
        return 1;
    else if(a[2]==a[5] && a[5]==a[8])
        return 1;
    else if(a[0]==a[4] && a[4]==a[8])
        return 1;
    else if(a[2]==a[4] && a[4]==a[6])
        return 1;
    else if(a[0]!='1' && a[1]!='2' && a[2]!='3' && a[3]!='4' && a[4]!='5' && a[5]!='6' && a[6]!='7' && a[7]!='8' && a[8]!='9')
        return 0;
    else
        return -1;
}

void board(char x, char o, unsigned char *u1, unsigned char *u2, char *a)
{
    int i;
    if (OS=="nt")
        system("cls");
    if (OS=="posix")
        system("clear");
    printf("\tTic-Tac-Toe\n\n");
        printf("\n\n");
        printf("%s:- (%c)\n%s:-  (%c)\n\n\n",u1,x,u2,o);

        printf("  %c |  %c | %c\n",a[0],a[1],a[2]);
        printf("    |    |    \n");
        printf("----|----|----\n");
        printf("    |    |    \n");
        printf("  %c |  %c | %c\n",a[3],a[4],a[5]);
        printf("    |    |    \n");
        printf("----|----|----\n");
        printf("  %c |  %c | %c\n",a[6],a[7],a[8]);
        printf("    |    |    \n");
    }
void rules()
{
    char link;
    printf("\n\t\t\t\t\t\tTic-Tac-Toe\n\n");
    printf("Welcome to the most played 2D game and a sort of fun using X and O\n\n");
    printf("Rules:-\n");
    printf("\n1:Each player will be entering the number to put respective X or O in the desired position");
    printf("\n2:Player who gets a combination of 3 same characters either diagonal or horizontally or \n  vertically will be declared as the winner");
    printf("\n\n---------------------------------------------Enjoy The Game! Be a Winner!-----------------------------------------------\n\n");
    printf("For more clarifications press Y else type any other character:- ");
    scanf("%c",&link);
    if(link=='y' || link=='Y')
    {
        if (OS=="nt")
            system("start http://www.wikihow.com/Play-Tic-Tac-Toe");
        if (OS=="posix")
            system("firefox http://www.wikihow.com/Play-Tic-Tac-Toe");
    }

}
bool decision(char *x, char *o, unsigned char *u1)
{
    char dec;
    printf("\n\n");
    do {
        printf("Player1 %s choose the X or 0:",u1);
        dec=getchar();
        scanf("%c", &dec);
    } while(dec!='X' && dec!='x' && dec!='0');
    if (dec=='X' || dec=='x') {
        *x='X';
        *o='0';
    }
    else {
        *x='0';
        *o='X';
    }
    return 1;
}

///////// user with computer

void resetBoard()
{
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         boards[i][j] = ' ';
      }
   }
}
void printBoard()
{
   printf(" %c | %c | %c ", boards[0][0], boards[0][1], boards[0][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", boards[1][0], boards[1][1], boards[1][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", boards[2][0], boards[2][1], boards[2][2]);
   printf("\n");
}
int checkFreeSpaces()
{
   int freeSpaces = 9;

   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         if(boards[i][j] != ' ')
         {
            freeSpaces--;
         }
      }
   }
   return freeSpaces;
}
void playerMove()
{
   int x;
   int y;

   do
   {
      printf("Enter row #(1-3): ");
      scanf("%d", &x);
      x--;
      printf("Enter column #(1-3): ");
      scanf("%d", &y);
      y--;

      if(boards[x][y] != ' ')
      {
         printf("Invalid move!\n");
      }
      else
      {
         boards[x][y] = PLAYER;
         break;
      }
   } while (boards[x][y] != ' ');

}
void computerMove()
{
   //creates a seed based on current time
   srand(time(0));
   int x;
   int y;

   if(checkFreeSpaces() > 0)
   {
      do
      {
         x = rand() % 3;
         y = rand() % 3;
      } while (boards[x][y] != ' ');

      boards[x][y] = COMPUTER;
   }
   else
   {
      printWinner(' ');
   }
}
char checkWinner()
{
   //check rows
   for(int i = 0; i < 3; i++)
   {
      if(boards[i][0] == boards[i][1] && boards[i][0] == boards[i][2])
      {
         return boards[i][0];
      }
   }
   //check columns
   for(int i = 0; i < 3; i++)
   {
      if(boards[0][i] == boards[1][i] && boards[0][i] == boards[2][i])
      {
         return boards[0][i];
      }
   }
   //check diagonals
   if(boards[0][0] == boards[1][1] && boards[0][0] == boards[2][2])
   {
      return boards[0][0];
   }
   if(boards[0][2] == boards[1][1] && boards[0][2] == boards[2][0])
   {
      return boards[0][2];
   }

   return ' ';
}
void printWinner(char winner)
{
   if(winner == PLAYER)
   {
      printf("YOU WIN!");
   }
   else if(winner == COMPUTER)
   {
      printf("YOU LOSE!");
   }
   else{
      printf("IT'S A TIE!");
   }
}
