#ifndef MENU_H
#define MENU_H

#include <iostream>
using namespace std;

#define UKEY 72
#define DKEY 80
#define LKEY 75
#define RKEY 77
#define ENTER 13

#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

#define UKEY 72
#define DKEY 80
#define LKEY 75
#define RKEY 77
#define ENTER 13

void displayList(boolean[], string, string[], int);
void setBooleanArray(int, int&, int, boolean[]);
boolean* posArrayGenerator(int);
void initArray(boolean[], int);
void banner(string);

int initMenu(string headline, string options[], int numOfOptions)
{
	int c = 0, currentSelection = 1;
	boolean* pos = new boolean[];
	pos = posArrayGenerator(numOfOptions);
	initArray(pos, numOfOptions);
	int  y = 0;

	displayList(pos, headline, options, numOfOptions);
	while (1)
	{

		c = 0;

		switch (c = _getch())
		{

		case UKEY:
			system("CLS");
			setBooleanArray(c, y, numOfOptions, pos);
			displayList(pos, headline, options, numOfOptions);
			break;

		case DKEY:
			system("CLS");
			setBooleanArray(c, y, numOfOptions, pos);
			displayList(pos, headline, options, numOfOptions);
			break;




		case ENTER:		//if the user presses the enter key 
			
			for (int i = 0; i < sizeof(options); i++)	//loop as many times as there are menu options
			{
				if (pos[i]){ return (i + 1); }		//return the value of pos[] that corresponds to the menu item that the user had highlighted when they pressed enter
													//I return i+1 instead of just i to simplify things within game code; it's easier to think 'if option 1 was selected, do this', 'if option 2 was selected, do that' etc
    																															  //instead of 'if option 0 was selected, do this'.
			}

			break;

		}
	}
}

boolean* posArrayGenerator(int numOfOptions)
{
	switch (numOfOptions)
	{
	case 2: {return new boolean[2]; }
	case 3: {return new boolean[3]; }
	case 4: {return new boolean[4]; }
	case 5: {return new boolean[5]; }
	case 6: {return new boolean[6]; }
	case 7: {return new boolean[7]; }
	case 8: {return new boolean[8]; }
	case 9: {return new boolean[9]; }
	case 10: {return new boolean[10]; }
	case 11: {return new boolean[11]; }
	case 12: {return new boolean[12]; }
	}
}

void setBooleanArray(int c, int& y, int ymax, boolean pos[]){
	pos[y] = false;
	switch (c)
	{
	case UKEY: //on a press of the up key
		y--;
		break;

	case DKEY: //on a press of the down key
		y++;
		break;


	}


	if (y < 0){ y = (ymax); } //loop around to the other side.
	if (y > ymax){ y = 0; }

	pos[y] = true;


}


void displayList(boolean pos[], string headline, string options[], int numOfOptions){

	banner(headline);
	for (int i = 0; i < numOfOptions; i++) 
	{
		if (pos[i]){ cout << "->"; }
		else{ cout << "  "; }
		cout << (i+1)<<". "<<options[i] << endl;
	}


}

void initArray(boolean pos[], int numOfOptions){	//this function simply initializes all booleans in pos[] to false, then sets pos[0] to true
	for (int i = 0; i < numOfOptions; i++)
	{
		pos[i] = false;
	}

	pos[0] = true;
}



void banner(string headline)
{
	system("CLS");

	cout <<headline<< endl;
}
#endif