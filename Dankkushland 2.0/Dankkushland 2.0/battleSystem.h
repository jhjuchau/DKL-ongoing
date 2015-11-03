#ifndef battleSystem_h
#define battleSystem_h
#include <iostream>
#include "dankLib.h"
#include <stdlib.h> //for sleep()
using namespace std;

class skill //an ADT that encapsulates everything a skill can do, including name, number of hits, a power modifier and status inducing flags
{	
	public:
	string name;
	string flavorText;
	int numOfHits;
	int powModifier;
	skill()			//generic null constructor
	{
		name = "null";
		flavorText = "This skill should never be called.";
		numOfHits = 1;
		powModifier = 1;
	};
	skill skillLibrary(string);
};

class foe {
	string name;
	int pow;
	skill skills[3];

	foe(string nameIn, int powIn, string skillsIn[3])
	{
		name = nameIn;
		pow = powIn;
	}
};

skill skill::skillLibrary(string In)	//this function exists to simplify the assigning of skills to 'foes'. It takes a simple string input and generates the corresponding skill.
{
	skill nullSkill;
	return nullSkill;
}


/* DODGING OVERVIEW

	I want to incorporate a dodging method where you type in a string to avoid the attack:
	Thug Attacks!
	DODGE PROMPT -- YOU HAVE #X SECONDS //an actual countdown// 
	3, 2, 1...
	THUGANOMICS
	cin>>dodgeAttempt;


	if you type in THUGANOMICS perfectly within some allotted time, you avoid the effects of the attack. there could be various other methods of dodging attacks, like trivia from the game or real life, that wouldn't require
	a timer

*/

/* PLAYER ATTACK OVERVIEW
	
	I want to make a different playstyle for each player stat, and allow the player to attack via Strength, Intelligence, Charisma, or by Talking.
	Strength attacks would randomly generate to keys that you have to mash. I'd make it so the two keys 

*/
#endif