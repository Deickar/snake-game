#include "Board.h"
#include <iostream>

using namespace std;

Board::Board()
{
	// Initialize the board
	for(int y = 0; y < 30; y++)
	{
		for(int x = 0; x < 52; x++)
		{
			// Set borders to 3 and everything else to 0
			if(y == 0 || y == 29| x == 0 || x == 51)
			{
				gameBoard[y][x].content = 3;
			}
			else
			{
				gameBoard[y][x].content = 0;
			}
		}
	}
}

void Board::generateFood()
{
	
}

/*
	Prints out the current board state onto the console
*/
void Board::printBoard()
{
	for(int y = 0; y < 30; y++)
	{
		for(int x = 0; x < 52; x++)
		{
			//cout << gameBoard[y][x].content;
			switch(gameBoard[y][x].content) {
				case 0 : cout << " ";
					break;
				case 1 : cout << "*";
					break;
				case 2 : cout << "@";
					break;
				case 3 : cout << "#";
					break;
			}
		}
		cout << endl;
	}
}