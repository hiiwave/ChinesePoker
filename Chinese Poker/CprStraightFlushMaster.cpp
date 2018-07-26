/****************************************************************************
FileName   [ CprStraightFlushMaster.h ]
Synopsis   [ implement StraightFlush master ]
****************************************************************************/

#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"

bool CprStraightFlushMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	return h1.getCard(4).rankA() + h1.getCard(3).rankA() <= h2.getCard(4).rankA() + h2.getCard(3).rankA();
}
bool CprStraightFlushMaster::determineMe(CprHand& hand) {
	if (hand.size() != 5)	return false;
	CardList cards = hand.getCards();
	std::sort(cards.begin(), cards.end(), c_ordinal);

	int suit = cards.front().suit();
	
	bool ultimateStraight = (cards[0].rank() == 1 && cards[1].rank() == 10 && cards[2].rank() == 11 
		&& cards[3].rank() == 12 && cards[4].rank() == 13);
	for (int i = 1; i < 5; ++i) {
		if (cards.at(i).suit() != suit) {
			return false;
		} else if (!ultimateStraight && cards.at(i).rank() - cards.at(i - 1).rank() != 1) {
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

bool CprStraightFlushMaster::containsMe(const CprCollection& col, CprHand& res) {
	CprHand upperHand({ 10, 11, 12, 1, 1 }, HTStraightFlush);
	return containsMeUnder(col, upperHand, res);
}

bool CprStraightFlushMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res, bool equal) {
	if (col._availCards.size() < 5)	return false;
	assert(uppHand.getType() == HTStraightFlush);
	int uppRank = uppHand.getCard(4).rankA();

	CardList cards = col._availCards;
	assert(std::is_sorted(cards.begin(), cards.end()));
	vector<CardList> candies;	// candidates
	int suit = cards.front().suit();
	int suit_first = 0;
	int straightCount = 1;
	bool existA = cards.front().rank() == 1;
	
	for (unsigned i = 1; i < cards.size(); ++i) {
		const CprCard& c = cards.at(i);
		if (c.suit() != suit) {
			suit = c.suit();
			suit_first = i;
			straightCount = 1;
			existA = cards.at(i).rank() == 1;
		} else if (cards.at(i).rank() - cards.at(i - 1).rank() == 1) {
			++straightCount;
		} else {
			straightCount = 1;
		}
		if (straightCount >= 5) {
			if (straightCount > 5)	candies.pop_back();
			CardList candy = CardList(cards.begin() + i - 4, cards.begin() + i + 1);
			candies.push_back(candy);
		}
		if (straightCount >= 4 && existA && cards.at(i).rank() == 13) {
			// 10JQKA
			CardList candy = CardList(cards.begin() + i - 3, cards.begin() + i + 1);
			candy.push_back(cards.at(suit_first));
			candies.push_back(candy);
		}
	}
	if (candies.empty()) {
		return false;
	} else {
		std::sort(candies.begin(), candies.end(), [](const CardList& cs1, const CardList& cs2) {
			return cs1.back().rankA() < cs2.back().rankA();
		});
		for (int i = 0; i < (int)candies.size(); ++i) {
			if (compareDeeply(uppHand, candies.at(i))) {
				candies.erase(candies.begin() + i, candies.end());
				break;
			}
		}
		if (candies.empty())  return false;
		CardList selected = candies.back();
		std::sort(selected.begin(), selected.end(), c_less);
		res = CprHand(selected, HTStraightFlush);
		return true;
	}
}

void CprStraightFlushMaster::calcSubScore(CprHand& hand) {
	hand._subScoreI = (hand.at(4).rankA() << 4);
}