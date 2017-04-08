#include "snakegame.h"

using namespace std;

SnakeGame::SnakeGame()
{
	score = 0;
	
	int segment_y = 14, segment_x = 28;
	// Initialize the snake's initial 4 segments
	for(int i = 0; i < 4; i++)
	{
		SnakeSegment toAdd;
	
		if(i == 0)
		{
			// The snake's initial direction is always towards the right
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
	}
}

int SnakeGame::runGame()
{
	
}

void SnakeGame::moveSnake()
{
	
}

bool SnakeGame::foodEaten()
{
	
}

void SnakeGame::updateBoard()
{
	
}