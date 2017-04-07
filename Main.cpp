#include "Board.h"
#include <iostream>

using namespace std;

int main()
{
	Board * b = new Board();
	b->printBoard();
	b->clearBoard();
	b->printBoard();
	return 0;
}