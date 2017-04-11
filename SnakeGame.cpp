#include "snakegame.h"
#include <unistd.h>  /* only for sleep() */

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
			toAdd.nextYX = make_pair(segment_y + yAxisMoveDirection, segment_x + xAxisMoveDirection);
			toAdd.currentYX = make_pair(segment_y, segment_x);
		}
		else
		{
			// The next position of the current segment is equal to the current position of the segment ahead of it
			toAdd.nextYX = make_pair(segment_y, segment_x);
			segment_x -= 1;
			toAdd.currentYX = make_pair(segment_y, segment_x);
		}
		
		snake.push_back(toAdd);
	}
	
	board = new Board();
	board->generateFood();
	updateBoard();
}

/*
	Helper method for detecting keypresses
*/
int SnakeGame::kbhit(void)
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

/*
	Runs the snake game from start to finish.
*/
int SnakeGame::runGame()
{
	initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
	
	// TODO <<<<
	while(!gameOver())
	{	
		detectPlayerInput();
		
		moveSnake();
		updateBoard();
		board->printBoard();
		printw("[%d, %d]\n", snake[0].currentYX.first, snake[0].currentYX.second);
		refresh();
		
		sleep(1);
		clear();
	}
	
	board->printBoard();
	printw("KEKEKE\n");
	refresh();
	sleep(1);
	endwin();
}

/*
	Moves the entire snake forward by one square
	TODO
*/
void SnakeGame::moveSnake()
{
	for(int i = 0; i < snake.size(); i++)
	{
		snake[i].currentYX = snake[i].nextYX;
		
		if(i == 0)
		{
			snake[i].nextYX = make_pair(snake[i].currentYX.first + yAxisMoveDirection, snake[i].currentYX.second + xAxisMoveDirection);
		}
		else
		{
			// 
			snake[i].nextYX = snake[i - 1].currentYX;
		}
	}
}

/*
	Returns true if the snake head reaches a square that contains a food item, false otherwise
	TODO
*/
bool SnakeGame::foodEaten()
{
	BoardSquare square = board->getSquare(snake[0].currentYX.first, snake[0].currentYX.second);
	
	if(square.hasFood)
	{
		return true;
	}
	
	return false;
}

/*
	Updates the game board to reflect any moves the snake makes
	TODO
*/
void SnakeGame::updateBoard()
{
	board->clearBoard();
	
	for(int i = 0; i < snake.size(); i++)
	{
		
		board->addSquareOccupant(snake[i].currentYX.first, snake[i].currentYX.second, i);
		/*
		if(i == 0)
		{
			board->setSquareContent(snake[i].currentYX.first, snake[i].currentYX.second, 2);
		}
		else
		{
			board->setSquareContent(snake[i].currentYX.first, snake[i].currentYX.second, 1);
		}*/
	}
}

/*
	Returns true if game over conditions are met, false otherwise.
*/
bool SnakeGame::gameOver()
{
	//int squareContent = board->getSquareContent( snake[0].currentYX.first, snake[0].currentYX.second);
	BoardSquare square = board->getSquare(snake[0].currentYX.first, snake[0].currentYX.second);
	
	// The game is over if the snake's head reaches a square that is not empty (occupied by snake itself / border)
	// TODO THIS make it use occupants vector + isBorder
	if(square.isBorder || square.occupants.size() > 1)
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
	int yAxisDifference = snake[snake.size() - 2].currentYX.first - snake[snake.size() - 1].currentYX.first;
	int xAxisDifference = snake[snake.size() - 2].currentYX.second - snake[snake.size() - 1].currentYX.second;
	
	// The new segment should be directly behind the final segment of the snake
	int newY = snake[snake.size() - 1].currentYX.first - yAxisDifference;
	int newX = snake[snake.size() - 1].currentYX.second - xAxisDifference;;

	segmentToAdd.nextYX = snake[snake.size() - 1].currentYX;
	segmentToAdd.currentYX = make_pair(newY, newX);
	
	//cout << "Y: " << newY << " || X: " << newX << endl; 
	
	snake.push_back(segmentToAdd);
}

/*
	Returns the snake vector. For unit testing purposes only.
*/
vector<SnakeSegment> SnakeGame::getSnake()
{
	return snake;
}

void SnakeGame::detectPlayerInput()
{
	// TODO make snake unable of moving backwards into itself <<<<<<<<<<<<<<<<<<<<
	if (kbhit()) 
	{
		char moveDirection = getch();
		switch(moveDirection) {
			// W
			case 119 : 
				printw("Key pressed! It was: %d\n", moveDirection);
				yAxisMoveDirection = -1, xAxisMoveDirection = 0;
				break;
			// A
			case 97 :
				printw("Key pressed! It was: %d\n", moveDirection);
				yAxisMoveDirection = 0, xAxisMoveDirection = -1;
				break;
			// S
			case 115 :
				printw("Key pressed! It was: %d\n", moveDirection);
				yAxisMoveDirection = 1, xAxisMoveDirection = 0;
				break;
			// D
			case 100 :
				printw("Key pressed! It was: %d\n", moveDirection);
				yAxisMoveDirection = 0, xAxisMoveDirection = 1;
				break;
		}

		// Update the snake head's next position
		int nextY = snake[0].currentYX.first + yAxisMoveDirection;
		int nextX = snake[0].currentYX.second + xAxisMoveDirection;
		snake[0].nextYX = make_pair(nextY, nextX);
	} 
}