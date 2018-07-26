/****************************************************************************
FileName   [ CprHandMaster.cpp ]
Synopsis   [ implement CprHandMaster member functions ]
****************************************************************************/

#include "CprHandMaster.h"
#include "CprCollection.h"
#include "CprHand.h"
#include "CprEachMaster.h"

CprHandMaster * CprHandMaster::CreateMaster(HandType type) {
	CprHandMaster* ms = 0;
	switch (type) {
	case HTStraightFlush:
		ms = new CprStraightFlushMaster();
		break;
	case HTFourOfAKind:
		ms = new CprFourOfAKindMaster();
		break;
	case HTFullHouse:
		ms = new CprFullHouseMaster();
		break;
	case HTFlush:
		ms = new CprFlushMaster();
		break;
	case HTStraight:
		ms = new CprStraightMaster();
		break;
	case HTThreeOfAKind:
		ms = new CprThreeOfAKindMaster();
		break;
	case HTTwoPair:
		ms = new CprTwoPairMaster();
		break;
	case HTOnePair:
		ms = new CprOnePairMaster();
		break;
	case HTHighCard:
		ms = new CprHighCardMaster();
		break;
	case HTXianggong:
	default:
		assert(false);
		break;
	}
	return ms;
}

CprHandMaster::CprHandMaster() {
}

CprHandMaster::~CprHandMaster() {
}

bool CprHandMaster::Compare(const CprHand& h1, const CprHand& h2) {
	// return true if h1 <= h2
	assert(h1._type != HTUndefined && h2._type != HTUndefined);
	if (h1.getType() != h2.getType()) {
		return h1._type < h2._type;
	} else if (h1.getType() == HTXianggong) {
		return true;
	} else {
		CprHandMaster* ms = CreateMaster(h1._type);
		bool rv = ms->compareDeeply(h1, h2);
		delete ms;
		return rv;
	}
}

void CprHandMaster::DetermineType(CprHand& hand) {
	CprHandMaster* ms;
	for (int i = HTHighestType; i >= HTLowestType; --i) {
		HandType type = HandType(i);
		ms = CreateMaster(type);
		if (ms->determineMe(hand)) {
			hand._type = type;
			ms->calcSubScore(hand);		// for CprBruteAi
			delete ms;
			return;
		}
		delete ms;
	}
	assert(false);
}

bool CprHandMaster::CheckCollectionCards(const CprCollection &col, const CardList &cards) {
	assert(cards.size() == 13);
	if (col._cards.size() != cards.size()) {
		return false;
	}
	for (int i = 0; cards.size(); ++i) {
		if (col._cards.at(i) != cards.at(i)) {
			return false;
		}
	}
	return true;
}

string CprHandMaster::traslateType(HandType type) {
	switch (type) {
	case HTStraightFlush:
		return "StraightFlush";
	case HTFourOfAKind:
		return "FourOfAKind";
	case HTFullHouse:
		return "FullHouse";
	case HTFlush:
		return "Flush";
	case HTStraight:
		return "Straight";
	case HTThreeOfAKind:
		return "ThreeOfAKind";
	case HTTwoPair:
		return "TwoPair";
	case HTOnePair:
		return "OnePair";
	case HTHighCard:
		return "HighCard";
	case HTXianggong:
		return "Xianggong";
	default:
		assert(false);
		return string();
	}
}

CprHand * CprHandMaster::ContainType(const CprCollection &, HandType) {
	return nullptr;
}

CprHand CprHandMaster::GetBestHand(const CprCollection& col) {
	return GetBestHandUnder(col, CprHand::GetUltraPseudoHand());
}
CprHand CprHandMaster::GetBestHandUnder(const CprCollection& col, const CprHand& upperHand) {
	// Find the best hand smaller than upperHand
	// 1. Find if there exists a second-best hand with same type as upperHand
	// 2. If not so, find the best hand with different type to upperHand
	CprHandMaster* ms;
	CprHand bestHand;
	
 	for (int i = upperHand._type; i >= 2; --i) {
		HandType type = HandType(i);
		ms = CreateMaster(type);
		bool b = false;

		if (type == upperHand._type) {
			b = ms->containsMeUnder(col, upperHand, bestHand);
		} else {
			b = ms->containsMe(col, bestHand);
		}
		if (b) {
			bestHand._type = type;
			ms->calcSubScore(bestHand);
			assert(bestHand.getSubScore() > 0);
			delete ms;
			return bestHand;
		} else {
			delete ms;
		}
	}
	assert(false);
	return CardList();
}

void CprHandMaster::CalculateSubScore(CprHand &hand) {
	assert(hand._type != HTUndefined);
	CprHandMaster *ms = CreateMaster(hand._type);
	ms->calcSubScore(hand);
	delete ms;
}


/* ----------------
	protected methods
	---------------- */

void CprHandMaster::recompCardsOfHand(CprHand &hand, const CardList& cards) {
	hand._cards = cards;
}


/* ----------------
   private methods
	---------------- */
