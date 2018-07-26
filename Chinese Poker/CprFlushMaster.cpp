/****************************************************************************
FileName   [ CprFlushMaster.h ]
Synopsis   [ implement Flush master ]
****************************************************************************/

#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"

bool CprFlushMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	int h1Score = 0, h2Score = 0;
	for (int i = 0; i < h1.size(); ++i) {
		h1Score += h1.getCard(i).rankA() << 4 * (4 - i);
		h2Score += h2.getCard(i).rankA() << 4 * (4 - i);
	}
	return h1Score <= h2Score;
}
bool CprFlushMaster::determineMe(CprHand& hand) {
	if (hand.size() < 5)  return false;
	int suit = hand.getCard(0).suit();
	for (const CprCard& c : hand._cards) {
		if (c.suit() != suit) {
			return false;
		}
	}
	std::sort(hand._cards.begin(), hand._cards.end(), c_greater);
	return true;
}

bool CprFlushMaster::containsMe(const CprCollection& col, CprHand& res) {
	CprHand upperHand({ 1, 1, 1, 1, 1 }, HTFlush);	// AAAAA
	return containsMeUnder(col, upperHand, res, true);
}

bool CprFlushMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res, bool equal) {
	CardList cards = col.getAvailableCards();
	assert(std::is_sorted(cards.begin(), cards.end()));
	int suit = cards.front().suit();
	int suitCount = 1;

	for (unsigned i = 1; i < cards.size(); ++i) {
		const CprCard& c = cards.at(i);
		if (cards.at(i).suit() != suit) {
			suit = cards.at(i).suit(); 
			suitCount = 1;
		} else {
			++suitCount;
		}
		if (suitCount >= 5) {
			CprHand candidate;
			candidate._type = HTFlush;
			candidate._cards.insert(candidate._cards.end(), cards.begin() + i - 4, cards.begin() + i + 1);
			std::sort(candidate._cards.begin(), candidate._cards.end(), c_greater);
			if (!compareDeeply(uppHand, candidate)) {
				if (res.empty()) {
					res = candidate;
				} else if (compareDeeply(res, candidate)) {
					res = candidate;
				}
			}
		}
	}
	if (!res.empty()) {
		return true;
	} else {
		return false;
	}
}

void CprFlushMaster::calcSubScore(CprHand& hand) {
	hand._subScoreI = (hand.at(0).rankA() << 4) + hand.at(1).rankA();
}