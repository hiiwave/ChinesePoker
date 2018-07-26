#include "CprBruteAi.h"

CprBruteAi::CprBruteAi(double pow, double multi1st)
	: _pow(pow), _mult1st(multi1st) {
}

CprBruteAi::~CprBruteAi() {
}

static void generateHands(const CardList& cards, HandList& res, CprHand& current, int start, int handSize = 5) {
	if (current.size() == handSize) {
		CprHand hand = current;
		// hand.print(); cout << endl;
		
		// FIXME: test
		CprHandMaster::DetermineType(hand);	// will sort hand
		res.push_back(hand);
		return;
	}
	for (unsigned i = start; i < cards.size(); ++i) {
		current.push_Card(cards[i]);
		generateHands(cards, res, current, i + 1, handSize);
		current.pop_Card();
	}
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

void CprBruteAi::playerStrategy() {
	double maxScore = -1;
	CprCollection maxCollection;

	HandList hand1s;
	CprHand tmp;
	generateHands(_collection.getAvailableCards(), hand1s, tmp, 0, 3);

	int count = 0;	// up to C13_3 = 143*6 = 286

	for (CprHand& h1 : hand1s) {
		// cout << ++count << " " << flush;
		_collection.settingHand(0, h1);
		CprCollection colAfter1 = _collection;
		HandList hand2s;
		CprHand tmp2;
		generateHands(colAfter1.getAvailableCards(), hand2s, tmp2, 0, 5);	
		for (CprHand& h2 : hand2s) {
			if (!(h1 <= h2)) {
				continue;
			}
			_collection.settingHand(1, h2);
			CprHand h3(_collection.getAvailableCards());
			if (h3.size() != 5) {
				CprHand hhhh = h2;
				cout << "Q" << endl;
			}

			assert(h3.size() == 5);
			CprHandMaster::DetermineType(h3);
			if (!(h2 <= h3)) {
				_collection = colAfter1;
				continue;
			}
			_collection.settingFinalHand();
			
			double score = calculateScore();
			if (score > maxScore) {
				maxScore = score;
				maxCollection = _collection;
			}
			_collection = colAfter1;
		}
		_collection.resetAllHands();		
	}
	assert(maxCollection.isValidSet());
	_collection = maxCollection;
}

double CprBruteAi::calculateScore() {
	CprHand h1 = _collection.getHand(0);
	CprHand h2 = _collection.getHand(1);
	CprHand h3 = _collection.getHand(2);

	double h1Score = _mult1st * ST(h1);
	double h2Score = ST(h2);
	double h3Score = ST(h3);
	return h1Score + h2Score + h3Score;
}

double CprBruteAi::ST(const CprHand& hand) {
	double rv;
	double diff = ST(advanceType(hand.getType())) - ST(hand.getType());
	diff *= 0.5;
	diff *= hand.getSubScore();
	rv = ST(hand.getType()) + diff;
	assert(rv > ST(hand.getType()) && rv < ST(advanceType(hand.getType())));
	return rv;
}

double CprBruteAi::ST(HandType type) {
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