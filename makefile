Main : Main.cpp board.o
	g++ -o Main Main.cpp board.o

board.o : Board.h Board.cpp
	g++ -c Board.cpp -o board.o
	
clean:
	\rm *.o Main