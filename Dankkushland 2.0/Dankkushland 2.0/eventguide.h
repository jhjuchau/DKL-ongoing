/*QUICK EVENTS REFERENCE GUIDE
you.event[i] == 0 if undone, 1 if done, but they're ints, so other values are possible, like talking to david
0: First time: Starting from the Bottom			0 if first time, 1 if gemini there, 2 if gemini not there
1: First time: Outside
2: Garden Growing,							    0 if no time, 1 if seen, 2 if ripe, 3 if snipped
3: David Interaction,						    0 is default, 1 = friendly, 2 = suspicious, 3 = hostile
4: First time: Road, doubting your friends    	1 = friendly, 2=suspicious, 3 = hostile
5: Jackie in a fight						    1 = ignored,  2 = nothing special,   3 = beat up    4 = gave unripe reliable  5=Khandiel  6= Jessa
6: First time, outskirts
7: First time and different events, EV Square	0 default, 1 been there once, saw claudia+christine, 2 slip on disguise, 3 see alvin,
8: First time in David's store
9: David discount								0 is default, each ++ is an additional 20% discount
10: First time in da club                       0 if first time in club, 1 once seen club flavor text, 2 if seen hallway flavor text
11: Talking with Bee
*/


//ctrl+k, ctrl+c == comment selection
//ctrl+k, ctrl+u == uncomment selectionh