#ifndef battleSystem_h
#define battleSystem_h
#include <iostream>
#include "dankLib.h"
#include <stdlib.h> //for sleep()
using namespace std;

class foe{
public:
	string name;
	int maxHP,
		currHP,
		pow;

	//you must assign skills in sequential order. skill2 requires a skill1 or the game can freak out
	string skill1, skill2, skill3;

	//default foe has no skills
	foe()
	{
		skill1 = "none";
		skill2 = "none";
		skill3 = "none";
	}

	//this will be a giant library of all the enemies in the game 
	//OR just the most common enemies
	void createFoe(string in)
	{
		/*if (in == "template")
		{
			maxHP = 0;
			currHP = maxHP;
			pow = 0;

			skill1 = "none";
		}*/

		if (in == "thug")
		{
			name = "Thug";
			maxHP = 10;
			currHP = maxHP;
			pow = 2;
		}

	}
	//On their move, they will randomly choose between skills or basic attacks. They are twice as likely to basic attack as they are to do anything else
	//returns the amount of damage they do
	int theirAction()
	{
		int action = rng();

		if (skill3 != "none")
		{
			if (action >= 4){ return basicAttack(); }
			if ((action > 5) && (action < 8)){}
		}

	}

	int basicAttack()
	{
		int mod = rng1to3(), damage=0, flavor = rng();
		if (mod == 1){ damage = pow - 1; }
		if (mod == 2){ damage = pow; }
		if (mod == 3){ damage = pow + 1; }
		cout << name << " " << endl;
		if (flavor == 1){ cout << "takes a swing!" << endl; }
		if (flavor == 2){ cout << "goes in raw!" << endl; }
		if (flavor == 3){ cout << "performs a standard attack!" << endl; }
		if (flavor == 4){ cout << "goes Chris Brown!" << endl; }
		if (flavor == 5){ cout << "tickles you vehemently!" << endl; }
		if (flavor == 6){ cout << "lets you have it!" << endl; }
		if (flavor == 7){ cout << "knocks a tooth out!" << endl; }
		if (flavor == 8){ cout << "pops you in the nose!" << endl; }
		if (flavor == 9){ cout << "twists your nipples!" << endl; }
		if (flavor == 10){ cout<< "slaps your ass!" << endl; }	
		return damage;
	}
};

//1 for attack, 2 for item, 3 for skill
int getYourAction()
{
	int sel = 0;
	while (sel != 1 || sel != 2 || sel != 3)
	{
		cout << "Enter the number of the action you want to take:" << endl;
		cout << "1: Attack" << endl;
		cout << "2: Use Item" << endl;
		cout << "3: Tech" << endl;
		cin >> sel;
		if (sel != 1 || sel != 2 || sel != 3){ cout << "That ain't no valid option." << endl; }
	}

	return sel;
}



#endif