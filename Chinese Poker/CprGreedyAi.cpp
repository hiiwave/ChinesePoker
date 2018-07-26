/****************************************************************************
FileName   [ CprGreedyAi.cpp ]
Synopsis   [ implement a greedy AI strategy ]
****************************************************************************/

#include "CprGreedyAi.h"

CprGreedyAi::CprGreedyAi() {
}


CprGreedyAi::~CprGreedyAi() {
}

void CprGreedyAi::playerStrategy() {
	CprHand hand3 = CprHandMaster::GetBestHand(collection());
	assert(collection().settingHand(2, hand3));
	CprHand hand2 = CprHandMaster::GetBestHand(collection());
	assert(collection().settingHand(1, hand2));
	collection().settingFinalHand();
}
