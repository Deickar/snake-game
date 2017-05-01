#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "board.h"
#include <list>
#include <unordered_map>
#include <queue>

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
	void growSnake();
	void updateBoard();
	bool foodEaten();
	bool gameOver();
	int kbhit(void);
	void detectPlayerInput();
	std::vector<SnakeSegment> getSnake();
	std::string makeKey(std::pair<int, int> pairToConvert);
	
private:
	Board * board;
	std::vector<SnakeSegment> snake;
	int score;
	int yAxisMoveDirection;
	int xAxisMoveDirection;
	// Move list containing the moves the snake should make to reach the current food item <<< maybe make this a stack
	std::list< std::pair<int, int> > nextAIMove;
	// Hash table which maps each square on the board to its parent (when traversing the board)
	// Key == current position, value == parent's YX coordinates
	std::unordered_map< std::string, std::pair<int, int> > parent;
	// Queue used for BFS purposes
	std::queue< std::pair<int, int> > queue;
	// Hash table which maps each square on the board to its parent (when traversing the board)
	std::unordered_map< std::string, bool > visited;
};


#endif /* SNAKEGAME_H */