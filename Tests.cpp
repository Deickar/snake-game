#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Board.h"

using namespace std;

TEST_CASE( "The content of gameBoard[10][10] are set to different values") {
	Board * b = new Board();
    //REQUIRE( test == 2 );
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