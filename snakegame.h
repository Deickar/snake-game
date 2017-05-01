#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "board.h"
#include <unordered_map>
#include <queue>
#include <stack>

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
	int runGame(int activateAI);
	void moveSnake();
	void growSnake();
	void updateBoard();
	bool foodEaten();
	bool gameOver();
	int kbhit(void);
	void detectPlayerInput();
	std::vector<SnakeSegment> getSnake();
	
	// AI related methods
	std::string makeKey(std::pair<int, int> pairToConvert);
	void findPathToFoodBFS();
	void makeAIMove();
	
private:
	Board * board;
	std::vector<SnakeSegment> snake;
	int score;
	int yAxisMoveDirection;
	int xAxisMoveDirection;
	
	// Queue used for BFS purposes
	std::queue< std::pair<int, int> > queue;
	// Hash table which maps each square on the board to its parent (when traversing the board)
	std::unordered_map< std::string, bool > visited;
	// Hash table which maps each square on the board to its parent (when traversing the board)
	// Key == current position, value == parent's YX coordinates
	std::unordered_map< std::string, std::pair<int, int> > parent;
	// Move list containing the moves the snake should make to reach the current food item
	std::stack< std::pair<int, int> > nextAIMove;
};


#endif /* SNAKEGAME_H */