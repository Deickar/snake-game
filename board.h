#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdlib>

#include <ncurses.h>

struct BoardSquare 
{
	bool hasFood;
	bool isBorder;
	std::vector<int> occupants;
};

class Board
{
public:
	Board();
	void printBoard();
	void clearBoard();
	void generateFood();
	void addSquareOccupant(int square_y, int square_x, int content);
	BoardSquare getSquare(int square_y, int square_x);
	std::pair <int, int> getFoodPosition();
	
private:
	std::vector< std::vector<BoardSquare> > gameBoard;
	int food_y;
	int food_x;
	int y_width;
	int x_width;
};

#endif /* BOARD_H */