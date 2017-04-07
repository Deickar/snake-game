#include "Board.h"
#include <iostream>

using namespace std;

Board::Board()
{
	gameBoard.resize(30, vector<BoardSquare>(52));
	//gameBoard.resize(30, )
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
			
			// All squares do not have food at the beginning
			gameBoard[y][x].hasFood = false;
		}
	}
	
	// Initialize the food coordinates
	food_x = -1, food_y = -1;
	
	gameBoard[28][25].content = 2;
	//gameBoard[28][25].hasFood = true;
}

void Board::generateFood()
{
	
}

/*
	Prints out the current board state onto the console.
*/
void Board::printBoard()
{
	for(int y = 0; y < 30; y++)
	{
		for(int x = 0; x < 52; x++)
		{
			if(gameBoard[y][x].hasFood)
			{
				cout << "F";
				continue;
			}
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

/*
	Clears board of all snake data.
	Does not clear food data.
*/
void Board::clearBoard()
{
	// Ignore the borders when clearing data
	for(int y = 1; y <= 28; y++)
	{
		for(int x = 1; x <= 50; x++)
		{
			gameBoard[y][x].content = 0;
		}
	}
}