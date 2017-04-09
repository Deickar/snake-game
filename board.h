#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdlib>

#include <ncurses.h>

struct BoardSquare 
{
	bool hasFood;
	bool isBorder;
	// Integer describing the content of the square
	// 0 == empty, 1 == snake body segment, 2 == snake head, 3 == border
	int content;
	std::vector<int> occupants;
};

class Board
{
public:
	Board();
	void generateFood();
	void printBoard();
	void clearBoard();
	void setSquareContent(int square_y, int square_x, int content);
	void addSquareOccupant(int square_y, int square_x, int content);
	int getSquareContent(int square_y, int square_x);
	std::pair <int, int> getFoodPosition();
	
private:
	std::vector< std::vector<BoardSquare> > gameBoard;
	int food_y;
	int food_x;
	
	int y_width;
	int x_width;
};

#endif /* BOARD_H */