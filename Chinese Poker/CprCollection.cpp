/****************************************************************************
FileName   [ CprCollection.cpp ]
Synopsis   [ implement CprCollection member functions ]
****************************************************************************/

#include "CprCollection.h"
#include "CprHand.h"


CprCollection::CprCollection() 
	:_cards(), _hands(3) {
}

CprCollection::~CprCollection() {
}

bool CprCollection::settingHand(int hidx, const CprHand &h) {
	bool b = settingHand(hidx, h.getCards());
	if (b) {
		_hands.at(hidx)._type = h._type;
		_hands.at(hidx)._subScoreI = h._subScoreI;
	}
	return b;
}

bool CprCollection::settingHand(int hidx, const CardList& cs) {
	assert(hidx >= 0 && hidx < 3);
	if (!hand(hidx).empty()) {
		return false;
	}
	// 1. Check duplicate elements in cards
	CardList cards = cs;
	CardList::iterator it = std::unique(cards.begin(), cards.end());
	if (it != cards.end()) {
		return false;
	}

	// 2. Check all cards available
	for (const CprCard& c : cards) {
		if (!isCardAvailable(c)) {
			return false;
		}
	}

	// 3. Remove cards from _availCards
	CardList post_availCards(_availCards.size());
		// CardList post_availCards(_availCards.size() - cards.size());
	std::sort(cards.begin(), cards.end());
	it = std::set_difference(_availCards.begin(), _availCards.end(),
		cards.begin(), cards.end(), post_availCards.begin());
	assert(std::distance(post_availCards.begin(), it) == _availCards.size() - cards.size());
	post_availCards.resize(_availCards.size() - cards.size());
	_availCards = post_availCards;
	computeACR();

	// 4. Set hand by cards
	_hands.at(hidx) = CprHand(cs);
	return true;
}

bool CprCollection::settingFinalHand() {
	int finIdx = -1;
	for (int hidx = 0; hidx < 3; ++hidx) {
		if (_hands.at(hidx).empty()) {
			assert(finIdx == -1);
			finIdx = hidx;
		}
	}
	assert(finIdx != -1);
	if (finIdx == 0) {
		assert(_availCards.size() == 3);
	} else {
		assert(_availCards.size() == 5);
	}
	CardList finalCards = _availCards;
	std::sort(finalCards.begin(), finalCards.end(), c_ordinal);
	settingHand(finIdx, finalCards);
	CprHandMaster::DetermineType(_hands.at(finIdx));
	CprHandMaster::CalculateSubScore(_hands.at(finIdx));

	_availCards.clear();
	computeACR();
	return true;
}

void CprCollection::finishSetting() {
	for (CprHand& hand : _hands) {
		CprHandMaster::DetermineType(hand);
		// if (hand._type == HTUndefined) {
		// 	CprHandMaster::DetermineType(hand);
		// }
	}
}


void CprCollection::resetHand(int hidx) {
	// TODO
}

void CprCollection::resetAllHands() {
	for (int i = 0; i < 3; ++i) {
		_hands.at(i) = CprHand();
	}
	_availCards = _cards;
	computeACR();
}

CprHand & CprCollection::hand(int idx) {
	return _hands.at(idx);
}

const CprHand & CprCollection::getHand(int idx) const {
	return _hands.at(idx);
}

const CardList & CprCollection::getAvailableCards() const {
	return _availCards;
}

void CprCollection::computeACR() {
	for (int i = 1; i <= 14; ++i) {
		_ACR[i].clear();
	}
	for (const CprCard& c : _availCards) {
		_ACR[c.rank()].push_back(c);
		std::sort(_ACR[c.rank()].begin(), _ACR[c.rank()].end());
	}
	_ACR[14] = _ACR[1];
}

const CardList * CprCollection::getACR() const {
	return _ACR;
}

void CprCollection::printByRank() const {
	CardList cards = _availCards;
	std::sort(cards.begin(), cards.end(), c_ordinal);
	for (const CprCard& c : cards) {
		cout << c << " ";
	}
	cout << endl;
}

void CprCollection::printBySuit() const {
	CardList cards = _availCards;
	for (const CprCard& c : cards) {
		cout << c << " ";
	}
	cout << endl;
}

void CprCollection::showCollection(int pType) const {
	if (!_availCards.empty()) {
		cout << "Available cards: " << endl << "  ";
		printByRank();
	}
	for (unsigned i = 0; i < _hands.size(); ++i) {
		const CprHand& hand = _hands.at(i);
		cout << "hand " << (i + 1) << ": ";
		hand.print(pType);
		cout << endl;
	}
}

bool CprCollection::isValidSet() const {
	const HandList& hands = _hands;
	if (hands.size() != 3 || hands[0].size() != 3 ||
		hands[1].size() != 5 || hands[2].size() != 5) {
		return false;
	}
	CardList cards = hands.at(0).getCards();
	cards.insert(cards.end(),
		hands.at(1).getCards().begin(), hands.at(1).getCards().end());
	cards.insert(cards.end(),
		hands.at(2).getCards().begin(), hands.at(2).getCards().end());
	std::sort(cards.begin(), cards.end());

	CardList colCards = _cards;
	std::sort(colCards.begin(), colCards.end());
	assert(cards.size() == 13 && colCards.size() == 13);
	for (unsigned i = 0; i < cards.size(); ++i) {
		if (cards.at(i) != colCards.at(i)) {
			return false;
		}
	}
	return true;
}

bool CprCollection::isFinalHandLeftOnly() const {
	const HandList& hands = _hands;
	int emptyCount = 0;
	for (int i = 0; i < 3; ++i) {
		if (hands.at(i).empty()) {
			++emptyCount;
		}
	}
	return emptyCount == 1;
}

bool CprCollection::sameWith(const CprCollection & col) {
	for (int i = 0; i < 3; ++i) {
		if (!_hands.at(i).sameWith(col._hands.at(i))) {
			return false;
		}
	}
	return true;
}

/* -----------------------
   private Methods
----------------------- */

bool CprCollection::isCardAvailable(const CprCard& c) const {
	return std::find(_availCards.begin(), _availCards.end(), c) != _availCards.end();
}