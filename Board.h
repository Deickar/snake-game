#ifndef BOARD_H
#define BOARD_H

#include <vector>

struct BoardSquare 
{
	bool hasFood;
	// Integer describing the content of the square
	// 0 == empty, 1 == snake body segment, 2 == snake head, 3 == border
	int content;
};

class Board
{
public:
	Board();
	void generateFood();
	void printBoard();
	void clearBoard();
	void setSquareContent(int square_y, int square_x, int content);
	
protected:
	//BoardSquare * gameBoard;
	//std::vector<BoardSquare><BoardSquare> gameBoard;
	std::vector< std::vector<BoardSquare> > gameBoard;
	int food_x;
	int food_y;
	
	int y_width;
	int x_width;
};

#endif /* BOARD_H */