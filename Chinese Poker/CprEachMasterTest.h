#pragma once
#include <iostream>
#include "CprCollection.h"
#include "CprEachMaster.h"
using namespace std;

template <class T_M>
class CprEachMasterTest {
public:
	CprEachMasterTest() {}
	void run() {
		int type; cin >> type;	
		if (type == 0) {
			readHand(5);
			readHand(5);
			readHand(3);
			check_compare();
		} else if (type == 1) {
			readCollection();
			check_contain();
		} else {
			bool equal;
			cin >> equal;
			readCollection();
			readHand(5);
			check_contain_under(equal);
		}
	}
private:
	void readCollection() {
		CardList cards = readCards(13);
		std::sort(cards.begin(), cards.end());
		_col._cards = cards;
		_col._availCards = cards;
		_col.computeACR();
	}
	void readHand(int handSize) {
		CardList cards = readCards(handSize);
		if (handSize == 5) {
			if (_hand1.empty()) {
				_hand1._cards = cards;	
			} else {
				_hand2._cards = cards;
			}
		} else {
			_smallHand._cards = cards;
		}
	}
	void check_compare() {
		bool b1 = master.determineMe(_hand1);
		bool b2 = master.determineMe(_hand2);
		bool b3 = master.determineMe(_smallHand);
		cout << b1 << ' ' << b2 << ' ' << b3 << endl;
		if (b2 && b1) {
			cout << master.compareDeeply(_hand2, _hand1) << endl;
		}
		if (b3 && b2) {
			cout << master.compareDeeply(_smallHand, _hand2) << endl;	
		}
	}
	// under test_EachMaster.h
	void check_contain() {
		CprHand hand;
		bool b1 = master.containsMe(_col, hand);
		cout << b1 << endl;
		if (b1) {
			master.determineMe(hand);
			hand.print();
			cout << endl;
		}
	}
	void check_contain_under(bool equal) {
		CprHand hand;
		master.determineMe(_hand1);
		bool b1 = master.containsMeUnder(_col, _hand1, hand, equal);
		cout << b1 << endl;
		if (b1) {
			master.determineMe(hand);
			hand.print();
			cout << endl;
		}
	}
	CardList readCards(int n) {
		CardList cards;
		for (int i = 0; i < n; ++i) {
			CprCard c;
			cin >> c;
			cards.push_back(c);
		}
		cin.clear();
		return cards;
	}
	T_M master;
	CprCollection _col;
	CprHand _hand1;
	CprHand _hand2;
	CprHand _smallHand;
};

/*
### Usage ###
```
int main () {
	CprEachMasterTest<Cpr*Master> mtest;
	mtest.run();	
}
```

### Input Format ###
The first line is a integer 0 or 1
0: test determineMe and deeplyCompare
1: test comtainsMe

! For type 0 test:
TEST_TYPE
Five Cards for _hand1
Five Cards for _hand2
Three Cards for _smallHand

! For type 1 test:
TEST_TYPE
Thirteen cards for _col


### Output Format ###
! For type 0 test:
The first line indicates whether the three hands are of type *
The next line indicates whether _hand2 <= _hand1 (if exists)
The next line indicates whether _smallHand <= _hand2 (if exists)

! For type 1 test:
The first line indicates whether _col contains hand of type *
The second line are the 5 cards of best hand of type * (if exists)


### Sample Input & Sample Output ###
Please refer to test_*.cpp

*/