/****************************************************************************
FileName   [ CprStraightMaster.h ]
Synopsis   [ implement Straight master ]
****************************************************************************/

#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"

bool CprStraightMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	return h1.getCard(4) <= h2.getCard(4);
}
bool CprStraightMaster::determineMe(CprHand& hand) {
	if (hand.size() != 5)	return false;
	CardList cards = hand.getCards();
	std::sort(cards.begin(), cards.end(), c_ordinal);

	bool ultimateStraight = (cards[0].rank() == 1 && cards[1].rank() == 10 && cards[2].rank() == 11
		&& cards[3].rank() == 12 && cards[4].rank() == 13);
	for (int i = 1; i < 5; ++i) {
		if (!ultimateStraight && cards.at(i).rank() - cards.at(i - 1).rank() != 1) {
			return false;
		}
	}
	if (ultimateStraight) {
		CardList res;
		res.insert(res.begin(), cards.begin() + 1, cards.end());
		res.push_back(cards.front());
		hand._cards = res;
	} else {
		hand._cards = cards;
	}
	return true;
}

bool CprStraightMaster::containsMe(const CprCollection& col, CprHand& res) {
	CprHand upperHand({ 10, 11, 12, 13, 1 }, HTStraight);
	return containsMeUnder(col, upperHand, res, true);
}

bool CprStraightMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res, bool equal) {
	if (col._availCards.size() < 5)	return false;
	assert(uppHand.getType() == HTStraight);
	int uppRank = uppHand.getCard(4).rankA();
	if (!equal) {
		--uppRank;
	}
	CardList straight;
	const CardList* acr = col.getACR();
	for (int i = uppRank; i >= 2; --i) {
		if (!acr[i].empty()) {
			// FIXME: which to choose when there are multiple cards?
			straight.push_back(acr[i].front());
		} else {
			straight.clear();
		}
		if (straight.size() == 5) {
			assert(res._cards.empty());
			std::sort(straight.begin(), straight.end(), c_less);
			res._cards = straight;
			res._type = HTStraight;
			return true;
		}
	}
	return false;
}

void CprStraightMaster::calcSubScore(CprHand& hand) {
	hand._subScoreI = (hand.at(4).rankA() << 4);
}