#include "board.h"
#include <iostream>
#include <algorithm>

using namespace std;

Board::Board()
{
	y_width = 20;
	x_width = 52;
	
	gameBoard.resize(y_width, vector<BoardSquare>(x_width));
	
	for(int y = 0; y < y_width; y++)
	{
		for(int x = 0; x < x_width; x++)
		{
			// Set borders to 3 and everything else to 0
			if(y == 0 || y == (y_width - 1) || x == 0 || x == (x_width - 1))
			{
				gameBoard[y][x].content = 3;
				gameBoard[y][x].isBorder = true;
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
			if(gameBoard[y][x].isBorder)
			{
				printw("#");
			}
			else if(gameBoard[y][x].hasFood)
			{
				printw("F");
				//cout << "F";
			}
			else if( find(gameBoard[y][x].occupants.begin(), gameBoard[y][x].occupants.end(), 0) != gameBoard[y][x].occupants.end() )
			{
				printw("@");
			}
			else if( !gameBoard[y][x].occupants.empty() )
			{
				printw("*");
			}
			else
			{
				printw(" ");
			}
			/*switch(gameBoard[y][x].content) {
				case 0 : printw(" ");
					break;
				case 1 : printw("*");
					break;
				case 2 : printw("@");
					break;
				case 3 : printw("#");
					break;
			}
			switch(gameBoard[y][x].content) {
				case 0 : cout << " ";
					break;
				case 1 : cout << "*";
					break;
				case 2 : cout << "@";
					break;
				case 3 : cout << "#";
					break;
			}*/
		}
		printw("\n");
		//cout << endl;
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
			//gameBoard[y][x].content = 0;
			gameBoard[y][x].occupants.clear();
		}
	}
}

/*
	Sets the content of the specified square on the board
	TODO <<<<<< remove this, no longer needed
*/
void Board::setSquareContent(int square_y, int square_x, int content)
{
	// Out of bounds check
	if(square_y < 0 || square_y > (y_width - 1) || square_x < 0 || square_x > (x_width - 1))
	{
		return;
	}
	
	gameBoard[square_y][square_x].content = content;
}

void Board::addSquareOccupant(int square_y, int square_x, int content)
{
	// Out of bounds check
	if(square_y < 0 || square_y > (y_width - 1) || square_x < 0 || square_x > (x_width - 1))
	{
		return;
	}
	
	gameBoard[square_y][square_x].occupants.push_back(content);
}

/*
	Returns the content of the specified square
*/
int Board::getSquareContent(int square_y, int square_x)
{
	// Out of bounds check
	if(square_y < 0 || square_y > (y_width - 1) || square_x < 0 || square_x > (x_width - 1))
	{
		return -1;
	}
	
	return gameBoard[square_y][square_x].content;
}

/*
	Returns the location of the current food item
*/
pair <int, int> Board::getFoodPosition()
{
	pair <int, int> foodPosition = make_pair(food_y, food_x);
	return foodPosition;
}