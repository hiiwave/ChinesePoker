/****************************************************************************
FileName   [ CprHighCardMaster.h ]
Synopsis   [ implement HighCard master ]
****************************************************************************/

#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"
#include <functional>

bool CprHighCardMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	int h1Score = 0, h2Score = 0;
	for (int i = 0; i < h1.size(); ++i) {
		h1Score += h1.getCard(i).rankA() << 4 * (4 - i);
		h2Score += h2.getCard(i).rankA() << 4 * (4 - i);
	}
	return h1Score <= h2Score;
}
bool CprHighCardMaster::determineMe(CprHand& hand) {
	std::sort(hand._cards.begin(), hand._cards.end(), c_greater);
	return true;
}

bool CprHighCardMaster::containsMe(const CprCollection& col, CprHand& res) {
	CprHand upperHand({ 1, 1, 1, 1, 1 }, HTHighCard);	// AAAAA
	return containsMeUnder(col, upperHand, res, true);
}

bool iterate5Cards(const CardList& Cards, int idx, CardList& cs, std::function<bool(CardList cs_)> done) {
	for (unsigned i = idx; i < Cards.size(); ++i) {
		cs.push_back(Cards.at(i));
		if (cs.size() == 5) {
			if (done(cs)) {
				return true;
			} else {
				cs.pop_back();
			}
		} else {
			if (iterate5Cards(Cards, i + 1, cs, done)) {
				return true;
			} else {
				cs.pop_back();
			}
		}
	}
	return false;
}

bool CprHighCardMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res, bool equal) {
	CardList avaCards = col.getAvailableCards();
	std::sort(avaCards.begin(), avaCards.end(), c_greater);
	int handSize = (col._cards.size() < 5) ? 3 : 5;

	CardList cs;
	iterate5Cards(avaCards, 0, cs, [this, uppHand](CardList cs_) {
		return !(this->compareDeeply(uppHand, CprHand(cs_, HTHighCard))) ;
	});
	assert(cs.size() == 5);
	res._cards.insert(res._cards.end(), cs.begin(), cs.end());
	res._type = HTHighCard;
	return true;
}

void CprHighCardMaster::calcSubScore(CprHand& hand) {
	hand._subScoreI = (hand.at(0).rankA() << 4) + hand.at(1).rankA();
}