#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "board.h"

/*
	Data structure representing a single segment of the snake
*/
struct SnakeSegment
{
	// 1st element = Y coordinate, 2nd element = X coordinate
	std::pair <int, int> currentYX;
	std::pair <int, int> nextYX;
};

class SnakeGame
{
public:
	SnakeGame();
	int runGame();
	void moveSnake();
	bool foodEaten();
	void updateBoard();
	bool gameOver();
	void growSnake();
	std::vector<SnakeSegment> getSnake();
	
private:
	std::vector<SnakeSegment> snake;
	int score;
	int yAxisMoveDirection;
	int xAxisMoveDirection;
	Board * board;
};


#endif /* SNAKEGAME_H */