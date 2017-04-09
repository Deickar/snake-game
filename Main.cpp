#include "board.h"
#include "snakegame.h"
#include <string>
#include <iostream>

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
	SnakeGame * s = new SnakeGame();
	s->growSnake();
	s->growSnake();
	s->growSnake();
	s->updateBoard();
	/*cout << s->gameOver() << endl;
	s->updateBoard();
	cout << s->gameOver() << endl;*/ // TODO REMOVE
	
	s->runGame();
	/*int counter = 0;
	string msg = "";
	
	while (1) 
	{
		b->printBoard();
		printw("SCORE: %d\n", counter);
		
		if (kbhit()) 
		{
			printw("Key pressed! It was: %d\n", getch());
			b->generateFood();
			refresh();
			sleep(1);
        } 
		else 
		{
			//b->printBoard();
			printw("No key pressed yet...\n");
            refresh();
            sleep(1);
        }
	
		counter += 1;
		clear();
    }*/
	
	endwin();
	
	cout << "KEKE GEM OVER!!!" << endl;
	
	return 0;
}