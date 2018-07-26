/****************************************************************************
FileName   [ CprDealer.h ]
Synopsis   [ define/implement a dealer in dealing phase ]
****************************************************************************/

#pragma once
#include "CprCollection.h"
#include "CprPlayer.h"

class CprDealer
{
public:
	CprDealer() {
		for (int i = 1; i <= 52; ++i) {
			ids.push_back(i);
		}
	}
	~CprDealer() {}
	void specialDeal(PlayerList& players) {
		cout << "DEBUG ING!" << endl;
		for (CprPlayer* player : players) {
			CardList cards;
			if (player == players.back()) {
				cards = CardList{ 5, 18, 31, 44, 12, 25, 38, 7, 20, 4, 17, 30, 2 };
			} else {
				for (int i = 0; i < 13; ++i) {
					cards.push_back(pickOneId());
				}
			}
			std::sort(cards.begin(), cards.end());
			(player->_myCards) = cards;
			(player->_collection)._cards = cards;
			(player->_collection)._availCards = cards;
			(player->_collection).computeACR();
		}
	}

	void deal(PlayerList& players) {
		// return specialDeal(players);	// DEBUG
		assert(players.size() <= 4 && players.size() > 0);
		for (CprPlayer* player : players) {
			CardList cards;
			for (int i = 0; i < 13; ++i) {
				cards.push_back(pickOneId());
			}
			std::sort(cards.begin(), cards.end());
			(player->_myCards) = cards;
			(player->_collection)._cards = cards;
			(player->_collection)._availCards = cards;
			(player->_collection).computeACR();
		}
	}
private:
	vector<int> ids;
	int pickOneId() {
		int pos = rand() % ids.size();
		int id = ids.at(pos);
		ids.at(pos) = ids.back();
		ids.pop_back();
		return id;
	}
};

