#include "CprStupidAi.h"

CprStupidAi::CprStupidAi() {
}


CprStupidAi::~CprStupidAi() {
}

void CprStupidAi::playerStrategy() {
	const CardList& availCards = _collection.getAvailableCards();
	CardList cards1 = CardList(availCards.begin(), availCards.begin() + 3);
	CardList cards2 = CardList(availCards.begin() + 3, availCards.begin() + 8);
	CardList cards3 = CardList(availCards.begin() + 8, availCards.end());
	_collection.settingHand(0, cards1);
	_collection.settingHand(1, cards2);
	_collection.settingHand(2, cards3);
}
