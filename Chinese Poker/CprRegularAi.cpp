/****************************************************************************
FileName   [ CprRegularAi.cpp ]
Synopsis   [ implement a regular AI strategy ]
****************************************************************************/

#include "CprRegularAi.h"

int CprRegularAi::RegularCount = 0;

CprRegularAi::CprRegularAi(double pow, double multi1st)
	: _pow(pow), _mult1st(multi1st) {
}

CprRegularAi::~CprRegularAi() {
}

template<class T> bool sameVec(const vector<T>& v1, const vector<T>& v2) {
	if (v1.size() != v2.size())  return false;
	for (unsigned i = 0; i < v1.size(); ++i) {
		if (v1.at(i) != v2.at(i)) {
			return false;
		}
	}
	return true;
}

static bool d_checkCards(const CprCollection& col) {
	// DEBUG purpose
	bool b = true;
	b &= sameVec(col.getHand(2).getCards(), CardList{ 1, 13, 11, 5, 4 });
	b &= sameVec(col.getHand(1).getCards(), CardList{ 26, 25, 24, 21, 20 });
	b &= sameVec(col.getHand(0).getCards(), CardList{ 43, 19, 36 });
	return b;
}

void CprRegularAi::playerStrategy() {
	double maxScore = -1;
	CprCollection maxCollection;
	CprHand uppHand3 = CprHand::GetUltraPseudoHand();
	CprHand uppHand2 = CprHand::GetUltraPseudoHand();
	for (int i = 0; i < RepeatTime; ++i) {
		CprHand hand3 = CprHandMaster::GetBestHandUnder(collection(), uppHand3);
		uppHand3 = hand3;
		if (!(CprHandMaster::GetBestHand(collection()) <= hand3)) {
			break;
		}
		uppHand2 = CprHand::GetUltraPseudoHand();
		for (int j = 0; j < RepeatTime; ++j) {
			assert(collection().settingHand(2, hand3));
			CprHand hand2 = CprHandMaster::GetBestHandUnder(collection(), uppHand2);
			assert(collection().settingHand(1, hand2));

			uppHand2 = hand2;
			collection().settingFinalHand();
			const CprHand& hand1 = collection().getHand(0);

			// cout << "RegularCount = " << RegularCount << endl;
			//if (RegularCount >= 0) {	// 360
			// // DEBUG purpose
			//	cout << "RegularCount = " << RegularCount << endl;
			//	_collection.showCollection(1);	
			//	int a;
			//}

			if (!(hand1 <= hand2)) {
				collection().resetAllHands();
				break;
			}

			double score = calculateScore();
			if (score > maxScore) {
				if (maxScore != -1) {
					// cout << "Seldom happen.." << endl;
				}
				maxScore = score;
				maxCollection = _collection;
				/*if (d_checkCards(maxCollection)) {
					cout << "RegularCount = " << RegularCount << endl;
					cout << "Ohoh.." << endl;
				}*/
			} 
			collection().resetAllHands();
			++RegularCount;
		}
	}
	assert(maxCollection.isValidSet());
	_collection = maxCollection;	
}

double CprRegularAi::calculateScore() {
	CprHand h1 = _collection.getHand(0);
	CprHand h2 = _collection.getHand(1);
	CprHand h3 = _collection.getHand(2);
	
	double h1Score = _mult1st * ST(h1);
	double h2Score = ST(h2);
	double h3Score = ST(h3);
	return h1Score + h2Score + h3Score;
}



double CprRegularAi::ST(const CprHand& hand) {
	double rv;
	double diff = ST(advanceType(hand.getType())) - ST(hand.getType());
	diff *= 0.5;
	diff *= hand.getSubScore();
	rv = ST(hand.getType()) + diff;
	assert(rv > ST(hand.getType()) && rv < ST(advanceType(hand.getType())));
	return rv;
}

double CprRegularAi::ST(HandType type) {
	return pow((int)type, _pow);
	/*
	switch (type) {
	case HTStraightFlush:
	return 10;
	case HTFourOfAKind:
	return 9;
	case HTFullHouse:
	return 8;
	case HTFlush:
	return 7;
	case HTStraight:
	return 6;
	case HTThreeOfAKind:
	return 5;
	case HTTwoPair:
	return 4;
	case HTOnePair:
	return 3;
	case HTHighCard:
	return 2;
	default:
	assert(false);
	return 0;
	}
	*/
}