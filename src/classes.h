#include<iostream>								// in-built library
#include<conio.h>								// in-built library
#include<cstdlib>								// in-built library
#include<ctime>									// in-built library
#include<iomanip>								// in-built library
#include<string>								// in-built library
#include<fstream>								// in-built library

using namespace std;

const int X=20;									// constant global integer for vertical dimension of the grid
const int Y=20;									// constant global integer for horizontal dimension of the grid
const unsigned char completeFill=219;			// constant global character for outline of the grid
const unsigned char degree=248;					// constant global character for the blocks
const double easy=10;							// constant global double for defining the speed of the easy game
const double hard=1;							// constant global double for defining the speed of the hard game

class Block										// class for the blocks
{
private:										// private members
	unsigned char block[4][4];					// character variable array defining the blocks 					
	int type;									// integer variable defining the type of block
public:											// public members
	Block()										// constructor
	{
		for (int i=0; i<4; i++)
			for (int j=0; j<4; j++)
				block[i][j]=' ';
	}
	void blockSelection();						// prototype for block selection function
	void blockRotation();						// prototype for block rotation function
	void blockOutput(int);						// prototype for block output function
	unsigned char blockCell(int, int);			// prototype for block element returning function
	~Block(){}									// destructor
};												// end of block class

class Grid : public Block						// class for the grid
{
private:										// private members
	unsigned char grid[X][Y];					// character variable array defining the grid 					
	unsigned int score;							// integer variable keeping track of the score
	bool gameOver;								// boolean to check whether game is over
public:											// public members
	Grid() 										// constructor
	{
		score=0;
		gameOver=false;
		for (int i=0; i<X; i++)
			for (int j=0; j<Y; j++)
				grid[i][j]=' ';
	}
	void gridOutput(Block);						// prototype for grid output function
	void gridInitialize(Block);					// prototype for block to grid function
	bool checkGame();							// prototype for checking the status of the game function
	unsigned int getScore();					// prototype for getting score function
	void operator = (Grid);						// prototype for = operator overloading
	void kbInput(int, Grid &, Block &);			// prototype for user input function
	bool moveDown(Grid &);						// prototype for block coming down function
	void moveUp(Grid &, Block &);				// prototype for rotation function
	void moveLeft(Grid &);						// prototype for block going left function
	void moveRight(Grid &);						// prototype for block going right function
	void updateScore();							// prototype for score updation function
	~Grid(){}									// destructor
};												// end of grid class
