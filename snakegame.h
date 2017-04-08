#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "board.h"

/*
	Data structure representing a single segment of the snake
*/
struct SnakeSegment
{
	std::pair <int, int> currentYXPosition;
	std::pair <int, int> nextYXPosition;
};

class SnakeGame
{
public:
	SnakeGame();
	int runGame();
	void moveSnake();
	bool foodEaten();
	void updateBoard();
	
private:
	std::vector<SnakeSegment> snake;
	int score;
};


#endif /* SNAKEGAME_H */