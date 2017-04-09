main : Main.cpp board.o snakegame.o
	g++ -o main Main.cpp board.o snakegame.o -lncurses

snakegame.o : snakegame.h SnakeGame.cpp
	g++ -c SnakeGame.cpp -o snakegame.o

board.o : board.h Board.cpp
	g++ -c Board.cpp -o board.o -lncurses
	
test:
	g++ -o tests Tests.cpp board.o snakegame.o -lncurses
	
a : a.cpp board.o
	g++ -o a a.cpp board.o -lncurses
	
clean:
	\rm *.o main
	
cleana:
	\rm a