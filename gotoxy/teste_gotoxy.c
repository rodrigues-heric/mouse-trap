/* Load Libraries */
#include <conio.h>
#include <windows.h>
#include <stdio.h>

/* Declare Goto Function */
void gotoxy(int, int);

/* Init X and Y plus the Variables which hold
 previous X and Y. */
int x, y, lastx, lasty;

/* Make a CHAR variable to get Key Input */
char a;

/* Main Function */
int main()
{
 /* Give a value to all integer variables we declared */
 x = 1; y = 1;
 lastx = x; lasty = y;

 /* start an Infinite Loop */
 while(1 == 1)
 {
 /* Head to LastX and LastY and clear old O*/
 gotoxy(lastx, lasty);
 printf(" ");
 /* Draw New M */
 gotoxy(x,y);
 printf("M");
 /* Get Input */
 a = getch();
 /* Remember Old X and Y */
 lastx = x; lasty = y;
/* If Down Arrow is Pressed, Y is increased */
 if (a == 80) y = y + 1;
/* If Up Arrow is Pressed, Y is decreased */
 if (a == 72) y = y - 1;
/* If Right Arrow is Pressed, X is increased */
 if (a == 77) x = x + 1;
/* If Left Arrow is Pressed, X is decreased */
 if (a == 75) x = x - 1;
 }
}

/* Make GOTOXY function */
void gotoxy(int eex, int eey)
{
  COORD coord;
  coord.X = eex;
  coord.Y = eey;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
