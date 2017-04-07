#include "Board.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Board::Board()
{
	y_width = 26;
	x_width = 52;
	
	gameBoard.resize(26, vector<BoardSquare>(52));
	
	for(int y = 0; y < y_width; y++)
	{
		for(int x = 0; x < x_width; x++)
		{
			// Set borders to 3 and everything else to 0
			if(y == 0 || y == (y_width - 1) || x == 0 || x == (x_width - 1))
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
	
	// Initialize the food coordinates to the temp value of [0, 0]
	food_x = 0, food_y = 0;
}

/*
	Generates a new random location for the next food item.
	Also clears the current food item from the board.
*/
void Board::generateFood()
{
	// Clear the current food item from the board
	gameBoard[food_y][food_x].hasFood = false;
	
	srand(time(NULL));
	// Valid y-axis values are from 1 to 24
	food_y = rand() % (y_width - 2) + 1;
	// Valid x-axis values are from 1 to 50
	food_x = rand() % (x_width - 2) + 1;
	
	gameBoard[food_y][food_x].hasFood = true;
}

/*
	Prints out the current board state onto the console.
*/
void Board::printBoard()
{
	for(int y = 0; y < y_width; y++)
	{
		for(int x = 0; x < x_width; x++)
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
	for(int y = 1; y <= (y_width - 2); y++)
	{
		for(int x = 1; x <= (x_width - 2); x++)
		{
			gameBoard[y][x].content = 0;
		}
	}
}