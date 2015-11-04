//every map is a function, items and character stats are classes
//specialized names contained within ngname()
//ch1(c, you, "outside", "convince");
//ch1 is overloaded to take two, three or four options

//WHEN ADDING A NEW MAP:
//put prototype under the maps comment header
//set you.loc to a unique ID
//add map ID to loadMap(you);
//put map in mapCout() with description
//invissave(you);

#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <stdlib.h> //for sleep()
#include <cstdlib>
#include <conio.h> //for _getch()
#include <Windows.h>//for system("CLS")
#include <fstream>


#include "dankLib.h"
#include "battleSystem.h"
#include "MenusWithArrowKeys.h"

#define UPKEY 72
#define DOWNKEY 80
#define LEFTKEY 75
#define RIGHTKEY 77
#define ENTER 13
#define SPACE 32
#define ESC 27

using namespace std;


class item
{
public:
    string name, description;
};

class stats
{ public:
    string name;
    int currHP, HP,    
        swole, 
        charisma,
        intel,
        skrilla, //range 1 - indefinite
		loc,
		edge;
    item inventory[7];
	//string spellbook[20];
	stats()
	{
		edge = 0;
	}

	//to determine whether events have occurred, will organize as events are scripted
	int event[75];
};


//*******************GAME FUNCTIONS**********************************************
//SYSTEM FUNCTIONS**********************************************
//ch1 is a simple cin command that returns the string for ease of additional events, capitalizes first letter, 
//allows for stats and inventory checking every time user input is allowed
void ch1(string&, stats&, string, string);
void ch1(string&, stats&, string, string, string);
void ch1(string&, stats&, string, string, string, string);
		//called during ch1 if 'S' or 'I' is inputted
	void statCheck(stats&);
	void inventoryCheck(stats&);
void newItem(stats&, string);
void deleteItem(stats&, string);
bool isInInventory(stats&, string);


//SAVE RELATED STUFF********************************************
int initialSaveCheck();
void newGame(stats&);
	void ngName(stats&);
	int ngInput(stats&); //getting stat customization
	void assignStats(stats&, int, int, int, int);
		void ngBools(stats&); //setting all events to default, "undone" state
		void ngItems(stats&);
void save(stats&);
void invissave(stats&);
void load(stats&); 
int loadOrNG(stats&); //runs if a save file is found
	int statsIntoHeadline(stats&, string&); //for use in loadOrNG, calls out name, location (with mapcout()) and skrilla
		string mapcout(stats&); //takes you.loc and calls out the map you're on, right underneath main for easy ammendment
void loadmap(stats&);   //takes you.loc and puts you in that function
void gap();



//MAP PROTOTYPES***********************************************************
void startingFromTheBottom(stats&);
void outside(stats&);
void garden(stats&);
void road(stats&);
	void talkWithSelwyn(stats&);
void evergreenOutskirts(stats&);
void evergreenCity(stats&);
void davidStore(stats&);
	void davidchat(stats&);
	void evStore(stats&);
	bool storeCheck(stats&, int);
void daClub(stats&);
	void hallway(stats&);
	void beeOffice(stats&);
		void hillaryCall();
		void inTheChair();

//undefined
void EVdowntown(stats&);
void chiefKeef(stats&);
void jackieRestaurant(stats&);
void cityHall(stats&);
	void mayorOffice(stats&);
void HWY101(stats&);
	void weedmontHills(stats&);
				void kenzos(stats&);
			void northWeedmont(stats&);
				void jasonChurch(stats&);
				void caruana(stats&);
				void goatFarm(stats&);
			void southWeedmont(stats&);
				void manor(stats&);
				void swamp(stats&);
				void rittenRibbie(stats&);
	void sfSquare(stats&);
		void outsideAlcatraz(stats&);
			void insideAlcatraz(stats&);
				void supplyCloset(stats&);
				void yourCell(stats&);
				void dankOneCell(stats&);
				void prisonYard(stats&);
		void fightClub(stats&);
		void sfDowntown(stats&);
			void sfsu(stats&);
			void dorms(stats&);

	

void test();


int main()
{
	test();
	cout<<"v. 8h 'we github now' Edition" <<endl;
    int first;
    stats you;
    first = initialSaveCheck();
	if (first == 0){load(you);}
    if (first == 1){newGame(you);startingFromTheBottom(you);}
	if (first == 2){loadOrNG(you);}
	system("pause");
    return 0;
}

void test()
{	
	
}


int initialSaveCheck()
{
    ifstream myFile;
    myFile.open("save.txt");
        if (myFile.fail())
					{
						   cout<<"File not found."<<endl<<"Creating new save file..."<<endl;
                           ofstream outputFile;
                           outputFile.open("save.txt");
                           outputFile<<0<<endl;
                           cout<<"New save.txt file created."<<endl;
                           return 1;
					}
            else {cout<<"Save file found."<<endl;
            fstream check;
            check.open("save.txt");
            string c;
            check>>c;
            if (c=="0"){return 1;}
			else {return 2;}
			}//closes outer else
return 0;
}
void newGame(stats& you)
{
	you.swole = 0; you.charisma = 0; you.intel = 0;  you.skrilla = 0;
    char choose = 'N';
    cout<<"Welcome to Dankkushland, where the money's hot and the joints are hotter."<<endl;
	ngName(you);
	int ngInputResult=0;
	while (ngInputResult == 0){ ngInputResult = ngInput(you); } //keep looping until it returns 1


	gap();
	cout<<"They call you "<<you.name<<"."<<endl;
	cout<<"You got "<<you.HP<<" HP."<<endl;
    cout<<"You got "<<you.swole<<" SWOLE."<<endl;
    cout<<"You got "<<you.charisma<<" CHARISMA."<<endl;
    cout<<"You got "<<you.intel<<" SMARTS."<<endl;
    cout<<"You have "<<you.skrilla<<" SKRILLA."<<endl;
    if (you.swole >= 10){cout<<"Damn son, you natty?"<<endl;}
    if (10 > you.swole >= 7){cout<<"You a hambeast man."<<endl;}
    if (you.charisma >= 10){cout<<"Tryna be like Dio, fool?"<<endl;}
    if (10 > you.charisma >= 7) {cout<<"Something clever "<<endl;}
    if (you.intel >= 10){cout<<"NEEEEEEEEEEEEEEEEERD."<<endl;}
    if (10 > you.intel >= 7 ) {cout<<"Damn, been taking them AP classes?"<<endl;}
    if (you.intel <= 1) {cout<<"You hella dumb though.\n"<<endl;}
    system("pause");

    cout<<"\nYou like what you see? (Y/N)"<<endl;
    cin>>choose;
    choose = toupper(choose);
    if (choose == 'Y'){ngBools(you);ngItems(you);save(you);startingFromTheBottom(you);}
    if (choose == 'N')
	{
		you.currHP = 0;
		you.HP = 0;
		you.swole = 0;
		you.charisma = 0;
		you.intel = 0;
		you.skrilla = 0;
		newGame(you);
	}
   }
void ngName(stats& you)
{   char sel;
	cout<<"What's your name, mang? Your real first name doe."<<endl;
	cin>>you.name;
	you.name[0] = toupper(you.name[0]);
	if (you.name == "James" || you.name == "Jam") {cout<<"Damn son too stronk, all stats +100"<<endl; you.swole = 100; you.charisma = 100; you.intel = 100;}
	else if (you.name == "David") {cout<<"Nguyen ('N') or Aribal ('A')? Or some other brother (any other character)?"<<endl;
									cin>>sel; sel = toupper(sel);
									if (sel == 'N'){cout<<"Hella buffets. Hella smash. Hella swole. +7 swole."<<endl; you.swole+=7;}
									else if (sel == 'A'){ cout << "Ayy bruh season three spoilers: Honoka dies. +5 charisma." << endl; you.charisma += 5; }
									else {cout<<"Sick name, "<<you.name<<", +1 to everything."<<endl; you.swole=1; you.charisma=1; you.intel=1; you.skrilla=100;}
	}
	else if (you.name == "Alex")  {cout<<"Jones ('J') or La ('L')? Or some other brother?"<<endl;
									cin>>sel; sel = toupper(sel);
									if (sel == 'J'){cout<<"Your father killed Dante. For that, difficulty is set to MAX."<<endl;}
									else if (sel == 'L'){cout<<"WOOOW. +1 to everything. And +250 skrilla."<<endl;you.intel+=1; you.charisma+=1; you.swole+=1; you.skrilla+=250;}
									else {cout<<"Sick name, "<<you.name<<", +1 to everything."<<endl; you.swole=1; you.charisma=1; you.intel=1; you.skrilla=100;}
	}
	else if (you.name == "Edgar") {cout<<"All that running from la migra made you strong. +5 swole."<<endl; you.swole = 5;}
	else if (you.name == "Greg")  {cout<<"I believe it. +5 Charisma, future hokage."<<endl; you.charisma=5;}
	else if (you.name == "Khanh") {cout<<"Clean up that keyboard and mouse you greasy motherfucker. \n +300 Skrilla, +2 intel"<<endl; you.skrilla = 300; you.intel=2;}
	else if (you.name == "Mike" || you.name == "Michael"){cout<<"Good point. +3 swole, +250 skrilla."<<endl; you.swole=3;you.skrilla=250;}
	else if (you.name == "Andrew"){int x = 0; while (x==0){cout<<"faggot";}}
	else if (you.name == "Eric"){cout<<"How are you playing this? You don't have an N64. +3 charisma, +250 skrilla."<<endl; you.charisma=3; you.skrilla=250;}
	else if (you.name == "Kyle"){cout<<
	  "            /|  /|"<<endl<<
      "           / \| / /|"<<endl<<
      "          \ \| |/ / |"<<endl<<
      "          \ | | / / \\"<<endl<<
      "        .-.) '. `_/"<<endl<<
      "       (.-.   / /"<<endl<<
      "           | ' |"<<endl<<
	  "           |___|"<<endl<<
      "          [_____]"<<endl<<
      "          |     |"<<endl;
	cout<<"YOU CAN'T SEE ME. +5 swole."<<endl; you.swole = 5;}
	else if (you.name == "Joseph") {cout<<"Your next line will be 'Sick Jojo's reference'. Base intel increased by 50."<<endl; you.intel=50;}
	else if (you.name == "Jotaro") {cout<<"Ore ga sabakuu. Base swole increased by 50. "<<endl; you.swole = 50;}
	else if (you.name == "Dio")    {cout<<"Toki wa ugoki desu. Base charisma increased by 50. "<<endl; you.charisma = 50;}
	else if (you.name == "Goku")  {cout<<" "<<endl;}
	else if (you.name == "Chheang"){cout<<"Post this to Holo-gram (c) Duong Inc. +3 charisma, +2 smarts."<<endl; you.charisma = 3; you.intel=2;}
	else if (you.name == "Jackie") {cout<<"Fucking kawaii. -2 swole, +5 charisma."<<endl; you.charisma = 5; you.swole = -2;}
	else if (you.name == "Jason")  {cout<<"Elsie's just okay. \n+5 smarts, but you have lung cancer from smoking, so -3 swole."<<endl; you.intel = 5; you.swole = -3;}
	else if (you.name == "Billy")  {cout<<"The real white man. +1000 skrilla, "<<endl; you.skrilla = 1000;}
	else if (you.name == "Vincent"){cout<<"She hit the floor, next thing you know; shawty got Lo. \n +5 intelligence."<<endl; you.intel=5;}
	else if (you.name == "Mariano"){cout<<"Fucking degenerate waifufag. -3 charisma, +8 charisma"<<endl;you.swole-=3; you.charisma+=8;}
	else if (you.name == "Katie")  {cout<<"My mommy calls me Sean. -2 intelligence, +4 charisma"<<endl; you.intel-=2; you.charisma+=4;}
	else if (you.name == "Matt")   {cout << "Ayyyyyyy" << endl; }
	else if (you.name == "Mark")   {cout<<"You're the mayor of Juke City. +3 to all stats."<<endl; you.charisma=3; you.swole=3; you.intel=3; you.skrilla=300;}
	else if (you.name == "Hillary"){cout<<"Callin' me B-Tier? You must be dumb. -3 intelligence, +3 to everything else."<<endl; you.intel=-3; you.swole=3; you.charisma=3; you.skrilla=300;}
	else if (you.name == "Cindy")  {cout<<"bruddahber gets +5 swole"<<endl; you.swole=5;}
	else if (you.name == "Chelsea"){cout<<"Please stop wearing yoga pants to Alex's. +5 charisma."<<endl; you.charisma=5;}
	else if (you.name == "Randy")  {cout<<"Send me nudies of girls and I'll make you even stronger. +2 swole, +5 charisma"<<endl; you.swole=2; you.charisma=5;
									cout<<"But -1000 skrilla from dating so much."<<endl; you.skrilla=-1000;}
	else if (you.name == "Tiana")  {cout<<"I'm never going to watch that crossdressing show. +3 charisma, +1 swole."<<endl; you.charisma=3; you.swole=1;}
	else if (you.name == "Miku"||you.name=="Hatsune"||you.name=="Luka")  {cout<<"Damn, for having great taste, +5 to everything."<<endl; you.swole=5; you.intel=5; you.charisma=5; you.skrilla=500;}
	else if (you.name == "Bryan"){ cout << "How was hanging out with Amanda? Charisma +5"; you.charisma += 5; }
	else if (you.name == "Cody")   {cout<<""<<endl;}
	else if (you.name == "Rex")    {cout<<" "<<endl;}

	else {cout<<"Sick name, "<<you.name<<". +1 to everything."<<endl; you.swole=1; you.charisma=1; you.intel=1; you.skrilla=100;}
	system("pause");
}
int ngInput(stats& you)
{
	int swin, chin, inin, skin;
	gap();
	cout<<"You've got 10 points, playa. Put them anywhere you want."<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"SWOLE      -- how many plates can you squat? Real men put all 10 here."<<endl;
    cout<<"CHARISMA   -- your street cred and sex appeal."<<endl;
    cout<<"SMARTS     -- sure, if you want to be a nerd."<<endl;
    cout<<"SKRILLA    -- if you a basic bitch, pick pesos over personality."<<endl<<endl;
    cout<<"How many swole points you want?"<<endl;
	cout<<"Each point of swole gives you 5 HP, but you got 20 to start."<<endl;
    cin>>swin;
    cout<<"How much charisma you want?"<<endl;
    cin>>chin;
    cout<<"How much smarts you need?"<<endl;
    cin>>inin;
    cout<<"Want to give up points for that paper? How many?"<<endl;
    cout<<"You start with 500 skrilla, each point is 200 more."<<endl;
    cin>>skin;
    if (swin + chin + inin + skin > 10)
	{
		cout<<"That's too many points, fool. You think you worth all that?"<<endl;
		system("pause");
		gap();
		swin = 0; chin = 0; inin = 0; skin = 0;
		return 0;
	}
    if (swin + chin + inin + skin < 10)
	{
		cout<<"No less than 10 mang. Starving kids out there would love these points."<<endl;
		system("pause");
		gap();
		swin = 0; chin = 0; inin = 0; skin = 0;
		return 0;
	}

	you.swole = you.swole + swin;
	you.HP = 20 + (you.swole * 5);
	you.currHP = you.HP;
	you.charisma = you.charisma + chin;
	you.intel = you.intel + inin;
	you.skrilla = you.skrilla + 500 + (skin * 200);
	you.loc = 0;
	return 1;
}

void ngBools(stats& you)
{
	for (int i = 0; i<75; i++)
	{
		you.event[i]=0;
	}
}
void ngItems(stats& you)
{
	for (int i = 0; i<7; i++)
	{
		you.inventory[i].name="Nothing";
	}
}
void newItem(stats& you, string newItemin)
{
	for(int i=0; i<7; i++)
	{
		if (you.inventory[i].name == "Nothing"){
			you.inventory[i].name = newItemin;
			cout<<you.inventory[i].name<<" placed in slot "<<i+1<<endl;
			return;}
	}
	//if no "Nothing"s found
	string sel;
	cout<<"Your pockets is full."<<endl;
	cout << "Here's whatchu got." << endl;
	inventoryCheck(you);
	cout << "NEW ITEM: " << newItemin << endl;
	cout << "\nPick the item you wanna drop." << endl;
	cin >> sel; 
	if (isInInventory(you, sel) == false && sel!=newItemin)
	{ 
		cout << "That ain't no valid option." << endl;
		cout << "Type that sucka out perfectly." << endl;
		system("pause"); newItem(you, newItemin); 
	}
	else if (isInInventory(you, sel) == true && sel == newItemin)
	{
		char pick='x';
		cout << "Shit fool you got at least two of those." << endl;
		while (pick != 'I' && pick != 'N')
		{
			cout << "Drop the one in your inventory('I'), or the one you're getting now? ('N')" << endl;
			cin >> pick; pick = toupper(pick);
			if (pick != 'I' && pick != 'N'){ cout << "Only 'I' or 'N', fool. Do I gotta spell it out for you?" << endl; }
		}

		if (pick == 'I'){ cout << "You whip out your backpack and chuck that shit." << endl; deleteItem(you, sel); newItem(you, sel); }
		if (pick == 'N'){ cout << "You drop that new shit real quick." << endl; return; }

	}
	else if (isInInventory(you, sel) == true){ cout << "You trashed " << sel << endl; deleteItem(you, sel); newItem(you, newItemin); }
	else if (sel == newItemin){ cout << "You dropped that new shit quick." << endl; return; }
}
bool isInInventory(stats& you, string itemName)
{
	for (int i = 0; i < 7; i++)
	{
		if (you.inventory[i].name == itemName){return true;}
	}
	return false;
}
void deleteItem(stats& you, string itemName)
{
	for (int i=0; i<7; i++)
	{
		if (you.inventory[i].name == itemName){you.inventory[i].name = "Nothing"; cout<<itemName<<" removed from inventory."<<endl;}
	}
}

void save(stats& you)
{
	cout<<"\nSaving..."<<endl;
	fstream save;
	save.open("save.txt");
	save<<you.name<<endl;
	save<<you.loc<<" ";
	save<<you.skrilla<<" ";
	save<<you.HP<<" ";
	save<<you.currHP<<" ";
	save<<you.swole<<" ";
	save<<you.charisma<<" ";
	save<<you.edge<<" ";
	save<<you.intel<<endl;
	for (int i=0; i<75; i++)
	{
		save<<you.event[i]<<" ";
	}
	save<<endl;
	for (int i=0; i<7; i++)
	{
		save<<you.inventory[i].name<<" ";
	}
	save.close();
	cout<<"Save complete!"<<endl;
}
void invissave(stats& you)
{
	fstream save;
	save.open("save.txt");
	save<<you.name<<endl;
	save<<you.loc<<" ";
	save<<you.skrilla<<" ";
	save<<you.HP<<" ";
	save<<you.currHP<<" ";
	save<<you.swole<<" ";
	save<<you.charisma<<" ";
	save<<you.edge<<" ";
	save<<you.intel<<endl;
	for (int i=0; i<75; i++)
	{
		save<<you.event[i]<<" ";
	}
	save<<endl;
	for (int i=0; i<7; i++)
	{
		save<<you.inventory[i].name<<" ";
	}
	save.close();
}
void load(stats& you)
{
	fstream save;
	save.open("save.txt");
	save>>you.name;
	save>>you.loc;
	save>>you.skrilla;
	save>>you.HP;
	save>>you.currHP;
	save>>you.swole;
	save>>you.charisma;
	save>>you.edge;
	save>>you.intel;
	for (int i=0; i<75; i++)
	{
		save>>you.event[i];
	}
	for (int i=0; i<7; i++)
	{
		save>>you.inventory[i].name;
	}
	save.close();
	cout<<"File successfully loaded!"<<endl;
	loadmap(you);
}
void ch1(string& c, stats& you, string str1, string str2)
{
	cin>>c;
	c[0] = toupper (c[0]);
	if (c=="S"){statCheck(you);ch1(c, you, str1, str2);}
	else if (c=="I"){inventoryCheck(you);ch1(c, you, str1, str2);}
	else {if (isValid(c, str1, str2)==false)
		{ch1(c, you, str1, str2);};}
	c[0] = tolower(c[0]);
}
void ch1(string& c, stats& you, string str1, string str2, string str3)
{
	cin>>c;
	c[0] = toupper (c[0]);
	if (c=="S"){statCheck(you);ch1(c, you, str1, str2, str3);}
	else if (c=="I"){inventoryCheck(you);ch1(c, you, str1, str2, str3);}
	else {if (isValid(c, str1, str2, str3)==false)
		{ch1(c, you, str1, str2, str3);};}
	c[0] = tolower(c[0]);
}
void ch1(string& c, stats& you, string str1, string str2, string str3, string str4)
{
	cin>>c;
	c[0] = toupper (c[0]);
	if (c=="S"){statCheck(you);ch1(c, you, str1, str2, str3, str4);}
	else if (c=="I"){inventoryCheck(you);ch1(c, you, str1, str2, str3, str4);}
	else {if (isValid(c, str1, str2, str3, str4)==false)
		{ch1(c, you, str1, str2, str3, str4);};}
	c[0] = tolower(c[0]);
}

void statCheck(stats& you)
{
	cout << "HP:       " << you.currHP << "/" << you.HP << endl;
	cout<<"SWOLE:    "<<you.swole<<endl;
	cout<<"CHARISMA: "<<you.charisma<<endl;
	cout<<"SMARTS:   "<<you.intel<<endl;
	cout<<"SKRILLA:  "<<you.skrilla<<endl;
	cout<<"EDGE:     ";
	if (you.edge <= 0){cout<<"Not edgy at all."<<endl;}
	if (you.edge == 1){cout<<"Only a little edgy."<<endl;}
	if (you.edge == 2){cout<<"Sliiiiiightly edgy."<<endl;}
	if (you.edge == 3){cout<<"Kinda edgy."<<endl;}
	if (you.edge == 4){cout<<"Getting a little bit edgy."<<endl;}
	if (you.edge == 5){cout<<"Halfway to Edgeville"<<endl;}
	if (you.edge == 6){cout<<"Jesus dude you're pretty edgy."<<endl;}
	if (you.edge == 7){cout<<"On the edge of edgy."<<endl;}
	if (you.edge == 8){cout<<"Edgier than Sasuke's kunai."<<endl;}
	if (you.edge == 9){cout<<"Edge level approaching maximum"<<endl;}
	if (you.edge == 10){cout<<"You are the edgelord."<<endl;}
	if (you.edge >  10){gap(); cout<<"You're so edgy you've cut through the game's source code."<<endl;
						system("pause");
						return;}
}
void inventoryCheck(stats& you)
{
	for (int i = 0; i < 7; i++)
	{
		cout<<"Pocket number "<<i+1<<": "<<you.inventory[i].name<<endl;
	}
	cout<<"You currently have "<<you.skrilla<<" SKRILLA."<<endl;
}

int loadOrNG(stats& you)
{
	fstream save;
	string headline;
	string options[2] = { "Yes", "No" };
	char ch2;
	
	statsIntoHeadline(you, headline);
		
	switch (initMenu(headline, options, 2))
	{
		case 1: 
		{
			system("CLS");
			load(you);
			break;
		}

		case 2:
		{
			cout << "Starting all over? All progress is lost. (Y/N)" << endl;	//I specifically left this as a (Y/N) char input to ensure people wouldn't accidentally overwrite their save
			cin >> ch2;
			ch2 = toupper(ch2);
			if (ch2 == 'Y'){ newGame(you); }
			else if (ch2 == 'N'){ loadOrNG(you); }
			else 
			{
				cout << "That ain't gonna fly. Only (Y/N)." << endl;
				system("pause");
				loadOrNG(you);
			}
		}
	}
	
	
							
							 
	return 0;
}
int statsIntoHeadline(stats& you, string& headline)
{
	fstream save;
	save.open("save.txt");
	save>>you.name;
	save>>you.loc;
	save>>you.skrilla;
	save.close();
	headline += "NAME: "; headline += you.name; headline += "\n";
	headline += "LOCATION: "; headline += mapcout(you); headline += "\n";
	headline += "SKRILLA: "; headline += you.skrilla; headline += "\n";
	headline += "Tryna load from this save? \n";
	return 0;
}

void gap()
{
	system("CLS");
}



//WHEN ADDING A NEW MAP, CHANGE THESE**********************************************
void loadmap(stats& you) //takes you.loc and puts you in the function for that map
{
	if (you.loc==0){startingFromTheBottom(you);}
	if (you.loc==1){outside(you);}
	if (you.loc==2){garden(you);}
	if (you.loc==3){road(you);}
	if (you.loc==4){evergreenOutskirts(you);}
	if (you.loc==5){evergreenCity(you);}
	if (you.loc==6){davidStore(you);}
	if (you.loc==7){daClub(you);}
	if (you.loc == 8){ hallway(you); }
	if (you.loc == 9){ beeOffice(you); }
	if (you.loc == 10){ EVdowntown(you); }
	if (you.loc == 11){ chiefKeef(you); }
	if (you.loc == 12){ jackieRestaurant(you); }
	if (you.loc == 13){ cityHall(you); }
	if (you.loc == 14){ mayorOffice(you); }
	if (you.loc == 15){ HWY101(you); }
	if (you.loc == 16){ inTheChair(you); }
}

string mapcout(stats& you) //calls out the map when offering you your save file
{
	if (you.loc == 0){return "Starting from the bottom.";}
	if (you.loc == 1){return "Outside Your Crib";}
	if (you.loc == 2){return "Your Kush Garden.";}
	if (you.loc == 3){return "Kush Valley Road";}
	if (you.loc == 4){return "Outskirts of Evergreen City";}
	if (you.loc == 5){return "Evergreen City Square";}
	if (you.loc == 6){return "David Nguyen's Store";}
	if (you.loc == 7){return "Da Club";}
	if (you.loc == 8){ return "Hallway to Bee's Office"; }
	if (you.loc == 9){ return "Bee's Office"; }
	if (you.loc == 10){ return "Evergreen City: Downtown"; }
	if (you.loc == 11){ return "Evergreen City: Chief Keef's Apartment"; }
	if (you.loc == 12){ return "Evergreen City: Jackie's Restaurant"; }
	if (you.loc == 13){ return "Evergreen City: City Hall"; }
	if (you.loc == 14){ return "Evergreen City: Mayor's Office"; }
	if (you.loc == 15){ return "Highway 101"; }
	if (you.loc == 16){ return "In The Chair."; }
	if (you.loc == 17){ return "Kenzo's"; }
	if (you.loc == 18){ return "Weedmont Hills: North"; }
	if (you.loc == 19){ return "Weedmont Hills: Jason's Church"; }
	if (you.loc == 20){ return "Weedmont Hills: Caruana Factory"; }
	if (you.loc == 21){ return "Weedmont Hills: Julian's Goat Farm"; }
	if (you.loc == 22){ return "Weedmont Hills: South"; }
	if (you.loc == 23){ return "Weedmont Hills: The Manor"; }
	if (you.loc == 24){ return "The Swamp"; }
	if (you.loc == 25){ return "Weedmont Hills: Ritten Ribbie"; }
	if (you.loc == 26){ return "San Fransisco Square"; }
	if (you.loc == 27){ return "San Fransisco: Outside Alcatraz"; }
	if (you.loc == 28){ return "San Fransisco: Alcatraz"; }
	if (you.loc == 29){ return "San Fransisco: Alcatraz Supply Closet"; }
	if (you.loc == 30){ return "San Fransisco: Alcatraz Cell"; }
	if (you.loc == 31){ return "San Fransisco: ???"; }
	if (you.loc == 32){ return "San Fransisco: Alcatraz Yard"; }
	if (you.loc == 33){ return "San Fransisco: Fight Club"; }
	if (you.loc == 34){ return "San Fransisco: Downtown"; }
	if (you.loc == 35){ return "San Fransisco: SFSU"; }
	if (you.loc == 36){ return "San Fransisco: SFSU Dorms"; }
	if (you.loc == 37){ return "out of bounds"; }
	if (you.loc == 38){ return "out of bounds"; }
	if (you.loc == 39){ return "out of bounds"; }
	if (you.loc == 40){ return "out of bounds"; }

	return "out of bounds";
}


//MAP DEFINITIONS************************************************************

void startingFromTheBottom(stats& you)
{
	you.loc = 0;
	if (you.event[0]==0)
	{
		you.event[0]=1;
		cout<<"\n\nYou roll over on your bed and look outside. It's pitch black. \nBut your sundial says it's morning!"<<endl;
		system("pause");
		cout<<"\n\nThere's smoke in the sky! But not just any smoke!"<<endl;
		cout<<"That's your stash of Grand Daddy Purple! Some jive turkies must've made off with that premium bud!"<<endl;
		cout<<"No whack ass busta is gonna get away with jacking your stash!"<<endl;
		system("pause");
		cout<<"\n\nYou get on up and take a step into your room."<<endl;
		cout<<"Your hella fly dog, Gemini, strolls on up and gives you props."<<endl;
		invissave(you);
		system("pause");
		gap();
		cout<<"\nWords in ALL CAPS are actions you can do. Type 'em in if you feel it, brutha."<<endl;
		if (you.name=="Jackie"||you.name=="Hillary"||you.name=="Chelsea"||you.name=="Taylor"||you.name=="Cindy"||you.name=="Carol"){cout<<"my b, sistahs too."<<endl;}
		if (you.name=="Greg"||you.name=="Naruto"){cout<<"Believe it."<<endl;}
		cout<<"Any time you can do anything, you can check your STATS(shortcut 'S') or your    inventory (shortcut 'I') too."<<endl;
		cout<<"**Options labelled (SPECIAL) will impact future events in the game differently**"<<endl;
		system("pause"); gap();
	}
	
	gap();
	
	cout<<"\nYou can go OUTSIDE, or CHECK your email."<<endl;
	if (you.event[0] != 2){ cout << "You can also CONVINCE Gemini to come with you." << endl; }
	cout<<"You don't hafta ride caps lock. Type your option lowercase."<<endl;
	
	string c;
	if (you.event[0] != 2){ ch1(c, you, "outside", "convince", "check", "study"); }
	else { ch1(c, you, "outside", "check", "study"); }

	if (c == "convince")
	{

		if (isInInventory(you, "Gemini")==true){cout<<"Don't trip. You already got Gemini."<<endl;
												system("pause");
												gap();
												startingFromTheBottom(you);}

		if (you.charisma >=6){
			gap();
			cout<<"Gemini's miring all that Charisma."<<endl;
			cout<<"Gemini decides to kick it with you."<<endl;
			cout<<"You obtained Gemini!"<<endl;
			newItem(you, "Gemini");
			you.event[0] = 2;
			invissave(you);
			system("pause");
			gap();
			startingFromTheBottom(you);}

		else
		{
			gap();
			int gemVal = 8  - you.charisma;
		     cout<<"Gemini cocks an eyebrow at you."<<endl;
			 cout<<"'Bruh, you serious? You ain't shit.'"<<endl;
			 cout<<"Mad disrespect. Guess you need, like, "<<gemVal<<" more CHARISMA."<<endl;
			 system("pause");gap();
			 startingFromTheBottom(you);
		}
	}

	if (c=="outside"){outside(you);}
	if (c == "check"){
		if (you.name == "James" || you.name == "Jam" || you.name == "Randy" || you.name == "Bryan")
		{
			cout << "'Welcome, " << you.name << ".' your computer screen reads." << endl;
			cout << "You have 396 unread emails from 396 different honies." << endl;
			cout << "You roll your eyes and sigh. Just another day..." << endl;
			cout << "You look back at your monitor, where the count is now 420." << endl;
			cout << "You log off and walk back into your room." << endl;
			system("pause");
			gap();
			startingFromTheBottom(you);
		}


		else
		{
				cout << "Nobody tryna holla at you right now." << endl;
				system("pause"); gap();
				startingFromTheBottom(you);
		}
	}

	
	if (c == "study"){
		cout << "Here's your fucking study option, Mike, you enormous faggot." << endl;
		cout << "Your intelligence went up by 2, because you fucking need some." << endl;
		you.intel += 2;
		system("pause"); gap();
		startingFromTheBottom(you);
	}

	system("pause");
	return;
}

void outside(stats& you)
{
	string c;
	int ch=0;
	you.loc = 1;
	invissave(you);
	
	if (you.event[1]==0)
	{
		you.event[1]=1;
		gap();
		cout<<"You step outside your house for the first time."<<endl;
		cout<<"The scent of charred bud drifts past your sniffer."<<endl;
		cout<<"You live in Evergreen Valley, so the smell of that good is normal."<<endl;
		cout<<"But today it just makes you shake your head with anger."<<endl;
		system("pause");

		gap();
		cout<<"As you look toward the road, you see your homie David Aribal."<<endl;
		cout<<"It's not even 9 in the morning, but you can tell he's faded."<<endl;
		cout<<"But he lives over in Weedmont Hills. Why's he over here...?"<<endl;
		invissave(you);
	}
		cout<<"You can go to your Kush GARDEN, go back INSIDE, or get on the ROAD."<<endl;
		if (you.event[3]==0){cout<<"You can also chill with DAVID."<<endl; ch1(c, you, "garden", "david", "road", "inside");}
		else {ch1(c, you, "garden", "road", "inside");}

		if (c=="garden"){garden(you);}

		if (c=="david")
			{
				if (you.event[3]==0){
				cout<<"You stroll on up to David and bump knuckles."<<endl;
				cout<<"'What's good, cuh? You smell that shit?' David asks as he sucks his joint."<<endl;
				cin.get();
				cout<<"'Yeah, that's my GDP, dawg.' you say, grinding your teeth."<<endl;
				cout<<"'Shit fool I hella failed Econ, but that smells like your Grand Daddy Purple.'"<<endl;
				cout<<"'Need any help getting it back?' David asks."<<endl;
				system("pause");
					while ( ch!=1 && ch!=2 &&  ch!=3)
					{
						gap();
						cout<<"Enter the number for the option."<<endl;
						cout<<"1: 'Shit man, you a real brother. I'd love your help.'"<<endl;
						cout<<"2: 'You sure you ain't tryna skiv summa my bud?'"<<endl;
						cout<<"3: 'Fuck you. I work alone.'"<<endl;
						cin>>ch;
						if (ch!=1 && ch!=2 && ch!=3){cout<<"Pick a valid number, fool."<<endl;}
					}
					gap();

					if (ch==1)
				{
					gap();
					cout<<"'Aight, I got you, breh.' David says, bumping your fist with his."<<endl;
					cout<<"Your street smarts tell you David's really on your side."<<endl;
					cout<<"You earned 2 Charisma!"<<endl;
					you.charisma+=2;
					you.event[3]=1;
					system("pause");
					gap();
					cout<<"'Imma go look for clues. TFTI, breh.' he calls, smiling."<<endl;
					cout<<"David climbs into his Benz and drives down the road."<<endl;
					cout<<"You're glad you stayed his friend."<<endl;
					system("pause");
					gap();
					outside(you);
				}


					if (ch==2)
				{   gap();
					cout<<"'Shit, fool, don't grill a homie.' David says, raising his hands."<<endl;
					cout<<"'I just gotta know who's on my side.' you say, eyes lowered."<<endl;
					cout<<"You realize that in defense of your kush, you can't even trust your friends."<<endl;
					cout<<"'I gotchu, man. I wouldn't take a brother's bud.' David says, nodding."<<endl;
					cout<<"'Imma go look for clues right now.' he says, climbing into his Benz."<<endl;
					system("pause");
					gap();
					cout<<"He drives away, but he ain't smiling. You can tell he knows you doubt him."<<endl;
					cout<<"But you stayed on your toes. Smart shit. +2 smarts."<<endl;
					you.event[3]=2; you.intel+=2; gap();
					outside(you);
				}
					if (ch==3)
				{
					cout<<"'Wooow. No invite.' David calls, climbing into his Benz."<<endl;
					cout<<"As he drives off, you feel hella manly. +2 swole."<<endl;
					cout<<"Your EDGE level has increased."<<endl;
					you.edge+=1;
					you.event[3]=3; you.swole+=2; 
					system("pause"); gap();
					outside(you);
				}
			}
		}

		if (c=="road"){road(you);}

		if (c=="inside"){startingFromTheBottom(you);}
}

void garden(stats& you)
{
	if (you.event[2]==3) 
	{
		gap();
		  cout<<"You've already cut Ol' Reliable's crop for this season."<<endl;
		  cout<<"Sorry, "<<you.name<<", but she won't grow no more for this playthrough."<<endl;
		  cout<<"You walk back to your stoop."<<endl;
		  system("pause");
		  cout<<endl<<endl;
		  outside(you);
	}

	string c;
	you.loc=2;
	invissave(you);
	int l = you.name.length();
	
			gap();
			cout<<"You stroll on down a gravel path that leads to your kush garden."<<endl;
			cout<<"Behind a purple picket fence lies acres of budding kush."<<endl;
			cout<<"You rest both hands on the fence, gold-and-diamond rings that spell your name   glistening in the sun."<<endl;
			if (l>10) {cout<<"Your toe rings sparkle the rest of your longass name."<<endl;}
			system("pause");
			gap();
			cout<<"Your kush farm is legendary for its quality. It stretches for miles."<<endl;
			cout<<"You donate 90% of your crop to a local orphanage, and sell another 9%, so you   can only take from one plant."<<endl;
			cout<<"You look at your very first plant with nostalgia: Ol' Reliable."<<endl;
			cout<<"Ol' Reliable's been getting you high since you was six."<<endl;
			if (you.event[2]==0){cout<<"But it ain't ripe this season. If you wait, it'll be even danker."<<endl;}
	if (you.event[2]==2){cout<<"You been patient, mayn. Ol' Reliable's bearing some dank fruit."<<endl;}
	system("pause"); gap();
	cout<<"You can TAKE some growing Reliable, or LEAVE."<<endl;
	
	ch1(c, you, "take", "leave");

	if (c=="take")
	{
		if (you.event[2]==0 || you.event[2]==1)
		{
		gap();
		cout<<"You gently snip enough for a spliff off of Ol' Reliable."<<endl;
		cout<<"You cross yourself, respecting the bud's sacrifice."<<endl;
		newItem(you, "UnripeReliable");
		system("pause");
		cout<<endl;
		cout<<"Wiping away tears, you turn from your plant and head back to your stoop."<<endl<<endl;
		you.event[2]=3;
		invissave(you);
		outside(you);
		}

		if (you.event[2]==2)
		{
			gap();
			cout<<"Waiting paid off, mang. That nostalgic scent tickles your nose."<<endl;
			cout<<"After snipping off some tender bud, you pocket it and walk away with a smile."<<endl;
			system("pause");
			gap();
			cout<<"A smile, and a happy tear trickles down your face."<<endl<<endl;
			system("pause");
			newItem(you, "PremiumReliable");
			you.event[2]=3;
			invissave(you);
			outside(you);
		}
	}


	if (c=="leave")
	{
		gap();
		cout<<"Lovin' that patience, mang. You head back to your stoop."<<endl;
		you.event[2] = 1;
		system("pause"); gap();
		outside(you);
	}

}

void road(stats& you)
{   string c;
	int ch=0;	
	you.loc = 3;
	invissave(you);
	if (you.event[4]==0)
	{
		gap();
		cout<<"You step on to the path toward Evergreen City."<<endl;
		cout<<"Wild, uncultivated kush grows between the cracks in the sidewalk."<<endl;
		cout<<"After a minute of walking, you see skyscrapers rising above the horizon."<<endl;
		cout<<"Smoke pours out of every window. You smile. This is your city."<<endl;
		system("pause");
		gap();
		cout<<"As you're walking, you go through the list of people you suspect to have stolen your GDP."<<endl;
		if (you.event[3]==2 || you.event[3]==3){cout<<"You still slightly doubt David Aribal. Why was he so close to your house?"<<endl;}
		else {cout<<"You don't believe it was David Aribal. Even though he was right next to your crib, he just doesn't seem like a guy who'd play a brother like that."<<endl;}
		cout<<"It could have been Eric. That guy's always so friendly. Maybe it's a fake personality to guise his real intentions..."<<endl;
		cout<<"But if you start thinking like that, everyone's a suspect. Do you..."<<endl;
		while ( ch!=1 && ch!=2 &&  ch!=3)
					{
						cout<<"1: Trust all your friends. They all you got."<<endl;
						cout<<"2: Stay on your toes. Never know when a friend gon' switch sides."<<endl;
						cout<<"3: Work alone. That Grand Daddy Purple is good enough to make the realest G into a T"<<endl;  //think of a better word
						cin>>ch;
						if (ch!=1 && ch!=2 && ch!=3){cout<<"Pick a valid number, fool."<<endl;}
					}
					gap();

					if (ch==1)
				{
					gap();
					cout<<"You decide to trust all your friends."<<endl;
					if (you.event[3]==2||you.event[3]==3){cout<<"Except David Aribal. Fuck that guy."<<endl;}
					cout<<"Homies is homies. You got faith in 'em."<<endl;
					cout<<"+3 to charisma, -1 smarts for bein' naive."<<endl;
					you.charisma+=3; you.intel-=1;
					you.event[4]=1;
					system("pause");
					gap();
					
				}

					if (ch==2)
				{  
					gap();
					if (you.event[3]==2){cout<<"Yeah, you a middle of the road kinda playa."<<endl;}
					cout<<"GDP is good bud. Can't go around thinkin' nobody ain't thought of liftin' that shit."<<endl;
					cout<<"+1 to your street smarts. -1 to swole for sitting on a fence all day."<<endl;
					you.intel+=1; you.swole-=1; you.event[4]=2;
					system("pause");
					gap();
				}
					
					if (ch==3)
				{
					cout<<"You reach up and touch your slashed Hidden Leaf headband."<<endl;
					cout<<"Your friends have done nothing but been a burden, anyway."<<endl;
					cout<<"Your EDGE level has increased."<<endl;
					newItem(you, "RogueNinjaHeadband");
					you.event[4]=3;
					you.edge+=2;
					save(you);
					system("pause");
					gap();
				}
			}


	invissave(you);
	if (you.event[5]==0){
		cout<<"While you're rollin' by, you notice some angry-lookin' fools having a chit-chat with your friend Jackie."<<endl;
		cout<<"Jackie don't look like she can handle herself."<<endl;
		cout<<"You can ignore her and go into TOWN or your HOUSE, or you can HELP a sistah out."<<endl;
		ch1(c, you, "town", "help", "house");
		if (c=="town"){cout<<"Damn, fool, ignoring Jackie getting wrecked? Your EDGE level has increased."<<endl;
						cout<<"You walk towards the outskirts of Evergreen City, not even noticing what happens to Jackie."<<endl;
						system("pause"); gap();
						you.edge+=1; you.event[5]=1;
						evergreenOutskirts(you);}

		if (c=="house"){cout<<"Damn, fool, ignoring Jackie getting wrecked? Your EDGE level has increased."<<endl;
						cout<<"You walk back towards your house, not even noticing what happens to Jackie."<<endl;
						system("pause"); gap();
						you.edge+=1; you.event[5]=1; outside(you);}

		if (c=="help")
		{
					gap();
					   cout<<"You walk up to them fools and look at Jackie."<<endl;
				       cout<<"'Hey, these fools giving you trouble?' you say, glancing dismissively at them."<<endl;
					   cout<<"'... four shipments lost in the sewers last week...'"<<endl;
					   cout<<"... Yo, what did you just hear from that dude? Jackie's in the game now?"<<endl;
					   system("pause"); gap();
					   cout<<"One of these fools has piercings all over and a black trenchcoat, and the other is just plain. They're both sizing you up."<<endl;
					   if (you.swole>8){cout<<"They scrawny, though. You swole enough to take 'em both."<<endl;}
					   else {cout<<"You don't think you're swole enough to take both of them, but you brave enough  to try."<<endl;}
					   cout<<"Jackie looks a little nervous, like a Oak-Town brotha 'round the cops."<<endl;
					   system("pause");
					   gap();
					   cout<<"Everyone else stays silent. The air got this weird tension."<<endl;
					   cout<<"'What's goin' on here, Jackie?' you ask, one eyebrow cocked like a .45."<<endl;
					   cout<<"Jackie sighs and gives you a look. It's a strange look. Like pity."<<endl;
					   cout<<"'I'm sorry.' says Jackie. And that innocent voice makes you want to believe it."<<endl;
					   cout<<"Jackie starts reaching into her purse, not breaking your eye contact."<<endl;
					   system("pause");
					   gap();
					   cout<<"Shit, man, something's going down. How do you react?"<<endl; ch=0;


					   while ( ch!=1 && ch!=2 &&  ch!=3 && ch!=4 && ch!=5)
					{
						
						cout<<"1: Take Shrapnel-Face hostage         --    SWOLE REQUIRED."<<endl;
						cout<<"2: Talk This Shit Out                 --    INTELLIGENCE REQUIRED"<<endl;
						cout<<"3: Start Running"<<endl; 
						if (isInInventory(you, "Gemini") == true){cout<<"4: Rush 'em with Gemini."<<endl;
							 if (isInInventory(you, "UnripeReliable") == true) cout<<"5: Offer them your Unripe Reliable (SPECIAL)"<<endl;}
						else {if (isInInventory(you, "UnripeReliable") == true) cout<<"4: Offer them your Unripe Reliable (SPECIAL)"<<endl;}
						cin>>ch;
						if (ch!=1 && ch!=2 && ch!=3 && ch!=4 && ch!=5){cout<<"Pick a valid number, fool."<<endl;}
					}
					gap();

					if (ch==1)
				{
					gap();
					if (you.swole >=5){cout<<"It doesn't take much swole to get Shrapnel-Face into a headlock."<<endl;
									   cout<<"You turn and face Jackie. 'What the fuck is going on witchu?' you yell."<<endl;
									   cout<<"'Let him go! You don't know what you're getting into!' Jackie yells, voice still kawaii."<<endl;
									   cout<<"'Tell me what the fuck is going on, and you'll get this boy back!'"<<endl;
									   cout << "Jackie and Plainboy turn and run. 'See if I care!' she yells." << endl;
									   system("pause");
									   gap();
									   talkWithSelwyn(you);
									   cout<<"You carefully think about what you would've done next time."<<endl;
									   cout<<"You should've dropped Cena's Stepover Toehold Facelock on that puss."<<endl;
									   cout<<"Reflecting on your efforts earned you +2 intelligence. Good work, playa."<<endl; you.intel+=2;
									   you.event[5]=2;
									   system("pause");
									   gap();
					}//close swole success

					else {cout<<"You try to grab Shrapnel-Face, but his skinny limbs slip from your pansy ass grip."<<endl;
						  cout<<"'Are you retarded?' Jackie says, genuinely concerned. You feel hella dumb for trying that."<<endl;
						  cout<<"Plainboy and Shrapnel-Face shove you to the ground and kick the shit out of you."<<endl;
						  cout<<"After you're sufficiently fucked up, Jackie signals them to stop and leans towards your ear."<<endl;
						  cout<<"'Just stay out of this, "<<you.name<<".' Jackie whispers. They turn and walk toward the city."<<endl;
						  system("pause");
						  gap();
						  cout<<"You knew you weren't swole, but you got some sick-looking scars for trying to fight them."<<endl;
						  cout<<"+3 charisma, -3 intelligence. You lost 5 HP, too. Ouch."<<endl; you.charisma+= 3; you.intel-=3; you.currHP-=5;
						  cout<<"When did Jackie become "<<endl;
							}//close swole fail

					system("pause");
					gap();
					
				}

					if (ch==2)
				{  
					gap();
					if (you.intel >=5){cout<<"'Ayy, this whole situation ain't nothing we can't resolve with words.'"<<endl;
										  cout<<"'Sorry, "<<you.name<<", but I don't wanna.' Jackie says, dead innocently."<<endl;
										  cout<<"'C'mawn girl, we can figure this shit out.' you say."<<endl; 
										  cout<<"You feel yourself start to sweat as she fondles whatever is in her purse."<<endl;
									      system("pause");
										  gap();
										  cout<<"'Jackie, I can hook you up with Khandiel.' you say, desperately reaching."<<endl;
										  cout<<"Jackie stops dead in her tracks, hand still in her purse. She thinks hard."<<endl;
										  cout<<"'...Talk to him for me, okay? But don't make it obvious!' she says, laughing    nervously."<<endl;
										  cout<<"She motions for the two knuckas to follow her and they start traipsing over to  Evergreen City."<<endl;
									      system("pause");
											gap();
											cout<<"You thought on your toes; good shit mayn. +2 smarts, +1 charisma."<<endl; you.intel+=2; you.charisma +=1;
											cout<<"But when did Jackie get so metal...?"<<endl; you.event[5]=5;
											system("pause");
											gap();}
					else				{cout<<"'Ayy, this whole situation ain't nothing we can't resolve with words.'"<<endl;
										  cout<<"'Sorry, "<<you.name<<", but I don't wanna.' Jackie says, dead innocently."<<endl;
										  cout<<"'C'mawn girl, we can figure this shit out.' you say."<<endl; 
										  cout<<"You feel yourself start to sweat as she fondles whatever is in her purse."<<endl;
									      system("pause");
										  gap();
											cout<<"'I could hook you up with Tran-Do.' you say, and realize how much of a cabron you are."<<endl;
											cout<<"Jackie stares at you blankly, like you just failed an intelligence stat check."<<endl;
											cout<<"She shakes her head, takes her hand out of her purse and motions her boys to fuck you up."<<endl;
											cout<<"You're so stunned by how retarded that was that you can't put up much of a fight."<<endl;
											cout<<"After you've been turned into baby food, they turn and walk towards Evergreen City."<<endl;
											system("pause");
											gap();
											cout<<"Like a Saiyan, you grow stronger every time you get shit on. +3 swole."<<endl;
											cout<<"But you also lost 8 HP and realize how dumb you really are. (-3 intelligence)"<<endl;
											cout<<"You dust off your slick cheetah print pants and wonder how deep this rabbit hole goes."<<endl;
											you.event[5]=2;
											you.swole+=3; you.intel-=3; you.currHP-=8;}
					system("pause");
					gap();
				}
					
					if (ch==3)
				{
					gap();
					cout<<"You turn your ass around and run. You don't see anything that happens, but you hear them running behind you."<<endl;
					cout<<"'Get back here, "<<you.name<<"!' you hear Jackie yell with a killer's voice."<<endl;
					cout<<"But nah, you keep on running. You duck in some bushes and lose 'em."<<endl;
					cout<<"You come back out after they give up. You lost 3 charisma, but burning those calories earned you 2 swole."<<endl;
					you.charisma-=3; you.swole+=2;
					system("pause");
					gap();
					cout<<"You dust off that sick suede jacket you wearin and look down the empty road."<<endl;
					cout<<"What was going on with Jackie? When'd she break bad?"<<endl;
					you.event[5]=3;
					system("pause");
					gap();
				}
					if (ch==4)
				{
					if (isInInventory(you, "Gemini")==true && isInInventory(you, "UnripeReliable")==false)
					{
						cout << "You blow your dog whistle, lungs strengthened by decades of kush." << endl;
						cout << "Gemini jumps out from the trees and bites the shrapnel off of Shrapnel-Face's face." << endl;
						cout << "Gemini turns and growls at the other two, but they turn and run towards Evergreen City." << endl;
						system("pause"); gap();
						talkWithSelwyn(you);
					}

					else if (isInInventory(you, "Gemini")==false && isInInventory(you, "UnripeReliable")==true)
					{
						cout<<"You remember you plucked that good shit early, reach into your pocket and pull out Ol' Reliable."<<endl;
						cout<<"'Ey, Jackie, you still light up? This shit's pretty dank.' you say, holding it out to her."<<endl;
						cout<<"Jackie's eyes widen. She knows you got the best shit. She motions for Plainboy to take that bud from you."<<endl;
						cout<<"Jackie takes a long smell of it, nods, and slides it into her purse. 'Don't follow us.' she says."<<endl;
						cout<<"She snaps her fingers and they all turn and walk toward Evergreen City."<<endl;
						system("pause"); gap();
						deleteItem(you, "UnripeReliable");
						cout<<"You lost Ol' Reliable, but you ain't trippin'. At least you made it out of there."<<endl;
						cout<<"The fuck's with Jackie, though? That girl's badder than the Persona 4 Golden anime."<<endl;
						you.event[5]=4;
						system("pause"); gap();
					}

					else {cout<<"Pick a valid number, fool."<<endl; ch=0;}

				}
					if (ch==5)
				{
					if (isInInventory(you, "Gemini")==true && isInInventory(you, "UnripeReliable") == true)
					{
						cout<<"You remember you plucked that good shit early, reach into your pocket and pull out Ol' Reliable."<<endl;
						cout<<"'Ey, Jackie, you still light up? This shit's pretty dank.' you say, holding it out to her."<<endl;
						cout<<"Jackie's eyes widen. She knows you got the best shit. She motions for Plainboy to take that bud from you."<<endl;
						cout<<"Jackie takes a long smell of it, nods, and slides it into her purse. 'Don't follow us.' she says."<<endl;
						cout<<"She snaps her fingers and they all turn and walk toward Evergreen City."<<endl;
						system("pause"); gap();
						deleteItem(you, "UnripeReliable");
						cout<<"You lost Ol' Reliable, but you ain't trippin'. At least you made it out of there."<<endl;
						cout<<"The fuck's with Jackie, though? That girl's badder than the Persona 4 Golden anime."<<endl;
						you.event[5]=4;
						system("pause"); gap();
					}
					else {cout<<"Pick a valid number, fool."<<endl; ch=0;}
				}
			}
					   
					    invissave(you);
	}

//end if (event[5] == 0)
	
		cout<<"You walk down the dusty road between your house and Evergreen City."<<endl;
		if (you.event[5]==1){cout<<"You notice blood where Jackie was talking to those guys earlier. Damn."<<endl;}
		cout<<"You can go HOME or head towards TOWN."<<endl;
		ch1(c, you, "home", "town");
		if (c=="home"){outside(you);}
		if (c=="town"){evergreenOutskirts(you);}
	}

void talkWithSelwyn(stats& you)
	{
		int choose=0;
		cout << "'H-hey man, we can talk this out.' Shrapnel-face stutters, bleeding from his smokesucker." << endl;
		cout << "You crack your knuckles. 'Talkin' ain't my thing.'" << endl;
		cout << "You grab him by the collar and lift him off the floor." << endl;
		cout << "'W-wait! I can give you these slick Golden Sneakers!" << endl;
		cout << "You cock an eyebrow, but the grease on his jacket is making your fingers slip." << endl;
		cout << "You only have one thing to talk about with this guy before he slips away." << endl;
		system("pause"); gap();
		
		while (choose != 1 && choose != 2 && choose != 3)
		{
			cout << "Enter the number of the option you choose." << endl;
			cout << "1: Take his Golden Sneakers. (SPECIAL)" << endl;
			cout << "2: Interrogate him about your Granddaddy Purple. (SPECIAL)" << endl;
			cout << "3: Interrogate him about Jackie's behavior. (SPECIAL)" << endl;
			if (choose != 1 && choose != 2 && choose != 3){ cout << "Best enter a valid option" << endl; }

			if (choose == 1)
			{
				cout << "'Lemme see these sneaks, punk,' you spit, shaking him." << endl;
				cout << "'R-right here! He says, pulling a pair of Gold Air Jordans from his trenchcoat." << endl;
				cout << "The moment you snatch them from his hands, he runs off towards the city." << endl;
				cout << "You examine them closely, and to your surprise, they're actually solid gold." << endl;
				cout << "Looks like they ain't good for ballin', but must be worth hella skrilla." << endl;
				you.event[5] = 2;
				newItem(you, "GoldAirJordans");
				system("pause");
				
			}

			if (choose == 2)
			{
				cout << "You shake your head. 'I don't need sneaks. I need information." << endl;
				cout << "You seen this smoke in the sky? That's my Grand Daddy purple.'" << endl;
				cout << "'Know anything about the flatfoots that stole it?' you say, shaking him." << endl;
				cout << "'Y-yeah! I do!' he whimpers. 'They told me it's to ressurrect the Dank One!'" << endl;
				cout << "You roll your eyes. 'More like the Fake One. Lemme show you how much I believe.'" << endl;
				cout << "After beating him up, he limps toward the city as fast as his scrawny legs will take him." << endl;
				cout << "You down a protein shake. Sick workout. +3 swole" << endl;
				you.event[5] = 3;
				you.swole += 3;
				system("pause");
			}

			if (choose == 3)
			{
				cout << "You shake your head. 'I don't need sneaks. I need information.'" << endl;
				cout << "What the hell's up with Jackie? She's never been this cold.' you shout at his tearstained mess of a face." << endl;
				cout << "'S-she never been the same since Jessa got gatted by those g-goons in Weedmont H-hills..." << endl;
				cout << "Your grip loosens and your face goes blank. Jessa got blasted...?" << endl;
				cout << "Shrapnel-face squirms away and starts running towards the city." << endl;
				cout << "You stand in place, processing this information. Damn." << endl;
				cout << "This insider info gives you +2 smarts."; you.intel += 2; you.event[5] = 6;
				system("pause");
			}
		}
		gap();
	}

void evergreenOutskirts(stats& you)
{
	string c;
	you.loc = 4;
	invissave(you);
	if (you.event[6]==0){
	cout<<"You step up to the tall stone walls and mile-long moat of Evergreen City."<<endl;
	cout<<"The familiar scents of Northern Lights and Lemon Haze drift in from the giant opening at the wall's center."<<endl;
	cout<<"The only way into the city is over a mile-long drawbridge."<<endl;
	cout<<"It's raised up every night to prevent the Dank One from getting inside."<<endl;
	cout<<"That's fairy tales, doe, you think to yourself. The Dank One never existed; no one's ever seen it. The wall's just there as a superstition."<<endl;
	you.event[6]=1;
	system("pause"); gap();
	cout<<"Hundreds of people walk the drawbridge in and out at all times. It's the busiest city in Dankkushland, after all."<<endl;
	cout<<"The moat's only feet away from the drawbridge, so kids jump straight from the bridge and swim in the moat."<<endl;
	cout<<"It's a good life, and a good city."<<endl;
	system("pause"); gap();
	}//close event[6]==0

	cout<<"You stand outside Evergreen City's walls. The drawbridge is down, welcomin' you."<<endl;
	cout<<"You can turn go down the ROAD to your crib, look into the MOAT, check that door-shaped BUSH, or go into TOWN."<<endl;
	ch1(c, you, "road", "moat", "bush", "town");
	if (c=="road"){road(you);}
	if (c=="bush"){cout<<"It's just a bush, you conclude. Just because it's door-shaped don't mean it's special."<<endl; evergreenOutskirts(you);}
	if (c=="moat"){cout<<"The water's clearer than the ice on your knuckles. Kids is down there, splashing and playing and shit."<<endl;
				   cout<<"You remember fondly when you were a little thug, playin' with your homies, too."<<endl;
				   cout<<"A smile creeps onto your face. But then you remember why you're here, and you put your mean mug back on."<<endl;
				   system("pause"); gap(); evergreenOutskirts(you);}
	if (c=="town")
	{
		int x=rng();cout<<"You start makin' the mile long walk across Evergreen City's drawbridge. On the  path, you see ";
		if (x>=8){cout<<"Matt, who flaked on being in the game."<<endl;}
		if (x==7||x==6){cout<<"Chheang, wearing a lab coat and muttering about holograms and dreams. He walks past you without even giving you props. He a busy kinda cat."<<endl;}
		if (x==5||x==4){cout<<"Andrew, busily handing out fliers for the Church of Not Gay. Godspeed."<<endl;}
		if (x < 3){ cout << "some dumb ducks." << endl; }
		system("pause");
		gap();
		evergreenCity(you);
	}
}

void evergreenCity(stats& you)
{
	string c;
	you.loc=5;
	invissave(you);
	if (you.event[7]==0){
		you.event[7]=1;
	cout<<"You've made it to Evergreen City. Vendors of all different strains line the streets. ";
	cout<<"Many of the randos recognize you and give you props; after all, you are the biggest player in the game."<<endl;
	cout<<"But you ain't got time for autographs today. You step through the growing crowd and put on your stunners. ";
	cout<<"There are three places you can go to search for information: your homie D. Nguyen's shop, da Club, ";
	cout<<"or you could take it straight to the mayor, who you known since you two was little killas."<<endl;
	cout<<"His office is downtown, though. Walk on over there if you wanna get straight to business."<<endl;
	system("pause"); gap();
	}//close first time in ev square
	invissave(you);

	if (you.event[7]==3){cout<<"Walking into Evergreen City Square, you see Alvin the fireman goin to put some  sucka's house out. Fool musta been blazin' way too hard."<<endl; you.event[7]=4;}
	if (you.event[7]==2){cout<<"You remember to slip on a purple trenchcoat and shutter shades so no one        recognizes you."<<endl; you.event[7]=3;}
	if (you.event[7]==1){cout<<"As you're walking, you overhear Claudia and Christine."<<endl;
						 cout<<"'... I prefer braided whips, they leave a clearer mark...'"<<endl;
						 system("pause"); gap();
						 you.event[7]=2;}	
		cout<<"You can go back to the OUTSKIRTS, into David Nguyen's STORE, hit da CLUB,       or hop on over to DOWNTOWN."<<endl; 
		ch1(c, you, "outskirts", "store", "club", "downtown");
		if (c=="outskirts"){gap(); evergreenOutskirts(you);}
		if (c=="store"){gap(); davidStore(you);}
		if (c=="downtown"){cout<<"You go downtown."<<endl;}
		if (c == "club"){ daClub(you); }
}

void davidStore(stats& you)
{
	string c;
	int x=rng();
	you.loc=6;
	invissave(you);
	if (you.event[8]==0){
		cout<<"You walk into David's store for the first time in a week."<<endl;
		cout<<"David's shop is the only place in town that doesn't sell weed; he's as clean as a whiteboard when school's out."<<endl; //think of a better one
		you.event[8]=2;
	}//close first time in David's
	if (you.event[8]==1){cout<<"You walk into David's store."<<endl;}
	davidcall();
	ch1(c, you, "shop", "talk", "leave");

	if (c=="leave")
	{
		cout<<"'Alright, bye now.' David calls, dusting off a"; you.event[8]=1;
		if (you.name=="Eric"){cout<<"n N64. 'Pick this up next time. I know you never had one!'."<<endl; }
		else if (you.name == "Jason"){ cout << " sick library of TWOGK doujins." << endl; }
		else if (you.name == "Matt"){ cout << "n old riding crop that Claudia sold to him." << endl; }
		else { cout << " bookshelf full of heads." << endl; }
		//different items for everybody
		system("pause"); gap();
		evergreenCity(you);
	} //random items based on int x}



	if (c=="talk"){cout<<"'Okay, what do you want to talk about?' he asks politely."<<endl;
				   cout<<"As you start, he interrupts and says 'Just one word, or the game glitches.'"<<endl;
				   cout<<"You stare wide-eyed at him, mouth open in confusion."<<endl;
				   system("pause"); gap();
				   cout<<"'Go on. Just let me know when you're DONE.'"<<endl;
				   cout << "You remember to ask him about your GDP, but you might have other things on your mind." << endl;
				   davidchat(you);}

	if (c == "shop")
	{ 
		cout << "David smiles and walks you over to his gigantic shelf of goods." << endl;
		cout << "'Take a look, it's all wonderful!'" << endl; 
		evStore(you); davidStore(you);
	}

}

	void davidchat(stats& you)
{
	string c;
	cin>> c;
	gap();

		if (c=="GDP"||c=="granddaddypurple"||c=="gdp"){   cout<<"'Your Granddaddy Purple, huh? Yeah, I've smelled it in the air. There've been   rumors...'"<<endl;
					   cout<<"You perk up. 'What kinda rumors we talkin' about?' you ask eagerly."<<endl;
					   cout<<"David leans forward, gettin' serious. 'They say it's to bring back the Dank     One.'"<<endl;
					   cout<<"You feel yourself deflate. You sigh. 'Look, man, fairy tales is fairy tales, you know I think they're just boogeymen.'"<<endl;
					   cout<<"David nods. The Dank One is just a story you tell to kids to keep them away   from bad kush."<<endl;
					   system("pause"); gap();
					   cout<<"After a thoughtful pause, you say 'Know anything about who jacked it?'"<<endl;
					   cout<<"Your friend leans back in his chair, one finger pressed to his forehead."<<endl;
					   cout<<"'I only heard this walking on the street. I don't have a name for you.' he says, looking apologetic."<<endl;
					   cout<<"You look at the floor, fists clenched. 'A'ight,' you say."<<endl;
					   system("pause"); gap();
					   cout<<"But it ain't a'ight."<<endl;
					   system("pause"); gap(); davidchat(you);
		}
		else if (c=="snake")
		{
			cout<<"David's eyes begin to water. You hear him whisper 'Good night, sweet prince'."<<endl; 
			cout << "An egg rolls out of his pocket towards you, glistening with a single tear." << endl;
			newItem(you, "Egg"); davidchat(you);
		}

		else if (c=="brawl")
		{
			cout<<"David's eyes light up. He brings out a Wii and you guys play a few matches."<<endl;
			cout << "He hits you with the Falco infinite and sucks the fun out of the game." << endl;
			cout<<"Afterward, he turns and says 'Thanks, man. Take a 20% discount.'"<<endl; 
			you.event[9]++; davidchat(you);
		}

		else if (c == "connie" || c == "jackie" || c=="katie")
		{
			cout<<"'Oh man, let's talk about something else.' David says, fidgeting."<<endl; 
			cout << "'Here, I'll give you this if you stop.' he says nervously, handing you an egg." << endl;
			newItem(you, "Egg"); davidchat(you);
		}
		else if (c == "poop" || c=="butt"){ cout << "'...Why?' David says, cocking an eyebrow so hard he knocks an egg off the shelf." << endl; newItem(you, "Egg"); davidchat(you); }

		else if (c=="~" || c=="ontherocks"||c=="rocks"||c=="ontherocks~"){cout<<"'If you stop, I'll slash prices by 20%.' he says, his PTSD flaring up."<<endl;
				davidchat(you); you.event[9]++;}
		else if (c=="done")  
		{
			cout<<"'Good chatting with you,' David says, handing you an egg. You smile back and nod."<<endl;
			newItem(you, "Egg");
			davidStore(you);
		}

		else if (c=="buttsex"||c=="sex"||c=="dick"||c=="dicks")
		{
			cout<<"'Nigga that's gay. Cleanse your thoughts.'"<<endl;
			cout << "He hands you an egg to symbolize rebirth." << endl;
			newItem(you, "Egg");
			system("pause"); gap(); davidchat(you);
		}

		else if (c=="discount")
		{						
			cout<<"'Aha.'"<<endl; system("pause"); gap();
			cout<<"'Ahahaha.'"<<endl; system("pause"); gap();
			cout<<"'By the stars, you're a silly one.'"<<endl;
			cout << "'Here, for the laugh.' David says, tossing you an egg." << endl;
			newItem(you, "Egg");
			system("pause"); gap(); davidchat(you);
		}

		else if (c == "moustache")
		{ 
			cout << "'Oh, you mean this?' David says, pointing at his lip fur." << endl; 
			cout << "'Thanks for asking! Have an egg.'" << endl;
			newItem(you, "Egg");
			system("pause"); gap(); davidchat(you);
		}
		else if (c == "lu")
		{
			gap();
			if (isInInventory(you, "Gemini"))
			{
				cout << "Gemini jumps out yo pocket and starts sniffing at Lu." << endl;
				cout << "David laughs. 'You goofed. They're about to fuck.'" << endl;
				cout << "Lu and Gemini sneak on into the back." << endl;
				cout << "When they come back, they have nineteen puppies in a basket." << endl;
				cout << "David hands you a puppy. 'All yours', he says, taking the others to the kitchen." << endl;
				newItem(you, "Puppy");
				system("pause"); gap(); davidchat(you);
			}
			
			else 
			{ 
				cout << "Lu comes out from the back.\nYou pet her.\nShe offers you the egg in her mouth." << endl; 
				newItem(you, "Egg");
				system("pause"); gap(); davidchat(you);
			}
		}
		else if (c=="me")
		{
			if (you.name=="Matt"){cout<<"fuck you."<<endl; newItem(you, "Egg");}
			else if (you.name=="James"){cout<<"Siiiick."<<endl;}
			else if (you.name=="Chheang"){cout<<"Damn you fine."<<endl;}
				else 
			{ 
				cout << "'I don't have much to say about you. Have an egg!' he says cheerily." << endl;
				newItem(you, "Egg"); 
				system("pause"); gap(); davidchat(you);
			}
		}

		else 
		{
			cout<<"'I don't have much to say about that. Are you DONE?' he says, taping a box shut."<<endl;
			cout<<"You don't take offense to his bluntness. You appreciate a good blunt."<<endl;
			davidchat(you);
		}
}
	void evStore(stats& you)
	{
		int storeChoice, price=10000;
		system("pause"); gap();
		cout << "YOU HAVE " << you.skrilla << " SKRILLA" << endl;
		cout << "1: Donut -- eat big to get big" << endl;
					cout << "\t\t--10 skrilla" << endl;
		cout << "2: Red Bull -- finna fly, son?" << endl;
					cout << "\t\t--25 skrilla" << endl;
		cout << "3: Lucina Figurine -- for the degenerate waifufag in your life" << endl;
					cout << "\t\t--125 skrilla" << endl;
		cout << "4: Replica Scissor Blade -- Kill la Kill yourself" << endl;
					cout << "\t\t--850 skrilla" << endl;
		cout << "5: Shaq Soda -- Discontinued, perfect condition, may be fermented" << endl;
					cout << "\t\t--2500 skrilla" << endl;
		cout << "6: Egg -- unfertilized flightless bird embryo; Delicious!" << endl;
					cout << "\t\t--Free!" << endl;
		cout << "7: EXIT" << endl;
		cin >> storeChoice;

		if (storeChoice == 1){ price = 10; }
		if (storeChoice == 2){ price = 25; }
		if (storeChoice == 3){ price = 125; }
		if (storeChoice == 4){ price = 850; }
		if (storeChoice == 5){ price = 2500; }
		if (storeChoice == 6){ price = 0; }
		if (storeChoice == 7){ return; }

		if (storeCheck(you, price) == true)
		{
			cout << "'Here you go!' David says, handing your purchase to you." << endl;
			you.skrilla = you.skrilla - price;
			cout << "You check your wallet. You've got " << you.skrilla << " skrilla left." << endl;
			if (storeChoice == 1){ newItem(you, "Donut"); }
			if (storeChoice == 2){ newItem(you, "RedBull");; }
			if (storeChoice == 3){ newItem(you, "LucinaFigure");; }
			if (storeChoice == 4){ newItem(you, "ReplicaScissor");; }
			if (storeChoice == 5){ newItem(you, "ShaqSoda");; }
			if (storeChoice == 6){ newItem(you, "Egg");; }
			if (storeChoice == 7){ return; }
			invissave(you);
		}

		evStore(you);
		
	}

		bool storeCheck(stats& you, int price)
	{
		if (you.skrilla > price){ return true; }
		if (you.skrilla < price){ return false; }
		if (you.skrilla = price){ cout << "'Oooh, just enough!' David says with a smile."; return true; }
	}

void daClub(stats& you)
{
	string c;
	you.loc=7;
	invissave(you);
	if (you.event[10] == 0){
		cout << "You step into the club for the first time today. 'Sandstorm' bumps in the background." << endl; 
		cout << "This is basically your second house. The VIP section is your office.";
		cout << "You ain't here for leisure, though." << endl;
		cout << "You know the club's owner, 'Bee' is in the back. Bee's got both hands deep in the kush game; ";
		cout << "If anyone knows who is stealing from whom, it'd be Bee." << endl;
		cout << "But you might be able to find something out from the regulars, too..." << endl;
		cout << "You see Mariano and Alex Cheung in some red leather chairs, a few yards from the green and purple dance floor." << endl;
		system("pause"); gap();
		you.event[10] = 1;
	}
	
	cout << "You can TALK to those nerds, hit the FLOOR, go to the BACK room, or LEAVE." << endl;
	ch1(c, you, "talk", "floor", "back", "leave"); gap();

	if (c == "leave"){ cout << "You walk out the club." << endl; system("pause"); gap(); evergreenCity(you); }
	if (c == "talk"){ cout << "You step on up to Mariano." << endl; }

	if (c == "back")
	{
		if (you.event[10]==1)
		{
			hallway(you);
			daClub(you);
		}
		
	}

	if (c == "floor")
		{
			cout << "You step up onto the pulsing floor. The music ebbs louder with every step you take towards the nine-foot speakers." << endl; 
			cout << "You're surrounded by unfamiliar faces. You search for somethug you recognize." << endl;
			cout << "Finally, you see a familiar mug. But he's not on the floor." << endl;
			system("pause"); gap();
			cout << "Twirling on a pole beside the raised DJ table is your old friend Vincent, wearing nothing but a leather thong." << endl;
			cout << "He is surrounded by women squealing and throwing dollar bills at him." << endl;
			cout << "On his face is a smile wider than you've ever seen.";
			cout << "You smirk to yourself. Let him follow his dreams." << endl;
			system("pause"); gap();
			daClub(you);
		}
}

void hallway(stats& you)
{
	string c; you.loc = 8;
	if (you.event[10] == 1)
	{
		cout << "You head towards the back room. The music fades as you turn down a dark, doorless hallway away from the dance floor." << endl;
		cout << "Down ten yards, a left turn. Eight more, another left... 'Sandstorm' fades into a dust cloud." << endl;
		system("pause"); gap();
		cout << "Lights become more and more scarce. Soon, there is only one at every turn." << endl;
		cout << "Annoyed, you light up a joint, both to help you see and to settle yourself down." << endl;
		system("pause"); gap();
		cout << "You finally reach a dimly lit door, the nameplate too dark to read." << endl;
		cout << "A single bouncer sits at a desk outside, headphones wrapped around his dome, focused on a computer. You recognize his face immediately in the light of his monitor." << endl;
		cout << "'Oh, hey " << you.name << ".' Alex La says, glancing up for only a moment." << endl;
		cout << "'What's good, Alex?' you say, still walking. 'Cool if I see Bee?'" << endl;
		cout << "'Yeah, sure. I don't care.' Alex says with a laugh." << endl;
		cout << "Your hand grips the doorknob. As you turn it, you hear '...Terrorists win...' eek out of his $400 Gold Beats headset." << endl;
		system("pause"); gap();
		cout << "Alex pulls off his headset, takes a deep breath and looks around. He looks at your hand almost fully turnt, and makes a face of realization." << endl;
		cout << "'Oh, Bee actually mentioned that if you showed up, to tell you that you can't come in.' Alex says." << endl;
		cout << "You pause, face scrunched in confusion. 'What? Just me?'" << endl;
		cout << "'Yeah, Bee didn't want to see specifically you.' Alex says, pulling his headset back on." << endl;
		cout << "'I don't care either way, but Bee said you'd die if you walked in today.' Alex says, laughing one more time." << endl;
		system("pause"); gap();
		cout << "'What? Why?' you wonder. You and Bee are tight. Or /were/ tight." << endl;
		cout << "'I don't know, but Bee's only going to be in for another few minutes.' Alex states flatly, glancing at you.";
		cout << " 'If you leave now, she'll be gone when you get back.'"<< endl;
		cout << "He slides his headphones back on. Your hand's still on the knob." << endl;
		you.event[10] = 2;
		system("pause"); gap();
	}
		
	int loop = 0; bool talked = false;
	while (loop == 0)
	{
		cout << "You can ENTER Bee's office, TALK to Alex, or LEAVE." << endl;
		cout << "If you're a puss and indecisive, you can SAVE, too." << endl;
		ch1(c, you, "enter", "leave", "talk", "save");
		if (c == "talk")
		{
			if (talked == false)
			{
				cout << "'Why doesn't Bee want to see me?' you turn to Alex and ask." << endl;
				cout << "'It's not that she doesn't want to see you...' Alex trails off, landing a 720 triple noscope.";
				cout << " You wince as air horns blare from his speakers and children scream in excitement." << endl;
				cout << "'Sick frag,' you mutter." << endl;
				cout << "'Thanks. It's just that Bee will kill you if you go inside.' Alex says with another laugh." << endl;
				cout << "You look back at the door and squint with confusion. What's Bee's beef with you?";
				cout << " This got something to do with your stolen bud...? " << endl;
				cout << "You glance at La contemplatively, but he's back to his game." << endl;
				talked = true;
				system("pause"); gap();
			}

			if (talked == true)
			{
				cout << "You turn to Alex again. 'Know why Bee'll kill me if I go in?'" << endl;
				cout << "'Nope.' he says, not even glancing up." << endl;
				cout << "'Help me out, man. I already got ninety-nine problems today.'" << endl;
				cout << "'I think your biggest problem is that you're hella annoying.' He sighs, not even glancing at you." << endl;
				cout << "You make a mental note to take Alex off your Kushmas card list." << endl;
				system("pause"); gap();
			}
			hallway(you);
		}//close 'talk' option

		if (c == "save")
		{
			cout << "You scared, baby boy? Here's your save." << endl;
			cout << "But you lose one charisma for being such a puss." << endl;
			you.charisma -= 1;
			save(you);
			hallway(you);
		}

		if (c == "leave")
		{
			cout << "You make the informed decision to not bother Bee." << endl;
			cout << "In terms of realism, this is the most reasonable choice, as there is a guarantee that Bee will try to harm you, ";
			cout<<"but no guarantee that Bee knows anything vital. Your decision was based on sound logic."<< endl;
			cout << "You smart, but you're a coward and afraid. +2 intelligence, -2 charisma." << endl; 
			you.intel += 2;
			you.charisma -= 2;
			you.event[11] = 1;
			system("pause");
			cout << "As you turn to leave, you hear the door to Bee's office swing open." << endl;
			cout << "'That's " << you.name << ", right, La?' you hear a familiar voice say." << endl;
			cout << "'Yep.' Alex responds curtly. 'Want to see them?"<<endl;
			cout << "'Yes. Now.' the voice demands, and your hear footsteps walk to a corner of the office.";
			cout << "You turn, but Alex is already up and has you by the arm, guiding you inside." << endl;
			cout << "The inside of the office has more smoke than an ogre has layers. The door is sealed along its rim, too; prime hotbox spot." << endl;
			cout << "Before you can react, you're standing in front of Bee's desk, and Alex storms out the room, ";
			cout << "slamming the door with the force of a guy whose mother takes all his blankets while he sleeps." << endl;
			system("pause"); gap();
			beeOffice(you);
		}

		if (c == "enter")
		{
			gap();
			cout << "Gutsy. +1 charisma." << endl; you.charisma += 1;
			you.event[11] = 2;
			cout << "You swallow your fear, and then your joint, and twist the knob." << endl;
			cout << "As soon as the door cracks open just a bit, dense smoke and dim light pour  out of the slat." << endl;
			cout << "You drag the heavy door across its parabolic arc. You can barely make out an    ornate wooden desk in the windowless room. " << endl;
			cout << "The smoke-grey tinted silouette of an incredibly large chair sits behind it,    facing away from you." << endl;
			cout << "You take a step inside, the cloud not affecting your seasoned lungs." << endl;
			system("pause"); gap();
			beeOffice(you);

		}
	}

}

void beeOffice(stats& you)
{
	you.loc = 9;
	string c;
	invissave(you);
	cout << "'Take a seat, " << you.name << ". We have a lot to talk about.' Bee's voice slices through  the cloud, sharper than you ever heard it." << endl;
	cout << "You notice a nice looking leather lounge chair right behind you." << endl;
	cout<< "It's even got a blunt-holder. You make a note to hit up Ikea." << endl;
	system("pause"); gap();
	cout << "'Bee, what's with this Godfather shit? You know something, don't you?' you      demand, taking a step forward and raising a finger." << endl;
	cout << "'"<<you.name << ", I said sit down. You want to know anything, you'll put your ass in the leather behind you.'" << endl;
	system("pause"); gap();
	cout << "Your face stays stone cold, but you clench your teeth in frustration." << endl;
	cout << "Bee's ordering you around like the popo to some street punk." << endl;
	cout << "Do you reject Bee's order and demand answers how you want them, or stay         reasonable and get Bee to cooperate with words?" << endl;
	system("pause"); gap();


	string options[2] = { "Stay standing", "Sit Down"};
	boolean standing = false;
	switch (initMenu("How do you react to Bee?", options, 2))
	{
	case 1:
	{
		if (you.swole >= 5)	//you successfully stay standing
		{
			standing = true;
			cout << "You chose to stay standing, and you SWOLE enough to keep your knees from buckling." << endl;
			cout << "You do a few squats in celebration of your stable joint structure. +3 swole." << endl;
			you.swole += 3;
			if (you.event[11] == 1)
			{
				cout << "How you gonna puss out when you're outside, but be all ballsy when shit gets dangerous? You strange, fool. +1 charisma." << endl;
				you.charisma += 1;
			}
			if (you.event[11] == 2)
			{
				cout << "You been bold as fuck. +2 charisma." << endl;
				you.charisma += 2;
				you.event[11] = 3;
			}
			system("pause"); gap();
		}

		else if (you.intel >= 10)
		{
			standing = true;
			cout << "You chose to stay standing. Your knees almost gave out, ";
			cout << "but with your overwhelming SMARTS, your comprehension of gravity and the universe allowed you to levitate off the ground." << endl;
			cout << "You quickly corporealize this understanding into an orb of levitation, which drains your mental energy significantly." << endl;
			cout << "You lose 5 intelligence out of exhaustion, but gain an untold treasure." << endl;
			newItem(you, "LevitationOrb");
			you.intel -= 5;
			system("pause"); gap();
			if (you.event[11] == 1)
			{
				cout << "How you gonna puss out when you're outside, but be all ballsy when shit gets dangerous? You strange, fool. +1 charisma." << endl;
				you.charisma += 1;
			}
			if (you.event[11] == 2)
			{
				cout << "You been bold as fuck. +2 charisma." << endl;
				you.charisma += 2;
				you.event[11] = 3;
			}
			system("pause"); gap();
		}

		else if (you.charisma >= 8)
		{
			standing = true;
			cout << "You chose to stay standing. Your knees almost gave out, but all that CHARISMA turned it into a sickass pose." << endl;
			cout << "Proud of yourself, you strut over to Bee's desk, grab a pen and paper and write down how to pull it off." << endl;
			newItem(you, "SickPoseInstructions");
			if (you.event[11] == 1)
			{
				cout << "How you gonna puss out when you're outside, but be all ballsy when shit gets dangerous? You strange, fool. +1 charisma." << endl;
				you.charisma += 1;
			}
			if (you.event[11] == 2)
			{
				cout << "You been bold as fuck. +2 charisma." << endl;
				you.charisma += 2;
				you.event[11] = 3;
			}
			system("pause"); gap();
		}



		else //you unsuccesfully try to stand, falling back into the chair
		{
			standing = false;
			cout << "You chose to stay standing. Unfortunately, you don't have enough SWOLE to keep your nervous knees from buckling." << endl;
			cout << "You stumble backwards and fall into the chair. Embarassing af, bruh. -2 charisma." << endl;
			you.charisma -= 2;
		}	//stamding = false, so this option will continue in the else block of if(standing==true), written below
		break;
	}

	case 2:
	{
		standing = false;
		cout << "You chose to sit down. You don't got nothing to gain from pressing the issue." << endl;
		cout << "Smart choice. +2 SMARTS. But that's pansy shit. -2 CHARISMA." << endl;
		you.intel += 2; you.charisma -= 2;
		break;
	}	//stamding = false, so this option will continue in the else block of if(standing==true), written belows

	//case 3:
	//{
	//	standing = true;
	//	cout << "'Feh, I don't need any pathetic friends.' you spit as you turn towards the door." << endl;
	//	cout << "You grab the knob and turn it harder than you turned on the Hidden Leaf Village." << endl;
	//	cout << "Your EDGE level has increased!" << endl;
	//	you.edge++;
	//	//Insert Alex boss fight here.
	//	cout << "*INCLUDE* alex boss fight" << endl;
	//	break;
	//}
	}

	if (standing == true)
	{
		cout << "Through the kush mist, you see Bee's arm raise from behind the chair, holding a switch with a single button." << endl;
		cout << "Bee's thumb drops on the button, and you hear a crescendo of mechanical whirring from behind you." << endl;
		cout << "Your instincts tell you to move, and dive to the right side of the room, hitting the wall and staggering. You turn towards Bee." << endl;
		system("pause"); gap();
		cout << "You can make out the faint, blurry side profile of Bee, thumb still on that     switch. You glance quickly around and see that the";
		cout << "chair that Bee offered you is now encased in a glass bubble, slowly filling up with a blue-tinted smoke." << endl;
		cout << "As a seasoned dealer, you recognize the smoke as Sea Mist." << endl;
		cout << "It's a halluginogenic strain so potent that, even with your tolerance, you'd probably fall into a week-long coma." << endl;
		cout << "You stand up fully as Bee sets down the switch." << endl;
		system("pause"); gap();
		cout << "Through the deep kush vapors, you hear the familiar scrape of a lighter, and see a brief spark that lights up near Bee's face. " << endl;
		cout << "You see her profile clearly for the first time in months, maybe years. The end   of the pipe near her face glows a dull red." << endl;
		cout << "She breathes heavily, but it doesn't sound like she's taking a hit from her pipe. Sounds more like a sigh." << endl;
		system("pause"); gap();
		cout << "After a moment, Bee sets her pipe on her desk and stands up. She reaches out to the darkness behind her desk and pulls on a drawstring you couldn't see before." << endl;
		cout << "Bright midday sun floods the room. There was an enormous window hidden beneath a drapery you couldn't see before. She reaches to one end of the giant window and pulls." << endl;
		cout << "The window opens, and the smoke from the room vacuums quickly outside, fleeing, as if not even the air wanted to know what comes next." << endl;
		system("pause"); gap();
		cout << "Bee turns back towards her desk, and pulls a Glock from the drawer underneath.  You see it's unloaded, but that's bound to change." << endl;
		cout << "'I usually keep that smoke in here as a defense. It's a strain of my own creation: White Widow, so dank that gunpowder just won't light.' she rummages around the drawer, probably looking for a magazine." << endl;
		cout << "You start looking for an exit, but the only ways out are the door or the window, and both are easy targets." << endl;
		system("pause"); gap();
		cout << "Your eyes frantically look around, while Bee pulls out the cartridge she was looking for. With a clean movement, she loads the Glock. Bee's lips harden." << endl;
		cout << "She turns to face you, and finally you get a straight look at her face. But it's not as you remember." << endl;
		cout << "Bee has an eyepatch covering her left eye, a scar beginning somewhere underneath it, running vertically along her face, ending below her chin." << endl;
		cout << "Your eyebrows furrow down. She never looked like that. Bee feels your confusion and closes her good eye. She turns her head to the floor, and pensively traces ";
		cout << "the scar along her face. She shakes her head once, then looks up, eyes harder than flint, staring right into your eyes." << endl;
		cout << "She points the Glock at your chest with one hand and pulls back the hammer with the other. " << endl;
		system("pause"); gap();
		cout << "She don't look like the Hillary Li you used to know." << endl;
		system("pause"); gap();
		cout << "'This goes deeper than a strain of weed, " << you.name << ". But there's really no time to  explain.'" << endl;
		cout << "She uses her free hand to press the switch on her desk again. The glass bubble   over the lounge chair raises up." << endl;
		cout << "'Someone from the Conclave will be here in minutes. Neither of us can take them. They want you out of the picture.'" << endl;
		cout << "'Conclave?' you ask, stalling, hoping for a way out." << endl;
		cout << "'Good, you don't know. It's better that way.' She lowers the Glock, but only by inches." << endl;
		system("pause"); gap();
		cout << "'Listen, " << you.name << ", we've got one shot to make this work.'" << endl;
		cout << "Hillary's voice is quiet this time. No authoritative edge."<<endl;
		system("pause"); gap();
		cout << "'You get in that chair, you drift off on that Sea Mist for a week or two, and   I'll make everything work out. You wake up in your house with your Grandaddy    Purple, Gemini, ";
		cout << "and all your friends stay completely safe. I swear to you,   all our problems will be solved.'"<<endl;
		cout << "Hillary's voice starts getting shaky, like she's desperate." << endl;
		system("pause"); gap();
		cout<< "'Hillary...' you start, raising a hand. In response, she flicks off the safety   and aims for your forehead." << endl;
		cout << "Hillary takes a deep breath, and her voice regains composure. 'If you don't,     this whole town, and everyone in it, are going straight to hell.'" << endl;
		cout << "'Everyone I care about, everyone you care about, gone. You need to be out of the picture. You choose to stand, I'll make sure you fall.' Hillary's eyes glint with determination." << endl;
		system("pause"); gap();
		cout << "'Hillary, just tell me what's happening. If something's going down, let me--'" << endl;
		cout <<  "You feel your heart plummet as Hillary chuckles." << endl;
		system("pause"); gap();
		cout << "'Nah, "<<you.name<<", there's only one thing you need to know.'" << endl;
		cout << "'If you don't get in that chair...'" << endl;
		system("pause"); gap();
		hillaryCall();
		string options[2] = { "Comply", "Refuse" };
		switch (initMenu("Choose.", options, 2))
		{
		case 1:
			cout << "You slowly raise both hands up." << endl;
			cout << "'I don't know what's going on, Hillary, but I trust you.' Your words come out slowly, carefully."<<endl;
			cout << "Hillary's hands don't move, but her eyes soften slightly. 'Please, get in. I'll make sure everything works out.'" << endl;
			cout << "Arms still raised, like a playa in front of the cops, you sidestep towards the chair." << endl;
			cout << "Your short, sharp, breaths catch a whiff of that Sea Mist; just standing near it gets you a little faded." << endl;
			cout << "You ease yourself into the recliner. Hillary slides back to the button on the desk, gun still loaded and pointed right at you." << endl;
			system("pause"); gap();
			inTheChair(you);
				break;


		case 2:
			cout << "You stay standing." << endl;
		}
		
	}

	if (standing==false)
	{
		cout << "You hear a soft chuckle from behind the chair." << endl;
		cout << "'Thanks for playing along, " << you.name << ",' you hear Bee say, almost almost whispering." << endl;
		cout << "You see Bee's arm raise, but what's in her hand? Looks like a switch or --" << endl;
		cout << "Her thumb drops on the button in the center, and your hear mechanical chunking sounds from above you." << endl;
		cout << "Before you have time to react, a glass dome has dropped over the entire chair. Your heart pounds, but you suddenly, abnormally begin to feel relaxed, sleepy even." << endl;
		cout << "Through your now-heavy eyelids, you see the dome filling with blue smoke. 'Sea Mist...' you say, recognizing the  ";
	}

}

void hillaryCall()
{
	cout << "'You";
	Sleep(500); gap();
	cout << "'You die.";
	Sleep(1000); gap();
	cout << "'You die. Right";
	Sleep(500); gap();
	cout << "'You die. Right where ";
	Sleep(500); gap();
	cout << "'You die. Right where you"<<endl;
	Sleep(500); gap();
	cout << "'You die. Right where you stand.'"<<endl;
	Sleep(2000);
	system("pause"); gap();
}

void inTheChair(stats& you)
{
	you.loc = 16;
	save(you);	//for dramatic effect
	system("pause"); gap();

	cout << ""
}

void EVdowntown(stats& you)
{
	you.loc = 10;
	string c;
	invissave(you);
	ch1(c, you, "talk", "leave");

}

void chiefKeef(stats& you)
{
	you.loc = 11;
	string c;
	invissave(you);
	ch1(c, you, "talk", "leave");

}

void jackieRestaurant(stats& you)
{
	you.loc = 12;
	string c;
	invissave(you);
	ch1(c, you, "talk", "leave");

}

void cityHall(stats& you)
{
	you.loc = 13;
	string c;
	invissave(you);
	ch1(c, you, "talk", "leave");

}

void mayorOffice(stats& you)
{
	you.loc = 14;
	string c;
	invissave(you);
	ch1(c, you, "talk", "leave");

}

void HWY101(stats& you)
{
	you.loc = 15;
	string c;
	invissave(you);
	ch1(c, you, "talk", "leave");

}