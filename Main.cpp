#include "board.h"
#include "snakegame.h"
#include <string>

#include <unistd.h>  /* only for sleep() */

using namespace std;

int kbhit(void)
{
	int ch = getch();

    if(ch != ERR)
	{
		ungetch(ch);
		return 1;
    } 
	else 
	{
        return 0;
    }
}

int main()
{
	initscr();

    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    scrollok(stdscr, TRUE);
	
	Board * b = new Board();
	/*b->printBoard();
	b->clearBoard();
	b->generateFood();
	b->printBoard();
	b->setSquareContent(26, 1, 3);
	b->setSquareContent(-1, 1, 3);
	
	b->setSquareContent(1, -1, 3);
	b->setSquareContent(1, 52, 3);*/
	
	int counter = 0;
	string msg = "";
	
	while (1) 
	{
		
		if (kbhit()) 
		{
			//b->printBoard();
			//printw("KEY PRESSED\n");
			printw("Key pressed! It was: %d\n", getch());
			//refresh();
			b->generateFood();
        } 
		else 
		{
			//b->printBoard();
			//printw("No key pressed yet...\n");
            //refresh();
            sleep(1);
        }
		
		counter += 1;
		
		b->printBoard();
		refresh();
		
		//system("clear");
		clear();
    }
	
	endwin();
	
	return 0;
}