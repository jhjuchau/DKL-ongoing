#ifndef DANK_H
#define DANK_H
#include <iostream>
using namespace std;

/*QUICK ITEMS REFERENCE
Gemini- picked up from house, useful with jackie and Lu
Egg- from david, useless
UnripeReliable  - if you didn't wait
PremiumReliable - if you waited
RogueNinjaHeadband - if you responded 3 to the road


*/

/*while ( ch!=1 && ch!=2 &&  ch!=3)
					{
						gap();
						cout<<"1: "<<endl;
						cout<<"2: "<<endl;
						cout<<"3: "<<endl;  
						cin>>ch;
						if (ch!=1 && ch!=2 && ch!=3){cout<<"Pick a valid number, fool."<<endl;}
					}
					gap();

					if (ch==1)
				{
					gap();
					system("pause");
					gap();
					
				}

					if (ch==2)
				{  
					gap();
					system("pause");
					gap();
				}
					
					if (ch==3)
				{
					gap();
					system("pause");
					gap();
				}
			}

*/
int rng()
{
	int randNum1;
	int lowest=1, highest=10;
	int range=(highest-lowest)+1;
	srand((unsigned)time(0));
	randNum1 = lowest + rand() % range;
	return randNum1;
}
int rng1to3()
{
	int randNum1;
	int lowest = 1, highest = 3;
	int range = (highest - lowest) + 1;
	srand((unsigned)time(0));
	randNum1 = lowest + rand() % range;
	return randNum1;
}
void rng(int& var1, int& var2)
{
	int lowest=1, highest=10;
	int range=(highest-lowest)+1;
	srand((unsigned)time(0));
	var1 = lowest + rand() % range;
	var2 = lowest + rand() % range;
}
void rng(int& var1, int& var2, int& var3)
{
	int lowest=1, highest=10;
	int range=(highest-lowest)+1;
	srand((unsigned)time(0));
	var1 = lowest + rand() % range;
	var2 = lowest + rand() % range;
	var3 = lowest + rand() % range;
}

char yn()
{
	char yn='x';
	while (yn!='Y' && yn!='N')
	{
		cin>>yn;
		yn = toupper(yn);
		if(yn!='Y' && yn!='N'){cout<<"Only 'Y' or 'N' are valid, playa."<<endl;}
	}

	return yn;
}

bool isValid(string input, string str1, string str2)
{
	str1[0] = toupper(str1[0]);
	str2[0] = toupper(str2[0]);

	if (input==str1){return true;}
	else if (input==str2){return true;}
	else {cout<<"Best type a valid option."<<endl;	return false;}
}

bool isValid(string input, string str1, string str2, string str3)
{
	str1[0] = toupper(str1[0]);
	str2[0] = toupper(str2[0]);
	str3[0] = toupper(str3[0]);

	if (input==str1){return true;}
	else if (input==str2){return true;}
	else if (input==str3){return true;}
	else {cout<<"Best type a valid option."<<endl;  return false;}
}

bool isValid(string input, string str1, string str2, string str3, string str4)
{
	str1[0] = toupper(str1[0]);
	str2[0] = toupper(str2[0]);
	str3[0] = toupper(str3[0]);
	str4[0] = toupper(str4[0]);
	if (input==str1){return true;}
	else if (input==str2){return true;}
	else if (input==str3){return true;}
	else if (input==str4){return true;}
	else {cout<<"Best type a valid option."<<endl; return false; }
}

bool isStatEnough(int stat, int measure)
{
	if (stat>=measure){return true;}
	if (stat<measure){return false;}
}

void davidcall()
{
	int i1, i2, i3; rng(i1, i2, i3);
	if (i1<=3){cout<<"'Hey, ";}
	else if ((4<=i1)&&(i1<=7)){cout<<"'Hello, ";}
	else if ((8<=i1)&&(i1<=10)){cout<<"'Hi, ";}

	if (i2<=3){cout<<"hey ";}
	else if ((4<=i2)&&(i2<=7)){cout<<"hello ";}
	else if ((8<=i2)&&(i2<=10)){cout<<"hi ";}

	if (i3<=3){cout<<"hey!' David calls. ";}
	else if ((4<=i3)&&(i3<=7)){cout<<"hello!' David calls. ";}
	else if ((8<=i3)&&(i3<=10)){cout<<"hi!' David calls. ";}

	cout<<"David twirls his moustache and gives you a warm   smile."<<endl;
	cout<<"'You here to SHOP, TALK, or LEAVE?'"<<endl;
}

#endif