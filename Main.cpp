#include "snakegame.h"
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	SnakeGame * s = new SnakeGame();
	
	if(argc == 1)
	{
		s->runGame(0);
	}
	else if(argc == 2)
	{
		string argument = argv[1];
		if(argument.compare("1") == 0)
		{
			s->runGame(1);
		}
	}
	
	return 0;
}