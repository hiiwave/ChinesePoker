/****************************************************************************
FileName   [ CprEachMaster.h ]
Synopsis   [ define masters on each card type ]
****************************************************************************/

#pragma once
#include "CprHandMaster.h"

#define CprEachMasterClass(T)												\
class T : public CprHandMaster											\
{																					\
	template <class S> friend class CprEachMasterTest;				\
private:																			\
	bool compareDeeply(const CprHand&, const CprHand&);			\
	bool determineMe(CprHand&);											\
	bool containsMe(const CprCollection&, CprHand&);				\
	bool containsMeUnder(const CprCollection&, const CprHand&, CprHand&, bool = false); \
	void calcSubScore(CprHand&);												\
}																					\

CprEachMasterClass(CprStraightFlushMaster);
CprEachMasterClass(CprFourOfAKindMaster);
CprEachMasterClass(CprFullHouseMaster);
CprEachMasterClass(CprFlushMaster);
CprEachMasterClass(CprStraightMaster);
CprEachMasterClass(CprThreeOfAKindMaster);
CprEachMasterClass(CprTwoPairMaster);
CprEachMasterClass(CprOnePairMaster);
CprEachMasterClass(CprHighCardMaster);

