/****************************************************************************
FileName   [ CprHumanPlayer.cpp ]
Synopsis   [ implement user interface for human players ]
****************************************************************************/

#include "CprHumanPlayer.h"
#include "CprCollection.h"
#include <sstream>

CprHumanPlayer::CprHumanPlayer() {}

CprHumanPlayer::~CprHumanPlayer() {
}

void CprHumanPlayer::playerStrategy() {
	cout << getId() << ", your cards are as follows: " << endl << "  ";
	collection().printByRank();
	cout << "Please play.. try 'help' for command list:" << endl;
	readCommands();
}

void CprHumanPlayer::showHelps() {
	cout << "Command List:" << endl;
	cout << "  help  : show all commands" << endl
		<< "  ls -r : print cards sorted by rank" << endl
		<< "  ls -s : print cards sorted by suit" << endl
		<< "  show  : show all hands" << endl
		<< "  reset : reset hands" << endl
		<< "  done  : finish setting" << endl
		<< "  1 3c Ac Ah : make 1st hand with (3c, Ac, Ah)" << endl
		<< "  2 3c 4c 5c 6c 7c : make 2nd hand with (3c, 4c, 5c, 6c, 7c)" << endl
		<< "  3 3c 4c 5c 6c 7c : make 3rd hand with (3c, 4c, 5c, 6c, 7c)" << endl;
}

void CprHumanPlayer::readCommands() {
	bool b = false;
	cout << "> ";
	
	while (!b && getline(cin, _command)) {
		if (_command.empty())  continue;
		b = parseOneCmd();
		if (!b) {
			cout << "> ";
		}
	}
}

bool CprHumanPlayer::parseOneCmd() {
	if (_command == "help") {
		showHelps();
	} else if (_command == "ls -r" || _command == "ls") {
		cout << "  ";
		collection().printByRank();
	} else if (_command == "ls -s") {
		cout << "  ";
		collection().printBySuit();
	} else if (_command == "show") {
		collection().showCollection();
	} else if (_command == "reset") {
		collection().resetAllHands();
	} else if (_command == "done") {
		return checkValidStrategy();
	} else {
		parseHandCmd();		
	}
	return false;
}

void CprHumanPlayer::parseHandCmd() {
	istringstream in(_command);
	int handNum;
	if (!(in >> handNum) || handNum > 3 || handNum <= 0) {
		cout << "Command Error!" << endl;
	} else if (handNum == 1) {
		CardList cards(3);
		if ( !(in >> cards[0] && in >> cards[1] && in >> cards[2]) ||
				!collection().settingHand(0, cards) ) {
			cerr << "Command error. Try 'help' to continue." << endl;
		}
	} else {
		assert (handNum == 2 || handNum == 3);
		CardList cards(5);
		if ( !(in >> cards[0] && in >> cards[1] && in >> cards[2]
			 	&& in >> cards[3] && in >> cards[4]) ||
				!collection().settingHand(handNum - 1, cards) ) {
			cerr << "Command error. Try 'help' to continue." << endl;
		}
	}
}

bool CprHumanPlayer::checkValidStrategy() {
	if (collection().isFinalHandLeftOnly()) {
		collection().settingFinalHand();
	}
	if (collection().isValidSet()) {
		collection().showCollection();
		char line[128];
		cout << "Are you sure to continue? (Y/N) \n> ";
		cin.getline(line, 128);
		char ch = line[0];
		if (ch == 'Y' || ch == 'y') {
			return true;
		} else {
			return false;
		}
	} else {
		cout << "Not ready yet." << endl;
		return false;
	}

}