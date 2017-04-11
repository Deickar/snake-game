#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "board.h"
#include "snakegame.h"

using namespace std;

TEST_CASE( "The content of gameBoard[10][10] are set to different values") {
	Board * b = new Board();
	
	REQUIRE(b->getSquareContent(10, 10) == 0);
	
 	SECTION( "gameBoard[10][10]'s content should be 2" ) 
	{
		b->setSquareContent(10, 10, 2);
		REQUIRE(b->getSquareContent(10, 10) == 2);
	}
	
	SECTION( "gameBoard[10][10]'s content should be 0 after calling the clearBoard() method" ) 
	{
		b->clearBoard();
		REQUIRE(b->getSquareContent(10, 10) == 0);
	}
}

TEST_CASE( "The location of the food item changes after calling generateFood()") {
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