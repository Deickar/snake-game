main : Main.cpp board.o snakegame.o
	g++ -o main Main.cpp board.o snakegame.o -lncurses -std=c++11

snakegame.o : snakegame.h SnakeGame.cpp
	g++ -c SnakeGame.cpp -o snakegame.o -std=c++11

board.o : board.h Board.cpp
	g++ -c Board.cpp -o board.o -lncurses
	
tests: Tests.cpp board.o snakegame.o
	g++ -o tests Tests.cpp board.o snakegame.o -lncurses -std=c++11
	
clean:
	\rm *.o main
	
cleantests:
	\rm tests