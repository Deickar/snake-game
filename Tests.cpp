#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "board.h"
#include "snakegame.h"

using namespace std;


TEST_CASE( "Test Board's clearBoard() method") {
	Board * b = new Board();
	
	for(int y = 1; y <= (20 - 2); y++)
	{
		for(int x = 1; x <= (52 - 2); x++)
		{
			REQUIRE(b->getSquare(y, x).occupants.size() == 0);
		}
	}
}

TEST_CASE( "Test Board's generateFood() method") {
	Board * b = new Board();
	pair <int, int> initial = make_pair(0, 0); 
	
 	SECTION( "The food item's initial position is [0, 0]" ) 
	{	
		REQUIRE(b->getFoodPosition() == initial);
	}
	
	SECTION( "Position is no longer [0, 0] after calling generateFood()" ) 
	{
		b->generateFood();
		REQUIRE(b->getFoodPosition() != initial);
	}
}

TEST_CASE( "Test Board's getSquare() method") {
	Board * b = new Board();
	
 	SECTION( "board[0][25] is a border square" ) 
	{	
		REQUIRE(b->getSquare(0, 25).isBorder == true);
	}
	
	SECTION( "board[10][25] is not a border square" ) 
	{	
		REQUIRE(b->getSquare(10, 25).isBorder != true);
	}
}

TEST_CASE( "Test Board's addSquareOccupant() method") {
	Board * b = new Board();
	
 	SECTION( "board[10][15] initially has no occupants" ) 
	{	
		REQUIRE(b->getSquare(10, 15).occupants.size() == 0);
	}
	
	SECTION( "board[10][15] has occupants 5 and 6 after two additions" ) 
	{	
		b->addSquareOccupant(10, 15, 5);
		REQUIRE(b->getSquare(10, 15).occupants.size() == 1);
		b->addSquareOccupant(10, 15, 6);
		REQUIRE(b->getSquare(10, 15).occupants.size() == 2);
		
		REQUIRE(b->getSquare(10, 15).occupants[0] == 5);
		REQUIRE(b->getSquare(10, 15).occupants[1] == 6);
	}
}

TEST_CASE( "Test SnakeGame's growSnake() method") {
	SnakeGame * s = new SnakeGame();
	
 	SECTION( "Snake's initial size is 4" ) 
	{	
		REQUIRE(s->getSnake().size() == 4);
	}
	
	SECTION( "Snake grows by 3 after calling growSnake() x3" ) 
	{
		s->growSnake();
		s->growSnake();
		s->growSnake();
		REQUIRE(s->getSnake().size() == 7);
		
		SECTION( "Snake's new tail end is at [14, 22]" ) 
		{
			vector<SnakeSegment> snake = s->getSnake();
			SnakeSegment finalSegment = snake[snake.size() - 1];
			REQUIRE( finalSegment.currentYX.first == 14 );
			REQUIRE( finalSegment.currentYX.second == 22 );
		}
	}
	
}

TEST_CASE( "Test SnakeGame's gameOver() method" ) {
	SnakeGame * s = new SnakeGame();
	
 	SECTION( "The game is not over when it is first initialized" ) 
	{	
		REQUIRE(s->gameOver() == false);
	}
	
	SECTION( "The game does not end when the snake moves into empty squares" ) 
	{	
		for(int i = 0; i < 22; i++)
		{
			s->moveSnake();
			s->updateBoard();
		}
		REQUIRE(s->gameOver() == false);
		
		SECTION( "The game ends when the head collides with a border" ) 
		{	
			s->moveSnake();
			s->updateBoard();
			REQUIRE(s->gameOver() == true);
		}
	}
}