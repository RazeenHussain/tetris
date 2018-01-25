#include"classes.h"																					// user-defined library

int play(double);																					// prototype for play function 
void updateHighScore(int);																			// prototype for highscore updation function
void instructions();																				// prototype for instruction function
void highscore();																					// prototype for highscore function

int main()																							// main function starts program execution
{
	system("color bf");																				// changes background clour to blue and foreground clour to white
	char option='0';																				// variable for input of choice of user
	while(option!=5)
	{
		system("cls");																				// clears the screen
		cout<<endl<<endl<<setw(40)<<"WELCOME TO TETRIS"<<endl<<endl<<endl;
		cout<<"  MAIN MENU"<<endl<<endl;
		cout<<"  1) PLAY EASY GAME   "<<setw(12)<<"(PRESS 1)"<<endl;
		cout<<"  2) PLAY HARD GAME   "<<setw(12)<<"(PRESS 2)"<<endl;
		cout<<"  3) INSTRUCTIONS     "<<setw(12)<<"(PRESS 3)"<<endl;
		cout<<"  4) HIGHSCORE        "<<setw(12)<<"(PRESS 4)"<<endl;
		cout<<"  5) EXIT             "<<setw(12)<<"(PRESS 5)"<<endl<<endl;
		cout<<"  ENTER YOUR CHOICE"<<endl<<"  ";
		cin>>option;
		while (option!='1' && option!='2' && option!='3' && option!='4' && option!='5')
		{
			cout<<"  INVALID OPTION"<<endl<<"PLEASE RE-ENTER YOUR CHOICE"<<endl<<"  ";
			cin>>option;
		}
		if (option=='1')
			updateHighScore(play(easy));
		else if (option=='2')
			updateHighScore(play(hard));
		else if (option=='3')
			instructions();
		else if (option=='4')
			highscore();
		else if (option=='5')
			return 0;
	}
}