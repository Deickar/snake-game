#include "snakegame.h"

using namespace std;

SnakeGame::SnakeGame()
{
	score = 0;
	// Default movement is towards the right
	yAxisMoveDirection = 0, xAxisMoveDirection = 1;
	
	int segment_y = 14, segment_x = 28; // 14, 28 <<<<<<<<<<<<<<<<<<<<<<<<<
	// Initialize the snake's initial 4 segments
	for(int i = 0; i < 4; i++)
	{
		SnakeSegment toAdd;
	
		if(i == 0)
		{
			// The snake's initial movement direction is always towards the right
			toAdd.nextYXPosition = make_pair(segment_y, segment_x + 1);
			toAdd.currentYXPosition = make_pair(segment_y, segment_x);
		}
		else
		{
			// The next position of the current segment is equal to the current position of the segment ahead of it
			toAdd.nextYXPosition = make_pair(segment_y, segment_x);
			segment_x -= 1;
			toAdd.currentYXPosition = make_pair(segment_y, segment_x);
		}
		
		snake.push_back(toAdd);
		
		/*if(i == 3) // TODO REMOVE <<<<<<<<<<<<<<<<
		{
			cout << "Y: " << toAdd.currentYXPosition.first << " || X: " << toAdd.currentYXPosition.second << endl; 
		}*/
	}
	
	board = new Board();
}

int SnakeGame::runGame()
{
	while(!gameOver())
	{
		
	}
}

/*
	Moves the entire snake forward by one square
*/
void SnakeGame::moveSnake()
{
	for(int i = 0; i < snake.size(); i++)
	{
		// 
		if(i == 0)
		{
			
		}
		else
		{
			
		}
	}
}

bool SnakeGame::foodEaten()
{
	
}

/*
	Updates the game board to reflect any moves the snake makes
*/
void SnakeGame::updateBoard()
{
	
}

/*
	Returns true if game over conditions are met, false otherwise.
*/
bool SnakeGame::gameOver()
{
	int squareContent = board->getSquareContent( snake[0].currentYXPosition.first, snake[0].currentYXPosition.second);
	
	// The game is over if the snake's head reaches a square that is not empty (occupied by snake itself / border)
	if(squareContent != 0)
	{
		return true;
	}
	
	return false;
}

/*
	Appends an additional segement to the tail end of the snake
*/
void SnakeGame::growSnake()
{
	SnakeSegment segmentToAdd;
	
	// Find the y and x-axis difference between the 2nd last and final segment to determine where the new segment should be
	int yAxisDifference = snake[snake.size() - 2].currentYXPosition.first - snake[snake.size() - 1].currentYXPosition.first;
	int xAxisDifference = snake[snake.size() - 2].currentYXPosition.second - snake[snake.size() - 1].currentYXPosition.second;
	
	// The new segment should be directly behind the final segment of the snake
	int newY = snake[snake.size() - 1].currentYXPosition.first - yAxisDifference;
	int newX = snake[snake.size() - 1].currentYXPosition.second - xAxisDifference;;

	segmentToAdd.nextYXPosition = snake[snake.size() - 1].currentYXPosition;
	segmentToAdd.currentYXPosition = make_pair(newY, newX);
	
	//cout << "Y: " << newY << " || X: " << newX << endl; 
	
	snake.push_back(segmentToAdd);
}