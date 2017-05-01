#include "snakegame.h"
#include <unistd.h>  /* only for sleep() */
#include <iostream> // TODO REMOVE <<<<<<<<<<<<<<<<<<<

using namespace std;

SnakeGame::SnakeGame()
{
	score = 0;
	// Default movement is towards the right
	yAxisMoveDirection = 0, xAxisMoveDirection = 1;
	
	int segment_y = 14, segment_x = 28;
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
	TODO <<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/
string SnakeGame::makeKey(std::pair<int, int> pairToConvert)
{
	string key = "" + to_string(pairToConvert.first) + " " + to_string(pairToConvert.second);
	return key;
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
	
	// Keep looping and detecting player input until the game ends
	while(!gameOver())
	{	
		// Calculate new path to the newly generated food item if the movelist is empty
		if(nextAIMove.empty())
		{
			printw("KEKE\n");
			// Use BFS to traverse the board starting from the snake's head until the food item is found
			
			// Mark all the squares that the snake occupies as visited so that the snake won't move into itself
			visited.clear();
			parent.clear();
			for(int i = 1; i < snake.size(); i++)
			{
				string key = makeKey(snake[i].currentYX); //"" + to_string(snake[i].currentYX.first) + " " + to_string(snake[i].currentYX.second);
				visited[key] = true;
			}
			
			// TODO make BFS into its own method
			// Initiate BFS here
			queue.push( make_pair(snake[0].currentYX.first, snake[0].currentYX.second) );
			while(!queue.empty())
			{
				pair<int, int> curYX = queue.front();
				queue.pop();
				
				// Exit the loop if the food item is found
				if(curYX == board->getFoodPosition())
				{
					//TODO <<<<<<<<<<<<<<
					/*printw("FOUND!\n");
					refresh();
					sleep(2);*/
					break;
				}
				
				// TODO make key-ify into a helper <<<<<<<<<<<<<<<<<<<<, 
				string key = makeKey(curYX); //"" + to_string(curYX.first) + " " + to_string(curYX.second);
				if(!visited[key])
				{
					// Mark position as visited
					visited[key] = true;
					// Visit all adjacent nodes clockwise (URDL)
					// -1,0 || 0,1 || 1,0 || 0,-1
					pair<int, int> URDL[4];
					URDL[0] = make_pair(curYX.first - 1, curYX.second);
					URDL[1] = make_pair(curYX.first, curYX.second + 1);
					URDL[2] = make_pair(curYX.first + 1, curYX.second);
					URDL[3] = make_pair(curYX.first, curYX.second - 1);
					
					for(int i = 0; i < 4; i++)
					{
						queue.push(URDL[i]);
						// Set parent here
						key = makeKey(URDL[i]);
						parent[key] = curYX;
					}
				}
			}
			// Clear the queue
			while(!queue.empty())
			{
				queue.pop();
			}
			
			// Start at the food item position and move backwards following the parents' trail until the snake's head is found
			
		}
		
		detectPlayerInput();
		
		moveSnake();
		updateBoard();
		board->printBoard();
		printw("Score: %d\n", score);
		printw("Snake length: %d\n", snake.size());
		refresh();
		
		// If the snake eats something the growth is shown upon the next move / screen refresh
		if(foodEaten())
		{
			score++;
			growSnake();
			board->generateFood();
			updateBoard();
		}
		
		// Display the current board state for 1 second before clearing it
		sleep(1);
		clear();
	}
	
	board->printBoard();
	printw(">>>>>>>>>> GAME OVER!!! <<<<<<<<<<\n");
	printw("Score: %d\n", score);
	printw("Snake length: %d\n", snake.size());
	refresh();
	sleep(1);
	
	endwin();
}

/*
	Moves the entire snake forward by one square
*/
void SnakeGame::moveSnake()
{
	for(int i = 0; i < snake.size(); i++)
	{
		snake[i].currentYX = snake[i].nextYX;
		
		if(i == 0)
		{
			// The snake head's next location is calculated using the current move direction
			snake[i].nextYX = make_pair(snake[i].currentYX.first + yAxisMoveDirection, snake[i].currentYX.second + xAxisMoveDirection);
		}
		else
		{
			snake[i].nextYX = snake[i - 1].currentYX;
		}
	}
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
	
	snake.push_back(segmentToAdd);
}

/*
	Updates the game board to reflect any moves the snake makes
*/
void SnakeGame::updateBoard()
{
	board->clearBoard();
	
	for(int i = 0; i < snake.size(); i++)
	{
		board->addSquareOccupant(snake[i].currentYX.first, snake[i].currentYX.second, i);
	}
}

/*
	Returns true if the snake head reaches a square that contains a food item, false otherwise
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
	Returns true if game over conditions are met, false otherwise.
*/
bool SnakeGame::gameOver()
{
	BoardSquare square = board->getSquare(snake[0].currentYX.first, snake[0].currentYX.second);
	
	// The game is over if the snake's head reaches a square that is not empty (occupied by snake itself / border)
	if(square.isBorder || square.occupants.size() > 1)
	{
		return true;
	}
	
	return false;
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
	Detects movement input from the player and adjusts the snake's move direction accordingly.
*/
void SnakeGame::detectPlayerInput()
{
	if (kbhit()) 
	{
		int newY = 0, newX = 0;
		
		char moveDirection = getch();
		switch(moveDirection) {
			// W
			case 119 : 
				newY = -1, newX = 0;
				break;
			// A
			case 97 :
				newY = 0, newX = -1;
				break;
			// S
			case 115 :
				newY= 1, newX = 0;
				break;
			// D
			case 100 :
				newY = 0, newX = 1;
				break;
		}
		
		// Prevents the user from making the snake head move backwards into its body
		if(yAxisMoveDirection + newY != 0 && xAxisMoveDirection + newX != 0)
		{
			yAxisMoveDirection = newY, xAxisMoveDirection = newX;
		}

		// Update the snake head's next position
		int nextY = snake[0].currentYX.first + yAxisMoveDirection;
		int nextX = snake[0].currentYX.second + xAxisMoveDirection;
		snake[0].nextYX = make_pair(nextY, nextX);
	} 
}

/*
	Returns the snake vector. For unit testing purposes only.
*/
vector<SnakeSegment> SnakeGame::getSnake()
{
	return snake;
}