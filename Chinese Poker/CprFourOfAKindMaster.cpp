/****************************************************************************
FileName   [ CprFourOfAKindMaster.h ]
Synopsis   [ implement FourOfAKind master ]
****************************************************************************/

#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"

bool CprFourOfAKindMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	return h1.getCard(0) <= h2.getCard(0);
}
bool CprFourOfAKindMaster::determineMe(CprHand& hand) {
	if (hand.size() != 5)	return false;
	CardList* acr = hand.getACR();
	int rank1st = 0, rank2nd = 0;
	for (int i = 1; i <= 13; ++i) {
		if (acr[i].size() == 4) {
			rank1st = i;
		} else if (acr[i].size() == 1) {
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
}

bool CprFourOfAKindMaster::containsMe(const CprCollection& col, CprHand& res) {
	CprHand upperHand({ 1, 14, 27, 40, 1 }, HTFourOfAKind);	// AAAAA
	return containsMeUnder(col, upperHand, res, true);
}

bool CprFourOfAKindMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res, bool equal) {
	if (col._availCards.size() < 5)	return false;
	assert(uppHand.getType() == HTFourOfAKind);

	int uppRank1st = uppHand.getCard(0).rankA();
	int uppRank2nd = uppHand.getCard(4).rankA();

	const CardList* acr = col.getACR();
	for (int i = uppRank1st; i >= 2; --i) {
		if (acr[i].size() < 4)	continue;
		for (int j = 14; j >= 2; --j) {
			if (j == i)  continue;
			if (acr[j].size() < 1)	continue;
			if ( i > uppRank1st || (i == uppRank1st && j >= uppRank2nd)
				) {
				continue;
			} else {
				// i i i i j is a FullHouse
				assert(res._cards.empty());
				res._cards.insert(res._cards.end(), acr[i].begin(), acr[i].begin() + 4);
				res._cards.insert(res._cards.end(), acr[j].begin(), acr[j].begin() + 1);
				res._type = HTFourOfAKind;
				return true;
			}
		}
	}
	return false;
}

void CprFourOfAKindMaster::calcSubScore(CprHand& hand) {
	hand._subScoreI = (hand.at(0).rankA() << 4);
}