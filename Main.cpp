#include "Board.h"
#include <iostream>

using namespace std;

int main()
{
	Board * b = new Board();
	b->printBoard();
	b->clearBoard();
	b->generateFood();
	b->printBoard();
	b->setSquareContent(26, 1, 3);
	b->setSquareContent(-1, 1, 3);
	
	b->setSquareContent(1, -1, 3);
	b->setSquareContent(1, 52, 3);
	return 0;
}