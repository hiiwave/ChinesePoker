/****************************************************************************
FileName   [ CprGame.cpp ]
Synopsis   [ implement CprGame member functions ]
****************************************************************************/

#include "CprGame.h"
#include "CprStage.h"
#include "CprRegularAi.h"
#include "CprGreedyAi.h"
#include "CprStupidAi.h"
#include "CprBruteAi.h"
#include "CprHumanPlayer.h"

CprGame::CprGame() {
	cout << endl;
	cout << "****************************" << endl;
	cout << "* Welcome to Chinese Poker *" << endl;
	cout << "****************************" << endl;
	cout << endl;
}

CprGame::~CprGame() {
	for (CprPlayer* p : _players) {
		delete p;
	}
}

void CprGame::setting() {
	const int playerNum = 4;
	if (playerNum >= 4) {
		CprPlayer* ai = new CprRegularAi(2.5, 5.0);
		ai->setId("Juice");
		_players.push_back(ai);
	}
	if (playerNum >= 3) {
		CprPlayer* ai = new CprRegularAi(1.5, 1.0);
		ai->setId("Candy");
		// CprPlayer* ai = new CprBruteAi(2.5, 5.0);
		// ai->setId("Brute");
		_players.push_back(ai);
	}

	// Custom AI (or greedy AI)
	CprPlayer* ai = new CprGreedyAi();
	ai->setId("Greed");
	// CprPlayer* ai = new CprRegularAi();
	// ai->setId("Nihao");
	_players.push_back(ai);

	char line[64];
	cout << "Human playing or AI playing? (H/A) \n> ";
	cin.getline(line, 64);
	char ch = line[0];
	// cout << "A" << endl;  ch = 'a';  // TEST

	if (ch == 'H' || ch == 'h') {
		CprPlayer* human = new CprHumanPlayer();
		human->setId("You");
		_players.push_back(human);
	} else {
		CprPlayer* ai = new CprRegularAi();
		ai->setId("Hey");
		_players.push_back(ai);
	}
}

void CprGame::start() {
	for (int T = 0; T < 1; ++T) {
		for (int i = 1; i <= 400; ++i) {
			CprStage stage(_players, i);
			stage.start();
		}
	}
	end();
}

void CprGame::end() {
	cout << "Game End." << endl;
	cout << "Press any button to exit.." << endl;
	cin.get();
}