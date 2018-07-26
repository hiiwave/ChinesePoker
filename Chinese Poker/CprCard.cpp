/****************************************************************************
FileName   [ CprCard.cpp ]
Synopsis   [ implement CprCard member functions ]
****************************************************************************/

#include "CprCard.h"
#include <sstream>

CprCard::CprCard() : _cardId(-1) {
}

CprCard::CprCard(int id) : _cardId(id) {}

CprCard::~CprCard() {}

int CprCard::suit() const {
	return 1 + (_cardId - 1) / 13;
}
int CprCard::rank() const {
	return (_cardId % 13) ? (_cardId % 13) : 13;
}
int CprCard::rankA() const {
	return (rank() == 1)? 14: rank();
}

int CprCard::getCardId() const {
	return _cardId;
}

bool CprCard::operator<=(const CprCard &c) const {
	int r1 = rank(), r2 = c.rank();
	if (r1 == 1)  r1 = 14;
	if (r2 == 1)  r2 = 14;
	return r1 <= r2;
}

bool CprCard::operator < (const CprCard& card) const {
	return _cardId < card._cardId;
}
bool CprCard::operator == (const CprCard& card) const {
	return _cardId == card._cardId;
}
bool CprCard::operator != (const CprCard& card) const {
	return _cardId != card._cardId;
}

int CprCard::SuitFromChar(const char c) {
	int suit;
	switch (c) {
	case 'c':
	case 'C':
		suit = 0;
		break;
	case 'd':
	case 'D':
		suit = 1;
		break;
	case 'h':
	case 'H':
		suit = 2;
		break;
	case 's':
	case 'S':
		suit = 3;
		break;
	default:
		suit = -1;
	}
	return suit;
}

int CprCard::RankFromChar(const char c) {
	int rank;
	switch (c) {
	case 'A':
	case 'a':
		rank = 1;
		break;
	case 'J':
	case 'j':
		rank = 11;
		break;
	case 'Q':
	case 'q':
		rank = 12;
		break;
	case 'K':
	case 'k':
		rank = 13;
		break;
	default:
		rank = -1;
	}
	return rank;
}

void CprCard::setting(int suit, int rank) {
	_cardId = suit * 13 + rank;
}

ostream& operator << (ostream& os, const CprCard& c) {
	switch (c.rank()) {
	case 1:
		os << "A";
		break;
	case 11:
		os << "J";
		break;
	case 12:
		os << "Q";
		break;
	case 13:
		os << "K";
		break;
	default:
		os << c.rank();
	}
	switch (c.suit()) {
	case 1:
		os << "c";
		break;
	case 2:
		os << "d";
		break;
	case 3:
		os << "h";
		break;
	case 4:
		os << "s";
		break;
	default:
		assert(false);
	}
	return os;
}

istream& operator >> (istream& is, CprCard& c) {
	string str;
	is >> str;
	if (str.empty()) {
		is.clear(ios::failbit);
		return is;
	}

	// 1. parse suit
	int suit = CprCard::SuitFromChar(str.back());
	if (suit == -1) {
		is.clear(ios::failbit);
		return is;
	}
	str.pop_back();

	// 2. parse rank
	istringstream in(str);
	int rank;
	if (in >> rank) {
	} else if (str.size() == 1) {
		rank = CprCard::RankFromChar(str.back());
	} else {
		rank = -1;
	}
	if (rank > 0 && rank <= 13) {
		c.setting(suit, rank);
	} else {
		is.clear(ios::failbit);
	}
	return is;
}

// in CprCard.cpp
// global function implementation
bool c_less(const CprCard& c1, const CprCard& c2) {
	if (c1 <= c2 && c2 <= c1) {
		assert(c1.rank() == c2.rank());
		return c1.suit() < c2.suit();
	} else {
		return c1 <= c2;
	}
}
bool c_greater(const CprCard& c1, const CprCard& c2) {
	if (c1 <= c2 && c2 <= c1) {
		assert(c1.rank() == c2.rank());
		return c1.suit() < c2.suit();
	} else {
		return !(c1 <= c2);
	}
}
bool c_ordinal(const CprCard& c1, const CprCard& c2) {
	if (c1.rank() != c2.rank()) {
		return c1.rank() < c2.rank();
	} else {
		return c1.suit() < c2.suit();
	}
}