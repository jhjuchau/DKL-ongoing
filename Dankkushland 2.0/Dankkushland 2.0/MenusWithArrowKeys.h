#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

#define UKEY 72
#define DKEY 80
#define LKEY 75
#define RKEY 77
#define ENTER 13

//This header file exists to create menus that are used by the player to make decisions. These menus are controlled by the arrow keys and Enter.
//Each key has a specific integer that it returns when pressed while _getch() is active and looking for input. These values are assigned to their corresponding key above. This improves code legibility later on.    

//The simplest way I could think of to get user input was to have a 


void displayList(int, string, string[], int);		//this function prints the desired list to the console. Further details are provided in the definition below.
void setPos(int, int, int&);		//this function resets the pos variable after every press of Up Arrow or Down Arrow, and allows the menus to loop from top to bottom and vice versa.

int initMenu(string headline, string options[], int numOfOptions)	//basically the main() of this header file. sustains the loops that get the desired input, calls the functions accordingly
{
	int c = 0;	//c is the value of the input. it pivots on _getch(), and is the subject of the switch case that determines the users' menu choice
	int pos = 0; //this variable keeps track of where the user is currently pointing at, so that when the user hits 'enter', the proper menu item is known and returned

	displayList(pos, headline, options, numOfOptions);	//displays the list, see function definition for details
	while (c!=ENTER)	//loop until the user has pressed ENTER
	{


		switch (c = _getch())	//c is the next input in the stream, but there are only cases for Up Arrow, Down Arrow and Enter. Any other normal user input has no effect
		{

		case UKEY:
			system("CLS");
			setPos(c, (numOfOptions-1), pos);
			displayList(pos, headline, options, numOfOptions);
			break;

		case DKEY:
			system("CLS");
			setPos(c, (numOfOptions-1), pos);
			displayList(pos, headline, options, numOfOptions);
			break;




		case ENTER:		//if the user presses the enter key 
			
			return pos + 1;	//if option 2 in this menu system is highlighted, pos==1. this is due to the nature of arrays and the for loop in displayList(). (see that function for more details)

			break;

		}
	}

}


void setPos(int c, int ymax, int& pos){	//after every press of the up or down arrow, this function is called to set pos to a proper value
	switch (c)	
	{
	case UKEY: //on a press of the up key
		pos--;	//decrement pos
		break;

	case DKEY: //on a press of the down key
		pos++;	//increment pos
		break;

		//I could've saved a couple lines of code by not passing 'c' directly, but instead having each if block in the switch case in initMenu pass some kind of sentinel and using if statements
		//I just figured this was more legible. The difference in efficiency is neglible.

	default: break;	//should never happen, since setPos is only called on a UKEY or DKEY press, but I've been told to expect ridiculous things
	}

	//the commented code below is for debugging purposes; I enable them whenever I need to fix how pos is set

	//cout << "\n before correct Y == " << y << endl;

	if (pos < 0){ pos = (ymax); } //if pos goes lower than zero, set pos to ymax
	if (pos > ymax){ pos = 0; }	  //if pos goes higher than ymax, set pos to 0

	//these two lines effectively give pos a domain of [0, ymax]


	//cout << "\n after correct Y == " << y << endl;
	//system("pause");


}


void displayList(int pos, string headline, string options[], int numOfOptions)	//the meat of this header file is a simple for loop that reads everything in the options array, along with some extra conditions
{

	system("CLS");	//clears the screen
	cout << headline << endl;	//headline is a prompt that gives context to the menu options on the screen, since the screen was just cleared.
								//for example, the game described a dog on a pathway, then gave you three options: pet the dog, offer the dog a treat, or run away.
								//in this context, 'headline' would be something like "What do you do with the dog?"
								//it's a convenience thing, in case people don't remember the context of a list of options for whatever reason
								
								//Since this is also called from the "loadOrNG" function, 'headline' in that context is a bunch of player info, so they can decide whether they want to continue or start a new game
								//for that specific formmatting of 'headline', see statsIntoHeadline() in THIS IS DANKKUSHLAND.cpp

	for (int i = 0; i < numOfOptions; i++)	//loop as many times as there are options in the menu 
	{
		if (pos==i){ cout << "->"; }	//print an arrow next to the menu item if that is the currently highlighted item
		else{ cout << "  "; }			//for consistent formatting, print a space next to every item that isn't highlighted. this space is the same length as the arrow, allowing all menu items to stay aligned
		cout << (i+1)<<". "<<options[i] << endl;	//this prints numbers next to actual choices, which are obtained from the options array
	}


}

#endif