#include "CprTest.h"
#include "CprDef.h"
#include "CprHand.h"
#include "CprCollection.h"
#include "CprEachMaster.h"
#include "CprEachMasterTest.h"
#include <sstream>

CprTest::CprTest() {
}


CprTest::~CprTest() {
}

void CprTest::run() {
	// simple_test();
	// t1_determineType();
	// t2_containsType();
	// t3_testMaster();
	t4_testBruteForce();
}

bool iterateCards(const vector<int> nums, int idx, vector<int> mys) {
	for (unsigned i = idx; i < nums.size(); ++i) {
		mys.push_back(nums[i]);

		if (mys.size() == 5) {
			for (unsigned t = 0; t < mys.size(); ++t) {
				cout << mys.at(t) << " ";
			}
			cout << endl;
		}
		

		if (mys.size() == 5) {
			if ( mys[0] + mys[1] + mys[2] + mys[3] + mys[4] >= 30 ) {
				return true;
			} else {
				mys.pop_back();
			}
		} else {
			if (iterateCards(nums, i + 1, mys)) {
				return true;
			} else {
				mys.pop_back();
			}
		}
	}
	return false;
}

void CprTest::simple_test() {
	vector<int> A{1, 2, 3, 4, 5, 6, 7, 8, 9};
	vector<int> mys;
	iterateCards(A, 0, mys);
}

void CprTest::t1_determineType() {
	string str = "3d 5h 3s 5d 5c";
	istringstream in(str);
	CardList cards(5);
	for (int i = 0; i < 5; ++i) {
		in >> cards.at(i);
	}
	CprHand hand(cards);
	CprHandMaster::DetermineType(hand);
	hand.print(1);
}

void CprTest::t2_containsType() {
	string str = "3d 5h 3s 4h qc qh ad 9d 8h 6d 6h 5d 5c";
	istringstream in(str);
	CardList cards(13);
	for (int i = 0; i < 13; ++i) {
		in >> cards.at(i);
	}
	CprCollection col;
	col._cards = col._availCards = cards;

	CprHand bestHand = CprHandMaster::GetBestHand(col);
	bestHand.print(1);
}

#define T_MASTER CprFlushMaster
#define VAL(str) #str
#define TOSTRING(str) VAL(str)

void CprTest::t3_testMaster() {
	cout << "Testing " << TOSTRING(T_MASTER) << ":" << endl;
	CprEachMasterTest<T_MASTER> mtest;
	mtest.run();
}

void CprTest::t4_testBruteForce() {
	cout << "hello, type c to continue\n> ";
	int c;  cin >> c;
	
	for (int i = 0; i < 70000; ++i) {
		// cout << i << ' ' << flush;
		CprHand h1({ 3, 17, 19 });
		CprHand h2({ 11, 18, 20, 28, 35 });
		CprHand h3({ 19, 20, 14, 16, 7 });
		CprHandMaster::DetermineType(h1);
		CprHandMaster::DetermineType(h2);
		CprHandMaster::DetermineType(h3);
	}
}