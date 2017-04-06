#ifndef BOARD_H
#define BOARD_H

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
	
	
protected:
	BoardSquare gameBoard[30][52];
	int food_x;
	int food_y;
	
};

#endif /* BOARD_H */