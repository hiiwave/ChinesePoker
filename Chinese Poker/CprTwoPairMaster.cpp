/****************************************************************************
FileName   [ CprTwoPairMaster.h ]
Synopsis   [ implement TwoPair master ]
****************************************************************************/

#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"

bool CprTwoPairMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	int h1Score = (h1._cards[0].rankA() << 8) + (h1._cards[2].rankA() << 4) + (h1._cards[4].rankA());
	int h2Score = (h2._cards[0].rankA() << 8) + (h2._cards[2].rankA() << 4) + (h2._cards[4].rankA());
	return h1Score <= h2Score;
}
bool CprTwoPairMaster::determineMe(CprHand& hand) {
	if (hand.size() != 5)	return false;
	CardList* acr = hand.getACR();
	int rk2_1 = 0, rk2_2 = 0, rk1 = 0;
	for (int i = 2; i <= 14; ++i) {
		if (acr[i].size() == 2) {
			if (rk2_1 == 0) {
				rk2_1 = i;
			} else {
				rk2_2 = i;
			}
		} else if (acr[i].size() == 1) {
			rk1 = i;
		}
	}
	if (rk2_1 == 0 || rk2_2 == 0 || rk1 == 0) {
		delete[] acr;
		return false;
	} else {
		CardList res;
		if (rk2_2 > rk2_1) {
			int tmp = rk2_1;
			rk2_1 = rk2_2;
			rk2_2 = tmp;
		}
		res.insert(res.end(), acr[rk2_1].begin(), acr[rk2_1].end());
		res.insert(res.end(), acr[rk2_2].begin(), acr[rk2_2].end());
		res.push_back(acr[rk1].front());
		hand._cards = res;
		delete[] acr;
		return true;
	}
}

bool CprTwoPairMaster::containsMe(const CprCollection& col, CprHand& res) {
	CprHand upperHand({ 1, 1, 1, 1, 1}, HTTwoPair);	// AAAAA
	return containsMeUnder(col, upperHand, res);
}

bool CprTwoPairMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res, bool equal) {
	if (col._availCards.size() < 5)	return false;
	assert(uppHand.getType() == HTTwoPair);
	int uppRank1st = uppHand.getCard(0).rankA();
	int uppRank2nd = uppHand.getCard(2).rankA();
	int uppRank3rd = uppHand.getCard(4).rankA();

	const CardList* acr = col.getACR();
	for (int i = uppRank1st; i >= 2; --i) {
		if (acr[i].size() < 2)	continue;
		for (int j = i - 1; j >= 2; --j) {
			if (acr[j].size() < 2)	continue;
			for (int k = 14; k >= 2; --k) {
				if (k == i || k == j)  continue;
				if (acr[k].empty())  continue;
				// i i j j k is a TwoPair
				if ( (i << 8) + (j << 4) + k >= 
					  (uppRank1st << 8) + (uppRank2nd << 4) + uppRank3rd
					) {
					continue;
				} else {
					assert(res._cards.empty());
					res._cards.insert(res._cards.end(), acr[i].begin(), acr[i].begin() + 2);
					res._cards.insert(res._cards.end(), acr[j].begin(), acr[j].begin() + 2);
					res._cards.push_back(acr[k].front());
					res._type = HTTwoPair;
					return true;
				}
			}	
		}
	}
	return false;
}

void CprTwoPairMaster::calcSubScore(CprHand& hand) {
	hand._subScoreI = (hand.at(0).rankA() << 4) + hand.at(2).rankA();
}