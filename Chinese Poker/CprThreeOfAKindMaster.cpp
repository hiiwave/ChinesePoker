/****************************************************************************
FileName   [ CprThreeOfAKindMaster.h ]
Synopsis   [ implement ThreeOfAKind master ]
****************************************************************************/

#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"

bool CprThreeOfAKindMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	return h1.getCard(0) <= h2.getCard(0);
}
bool CprThreeOfAKindMaster::determineMe(CprHand& hand) {
	if (hand.size() == 3) {
		return hand._cards[0].rank() == hand._cards[1].rank() && 
			hand._cards[0].rank() == hand._cards[2].rank();
	}
	assert(hand.size() == 5);
	CardList* acr = hand.getACR();
	int rk3 = 0;
	for (int i = 1; i <= 13; ++i) {
		if (acr[i].size() >= 3) {
			rk3 = i;
		}
	}
	if (rk3 == 0) {
		delete[] acr;
		return false;
	} else {
		CardList res;
		for (int i = 0; i < 3; ++i) {
			for (CardList::iterator it = hand._cards.begin(); it != hand._cards.end();) {
				if (*it == acr[rk3].at(i)) {
					it = hand._cards.erase(it);
				} else {
					++it;
				}
			}
		}
		assert(hand.size() == 2);
		std::sort(hand._cards.begin(), hand._cards.end(), c_greater);
		res.insert(res.end(), acr[rk3].begin(), acr[rk3].begin() + 3);
		res.insert(res.end(), hand._cards.begin(), hand._cards.end());
		hand._cards = res;
		delete[] acr;
		return true;
	}
}

bool CprThreeOfAKindMaster::containsMe(const CprCollection& col, CprHand& res) {
	CprHand upperHand({ 1, 14, 27, 1, 14 }, HTThreeOfAKind);	// AAAAA
	return containsMeUnder(col, upperHand, res);
}

bool CprThreeOfAKindMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res, bool equal) {
	if (col._availCards.size() < 5) {
		return false;
	}
	assert(col._availCards.size() >= 5);
	assert(uppHand.getType() == HTThreeOfAKind);

	int uppRank1st = uppHand.getCard(0).rankA();
	const CardList* acr = col.getACR();
	for (int i = uppRank1st; i >= 2; --i) {
		if (acr[i].size() < 3)	continue;
		// i i i is a threeOfAKind
		assert(res.empty());
		CardList resCards;
		resCards.insert(resCards.end(), acr[i].begin(), acr[i].begin() + 3);
		CardList avails(col._availCards.size() - 3);
		auto it = std::set_difference(col._availCards.begin(), col._availCards.end(), 
			resCards.begin(), resCards.end(), avails.begin());
		assert(it == avails.end());
			
		std::sort(avails.begin(), avails.end(), c_greater);
		for (unsigned i = 0; i < avails.size() - 1; ++i) {
			for (unsigned j = i + 1; j < avails.size(); ++j) {
				if ((avails[i].rankA() << 4) + avails[j].rankA() <
				 	(uppHand.getCard(3).rankA() << 4) + uppHand.getCard(4).rankA()
					) {
					resCards.push_back(avails[i]);
					resCards.push_back(avails[j]);
					res = CprHand(resCards, HTThreeOfAKind);
					return true;
				}
			}
		}		
	}
	return false;
}

void CprThreeOfAKindMaster::calcSubScore(CprHand& hand) {
	hand._subScoreI = (hand.at(0).rankA() << 4);
}