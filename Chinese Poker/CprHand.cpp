/****************************************************************************
FileName   [ CprHand.cpp ]
Synopsis   [ implement CprHand member functions ]
****************************************************************************/

#include "CprHand.h"
#include "CprHandMaster.h"

CprHand::CprHand()
	: _type(HTUndefined) {}

CprHand::CprHand(const CardList & cards)
	: _cards(cards), _type(HTUndefined) {}

CprHand::CprHand(const CardList & cards, HandType type) 
	: _cards(cards), _type(type) {
}

CprHand::~CprHand() {
}

bool CprHand::operator<=(const CprHand & hand) const {
	return CprHandMaster::Compare(*this, hand);
}

bool CprHand::operator>=(const CprHand & hand) const {
	return !CprHandMaster::Compare(*this, hand);
}

const CardList& CprHand::getCards() const {
	return _cards;
}

int CprHand::size() const {
	return (int)_cards.size();
}

bool CprHand::empty() const {
	return _cards.size() == 0;
}

CprCard & CprHand::at(int idx) {
	return _cards.at(idx);
}

CprCard CprHand::getCard(int idx) const {
	return _cards.at(idx);
}

CardList * CprHand::getACR() const {
	CardList* acr = new CardList[15];
	for (const CprCard& c : _cards) {
		acr[c.rank()].push_back(c);
		std::sort(acr[c.rank()].begin(), acr[c.rank()].end());
	}
	acr[14] = acr[1];
	return acr;
}

double CprHand::getSubScore() const {
	return (double)_subScoreI / 256;
}

void CprHand::setXianggong() {
	_type = HTXianggong;
}

void CprHand::print(int pType) const {
	for (const CprCard& c : _cards) {
		cout << c << " ";
	}
	if (pType >= 1) {
		cout << " (" << CprHandMaster::traslateType(_type) << ")";
	}
}

HandType CprHand::getType() const {
	return _type;
}

bool CprHand::sameWith(const CprHand &h) {
	if (size() != h.size())  return false;
	for (int i = 0; i < size(); ++i) {
		if (_cards.at(i) != h._cards.at(i))  return false;
	}
	return true;
}

void CprHand::push_Card(const CprCard & c) {
	_cards.push_back(c);
}

void CprHand::pop_Card() {
	_cards.pop_back();
}

CprHand CprHand::GetUltimateHand() {
	return CprHand({ 10, 11, 12, 13, 1 }, HTStraightFlush);
}

CprHand CprHand::GetUltraPseudoHand() {
	return CprHand({ 10, 11, 12, 1, 1 }, HTStraightFlush);
}

HandType advanceType(HandType type) {
	return HandType((int)type + 1);
}