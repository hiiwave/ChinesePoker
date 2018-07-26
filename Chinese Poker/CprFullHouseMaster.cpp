/****************************************************************************
FileName   [ CprFullHouseMaster.h ]
Synopsis   [ implement FullHouse master ]
****************************************************************************/

#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"

bool CprFullHouseMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	assert(h1.getCard(0).rank() == h1.getCard(1).rank() &&
		h1.getCard(0).rank() == h1.getCard(2).rank());
	assert(h2.getCard(0).rank() == h2.getCard(1).rank() &&
		h2.getCard(0).rank() == h2.getCard(2).rank());
	return h1.getCard(0) <= h2.getCard(0);
}
bool CprFullHouseMaster::determineMe(CprHand& hand) {
	if (hand.size() != 5)	return false;

	CardList* acr = hand.getACR();
	int rank1st = 0, rank2nd = 0;
	for (int i = 1; i <= 13; ++i) {
		if (acr[i].size() == 3) {
			rank1st = i;
		} else if (acr[i].size() == 2) {
			rank2nd = i;
		}
	}
	if (rank1st == 0 || rank2nd == 0) {
		delete[] acr;
		return false;
	} else {
		CardList cards;
		cards.insert(cards.end(), acr[rank1st].begin(), acr[rank1st].end());
		cards.insert(cards.end(), acr[rank2nd].begin(), acr[rank2nd].end());
		hand._cards = cards;
		delete[] acr;
		return true;
	}
	/*
	CardList cards = hand.getCards();
	std::sort(cards.begin(), cards.end(), c_ordinal);

	// 1. Check if isMyType
	int rankA = cards.front().rank(), rankB = 0;
	CardList listA, listB;
	listA.push_back(cards.front());
	for (int i = 1; i < 5; ++i) {
	CprCard& c = cards.at(i);
	if (rankB > 0) {
	if (c.rank() > rankB) {
	return false;
	} else {
	assert(c.rank() == rankB);
	listB.push_back(c);
	}
	} else {
	if (c.rank() > rankA) {
	rankB = c.rank();
	listB.push_back(c);
	} else {
	assert(c.rank() == rankA);
	listA.push_back(c);
	}
	}
	}

	// 2. myType detected. Recompose hand
	CardList recompCards;
	if (listA.size() > listB.size()) {
	assert(listA.size() == 3 && listB.size() == 2);
	recompCards.insert(recompCards.end(), listA.begin(), listA.end());
	recompCards.insert(recompCards.end(), listB.begin(), listB.end());
	} else {
	assert(listA.size() == 2 && listB.size() == 3);
	recompCards.insert(recompCards.end(), listB.begin(), listB.end());
	recompCards.insert(recompCards.end(), listA.begin(), listA.end());
	}
	recompCardsOfHand(hand, recompCards);
	*/
}

bool CprFullHouseMaster::containsMe(const CprCollection& col, CprHand& res) {
	CprHand upperHand({ 1, 14, 27, 13, 26 }, HTFullHouse);	// AAAKK
	return containsMeUnder(col, upperHand, res, true);
}

bool CprFullHouseMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res, bool equal) {
	if (col._availCards.size() < 5)	return false;
	assert(uppHand.getType() == HTFullHouse);
	assert(uppHand.getCard(0).rank() == uppHand.getCard(1).rank() &&
		uppHand.getCard(0).rank() == uppHand.getCard(2).rank());
	int uppRank1st = uppHand.getCard(0).rankA();
	int uppRank2nd = uppHand.getCard(3).rankA();

	const CardList* acr = col.getACR();
	for (int i = uppRank1st; i >= 2; --i) {
		if (acr[i].size() < 3)	continue;
		for (int j = 14; j >= 2; --j) {
			if (j == i)  continue;
			if (acr[j].size() < 2)	continue;
			if ( (!equal && ((i << 4) + j >= (uppRank1st << 4) + uppRank2nd)) ||
				  ( equal && ((i << 4) + j >  (uppRank1st << 4) + uppRank2nd)) 
				) {
				continue;
			} else {
				// i i i j j is a FullHouse
				assert(res._cards.empty());
				res._cards.insert(res._cards.end(), acr[i].begin(), acr[i].begin() + 3);
				res._cards.insert(res._cards.end(), acr[j].begin(), acr[j].begin() + 2);
				res._type = HTFullHouse;
				return true;
			}
		}
	}
	return false;
}

void CprFullHouseMaster::calcSubScore(CprHand& hand) {
	hand._subScoreI = (hand.at(0).rankA() << 4);
}