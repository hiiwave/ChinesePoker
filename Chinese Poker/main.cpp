/****************************************************************************
FileName   [ main.cpp ]
Synopsis   [ main of Chinese Poker Game ]
****************************************************************************/

#include "CprDef.h"
#include "CprGame.h"
#include "CprTest.h"
using namespace std;
int seed;

int main() {
	/*
	CprTest test;
	test.run();
	cout << "Press any buttons to continue .." << endl;
	system("pause");
	return 0;
	*/
	
	seed = (unsigned)time(0);
	// seed = 1452540360;
	cout << "This is TA's reference program." << endl;
	cout << "Using seed " << seed << ".." << endl;
 	srand(seed);
	CprGame game;
	game.setting();
	game.start();
	return 0;
}
