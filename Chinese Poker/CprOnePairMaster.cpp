/****************************************************************************
FileName   [ CprOnePairMaster.h ]
Synopsis   [ implement OnePair master ]
****************************************************************************/

#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"

bool CprOnePairMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	int h1Score = 0, h2Score = 0;
	for (int i = 0; i < h1.size(); ++i) {
		h1Score += h1.getCard(i).rankA() << 4 * (4 - i);
		h2Score += h2.getCard(i).rankA() << 4 * (4 - i);
	}
	return h1Score <= h2Score;
}
bool CprOnePairMaster::determineMe(CprHand& hand) {
	if (hand.size() == 3) {
		CardList& cards = hand._cards;
		if (cards.at(0).rank() == cards.at(1).rank()) {			
		} else if (cards.at(0).rank() == cards.at(2).rank()) {
			std::swap(cards.at(1), cards.at(2));
		} else if (cards.at(1).rank() == cards.at(2).rank()) {
			std::swap(cards.at(0), cards.at(2));
		} else {
			return false;
		}
		std::sort(cards.begin(), cards.begin() + 1);
		return true;
	}
	assert(hand.size() == 5);
	CardList* acr = hand.getACR();
	int rk2 = 0;
	for (int i = 1; i <= 13; ++i) {
		if (acr[i].size() >= 2) {
			rk2 = i;
		}
	}
	if (rk2 == 0) {
		delete[] acr;
		return false;
	} else {
		CardList res;
		for (int i = 0; i < 2; ++i) {
			for (CardList::iterator it = hand._cards.begin(); it != hand._cards.end();) {
				if (*it == acr[rk2].at(i)) {
					it = hand._cards.erase(it);
				} else {
					++it;
				}
			}
		}
		assert(hand.size() == 3);
		std::sort(hand._cards.begin(), hand._cards.end(), c_greater);
		res.insert(res.end(), acr[rk2].begin(), acr[rk2].begin() + 2);
		res.insert(res.end(), hand._cards.begin(), hand._cards.end());
		hand._cards = res;
		delete[] acr;
		return true;
	}
}

bool CprOnePairMaster::containsMe(const CprCollection& col, CprHand& res) {
	CprHand upperHand({ 1, 1, 1, 1, 1 }, HTOnePair);	// AAAAA
	return containsMeUnder(col, upperHand, res);
}

bool CprOnePairMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res, bool equal) {
	if (col._availCards.size() < 5) {
		return false;
	}
	assert(col._availCards.size() >= 5);
	assert(uppHand.getType() == HTOnePair);

	int uppRank1st = uppHand.getCard(0).rankA();
	const CardList* acr = col.getACR();
	for (int i = uppRank1st; i >= 2; --i) {
		if (acr[i].size() < 2)	continue;
		for (int j1 = 14; j1 >= 2; --j1) {
			if (j1 == i || acr[j1].empty()) continue;
			for (int j2 = j1 - 1; j2 >= 2; --j2) {
				if (j2 == i || acr[j2].empty()) continue;
				for (int j3 = j2 - 1; j3 >= 2; --j3) {
					if (j3 == i || acr[j3].empty()) continue;
					// ongoing
					CardList cards = CardList(acr[i].begin(), acr[i].begin() + 2);
					cards.push_back(acr[j1].front());
					cards.push_back(acr[j2].front());
					cards.push_back(acr[j3].front());
					if (!compareDeeply(uppHand, CprHand(cards, HTOnePair))) {
						res = cards;
						res._type = HTOnePair;
						return true;
					}
				}
			}
		}
	}
	return false;
}

void CprOnePairMaster::calcSubScore(CprHand& hand) {
	hand._subScoreI = (hand.at(0).rankA() << 4) + hand.at(2).rankA();
}