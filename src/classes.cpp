#include"classes.h"																				// user-defined library

void Block::blockSelection()																	// block class function for block selection
{
	for (int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			block[i][j]=1;
	type=rand()%7+1;
	if (type==1)
	{
		block[1][1]=degree;
		block[1][2]=degree;
		block[2][1]=degree;
		block[2][2]=degree;
	}
	if (type==2)
	{
		block[1][0]=degree;
		block[1][1]=degree;
		block[1][2]=degree;
		block[1][3]=degree;
	}
	if (type==3)
	{
		block[1][2]=degree;
		block[1][3]=degree;
		block[2][1]=degree;
		block[2][2]=degree;
	}
	if (type==4)
	{
		block[1][1]=degree;
		block[1][2]=degree;
		block[2][2]=degree;
		block[2][3]=degree;
	}
	if (type==5)
	{
		block[1][1]=degree;
		block[1][2]=degree;
		block[1][3]=degree;
		block[2][1]=degree;
	}
	if (type==6)
	{
		block[1][1]=degree;
		block[1][2]=degree;
		block[1][3]=degree;
		block[2][3]=degree;
	}
	if (type==7)
	{
		block[1][1]=degree;
		block[1][2]=degree;
		block[1][3]=degree;
		block[2][2]=degree;
	}
}										
void Block::blockRotation()																		// block class function for counter clockwise block rotation
{  
	unsigned char temp[4][4];
	for (int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			temp[3-i][j]=block[j][i];
	for (int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			block[i][j]=temp[i][j];
}
void Block::blockOutput(int line)																// block class function for block output
{
	for (int k=0; k<4; k++)
		if (block[line][k]!=degree)
			cout<<" ";
		else
			cout<<block[line][k];
}
unsigned char Block::blockCell(int i,int j)														// block class function for returning block array element
{
	return block[i][j];
}

void Grid::gridOutput(Block nextBlock)															// grid class function for grid output
{
	int line=0;
	system("cls");
	cout<<"\n\t     TETRIS GAME\n\n";
	for (int i=0; i<X; i++)
	{
		cout<<"\t";
		for(int j=0; j<Y; j++)
			if (i==0 || i==1 || i==X-1 || i==X-2 || j==0 || j==1 || j==Y-1 || j==Y-2)
				cout<<completeFill;
			else
				cout<<grid[i][j];
		if (i==X/3)
			cout<<"\t\tNEXT BLOCK";
		if (i>=X/3+1 && line<4)
		{
			cout<<"\t\t   ";
			nextBlock.blockOutput(line);
			line++;
		}
		if (i==X*2/3)
			cout<<"\t\tSCORE = "<<score;
		cout<<endl;
	}
}
void Grid::gridInitialize(Block currentBlock)													// grid class function for transfering block to grid
{
	for(int i=1; i<X-1; i++)
		for(int j=1; j<Y-1; j++)
			grid[i][j]=' ';
	int tempY=Y/2-2;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			grid[i+1][tempY+j]=currentBlock.blockCell(i,j);
}
bool Grid::checkGame()																			// grid class function for checking the status of the game
{
	return gameOver;
}
unsigned int Grid::getScore()																	// grid class function for getting the score of the game
{
	return score;
}
void Grid::operator = (Grid blockGrid)															// grid class = opertor overloading
{
	gameOver=false;
	for (int i=1; i<X-1; i++)
		for (int j=1; j<Y-1; j++)
			if (blockGrid.grid[i][j]==degree)
				if (grid[i][j]==' ')
					grid[i][j]=blockGrid.grid[i][j];
				else
					gameOver=true;
}
void Grid::kbInput(int input, Grid & blockGrid, Block & currentBlock)							// grid class function for user input
{
	if (input==224)
	{
		int arrow = getch();
		switch(arrow)
		{
			case 72:																			// up arrow key
				moveUp(blockGrid, currentBlock);
				break;
			case 75:																			// left arrow key
				moveLeft(blockGrid);
				break;
			case 77:																			// right arrow key
				moveRight(blockGrid);
				break;
			case 80:																			// down arrow key
				while (1)
					if (!(moveDown(blockGrid)))
						break;
				break;
		}
	}
	else if (input=='p')																		// pause key
	{
		cout<<"\n\t\t\tGAME PAUSED\n\t\t";
		system("pause");
	}
}
bool Grid::moveDown(Grid & blockGrid)															// grid class function for block moving down
{
	Grid tempGrid=blockGrid;
	bool check=true;
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (blockGrid.grid[i][j]!=' ')
			{
				if (blockGrid.grid[i][j]==degree)
					grid[i][j]=' ';
				blockGrid.grid[i][j]=' ';
			}
	for (int i=X-1; i>=0; i--)
		for (int j=Y-1; j>=0; j--)
			if (tempGrid.grid[i][j]!=' ')
				blockGrid.grid[i+1][j]=tempGrid.grid[i][j];
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (blockGrid.grid[i][j]==degree && grid[i][j]!=' ')
				check=false;
	for (int j=0; j<Y; j++)
		if (tempGrid.grid[X-3][j]==degree)
			check=false;
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (check)
			{
				if (blockGrid.grid[i][j]==degree)
					grid[i][j]=blockGrid.grid[i][j];
			}
			else
			{
				blockGrid.grid[i][j]=tempGrid.grid[i][j];
				if (tempGrid.grid[i][j]==degree)
					grid[i][j]=tempGrid.grid[i][j];
			}
	return check;
}
void Grid::moveUp(Grid & blockGrid, Block & currentBlock)										// grid class function for rotation
{
	int countX=3, countY=3;
	Block tempBlock=currentBlock;
	Grid tempGrid=blockGrid;
	bool check=true;
	currentBlock.blockRotation();
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (blockGrid.grid[i][j]!=' ')
			{
				if (blockGrid.grid[i][j]==degree)
					grid[i][j]=' ';
				blockGrid.grid[i][j]=' ';
			}
	for (int i=X-1; i>=0; i--)
	{
		countY=3;
		for (int j=Y-1; j>=0; j--)
			if (tempGrid.grid[i][j]!=' ')
			{
				blockGrid.grid[i][j]=currentBlock.blockCell(countX,countY);
				countY--;
			}
		if (countY!=3)
			countX--;
	}
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (blockGrid.grid[i][j]==degree && grid[i][j]!=' ')
				check=false;
	for (int j=0; j<Y; j++)
		if (blockGrid.grid[X-2][j]==degree)
			check=false;
	for (int i=0; i<X; i++)
		if (blockGrid.grid[i][1]==degree)
			check=false;
	for (int i=0; i<X; i++)
		if (blockGrid.grid[i][Y-2]==degree)
			check=false;
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (check)
			{
				if (blockGrid.grid[i][j]==degree)
					grid[i][j]=blockGrid.grid[i][j];
			}
			else
			{
				blockGrid.grid[i][j]=tempGrid.grid[i][j];
				if (tempGrid.grid[i][j]==degree)
					grid[i][j]=tempGrid.grid[i][j];
			}
	if (!check)
		currentBlock=tempBlock;
}
void Grid::moveLeft(Grid & blockGrid)															// grid class function for block going left
{
	Grid tempGrid=blockGrid;
	bool check=true;
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (blockGrid.grid[i][j]!=' ')
			{
				if (blockGrid.grid[i][j]==degree)
					grid[i][j]=' ';
				blockGrid.grid[i][j]=' ';
			}
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (tempGrid.grid[i][j]!=' ')
				blockGrid.grid[i][j-1]=tempGrid.grid[i][j];
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (blockGrid.grid[i][j]==degree && grid[i][j]!=' ')
				check=false;
	for (int i=0; i<X; i++)
		if (tempGrid.grid[i][2]==degree)
			check=false;
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (check)
			{
				if (blockGrid.grid[i][j]==degree)
					grid[i][j]=blockGrid.grid[i][j];
			}
			else
			{
				blockGrid.grid[i][j]=tempGrid.grid[i][j];
				if (tempGrid.grid[i][j]==degree)
					grid[i][j]=tempGrid.grid[i][j];
			}
}
void Grid::moveRight(Grid & blockGrid)															// grid class function for block going right
{
	Grid tempGrid=blockGrid;
	bool check=true;
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (blockGrid.grid[i][j]!=' ')
			{
				if (blockGrid.grid[i][j]==degree)
					grid[i][j]=' ';
				blockGrid.grid[i][j]=' ';
			}
	for (int i=0; i<X; i++)
		for (int j=Y-1; j>=0; j--)
			if (tempGrid.grid[i][j]!=' ')
				blockGrid.grid[i][j+1]=tempGrid.grid[i][j];
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (blockGrid.grid[i][j]==degree && grid[i][j]!=' ')
				check=false;
	for (int i=0; i<X; i++)
		if (tempGrid.grid[i][Y-3]==degree)
			check=false;
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			if (check)
			{
				if (blockGrid.grid[i][j]==degree)
					grid[i][j]=blockGrid.grid[i][j];
			}
			else
			{
				blockGrid.grid[i][j]=tempGrid.grid[i][j];
				if (tempGrid.grid[i][j]==degree)
					grid[i][j]=tempGrid.grid[i][j];
			}
	}
void Grid::updateScore()																		// function for score updation
{
	bool lineFull=true;
	int lines=0;
	for (int i=X-3; i>1; i--)
	{
		lineFull=true;
		for (int j=Y-3; j>1; j--)
			if (grid[i][j]!=degree)
				lineFull=false;
		if (lineFull)
		{
			lines++;
			for (int j=Y-3; j>1; j--)
				grid[i][j]=' ';
			for (int k=i;k>1;k--)
				for (int l=Y-3;l>1;l--)
				{
					grid[k][l]=grid[k-1][l];
					grid[k-1][l]=' ';
				}
			i++;
		}
	}
	if (lines==1)
		score+=1;
	else if (lines==2)
		score+=3;
	else if (lines==3)
		score+=5;
	else if (lines==4)
		score+=7;
}

int play(double delay)																			// function for start of play
{
	system("cls");
	srand(time(0));
	Grid grid, blockGrid;
	Block currentBlock, nextBlock;
	nextBlock.blockSelection();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\t\tWhen Ready ";
	system("pause");
	while(1)
	{
		currentBlock=nextBlock;
		nextBlock.blockSelection();
		blockGrid.gridInitialize(currentBlock);
		grid=blockGrid;
		if (grid.checkGame())
			break;
		while(1)
		{
			for (int counter=0; counter<delay; counter++)
			{
				if (kbhit())
					grid.kbInput(getch(), blockGrid, currentBlock);
				grid.gridOutput(nextBlock);
			}
			if (!grid.moveDown(blockGrid))
				break;
		}
		grid.updateScore();
	}
	system("cls");
	cout<<"\n\n\n\t\tGAMEOVER!"<<"\n\n\t     Your Score is "<<grid.getScore()<<"\n\n\t";
	system("pause");
	return (grid.getScore());
}
void updateHighScore(int score)																	// function for highscore updation
{
	int highScore;
	ifstream high1("highscore.txt");
	if (high1.is_open())
	{
		while(high1.good())
			high1>>highScore;
		high1.close();
		if (score>highScore)
		{
			ofstream high2("highscore.txt"); 
			high2<<score;
			high2.close();
		}
	}
	else 
		cout<<"UNABLE TO UPDATE HIGHSCORE";
}
void instructions()																				// function for displaying instructions
{
	system("cls");
	string line;																				// string used for input from the text file
	ifstream instructions("instructions.txt");													// opening file in read mode
	if (instructions.is_open())
	{
		while(instructions.good())
		{
			getline(instructions,line);
			cout<<line<<endl;
		}
		instructions.close();																	// closing file after use
	}
	else 
		cout<<"UNABLE TO SHOW INSTRUCTIONS";
	cout<<"\n\t\t\t";
	system("pause");
}
void highscore()																				// function for displaying highscore
{
	system("cls");
	cout<<"\n\n\t\tHIGHSCORE IS : ";
	string line;																				// string used for input from the text file
	ifstream highscore("highscore.txt");														// opening file in read mode
	if (highscore.is_open())
	{
		while(highscore.good())
		{
			getline(highscore,line);
			cout<<line<<endl;
		}
		highscore.close();																		// closing file after use
	}
	else 
		cout<<"UNABLE TO SHOW HIGHSCORE";
	cout<<"\n\t\t";
	system("pause");
}