/****************************************************************************
FileName   [ CprHandMaster.h ]
Synopsis   [ define a master familiar to any card operation ]
****************************************************************************/

#pragma once
#include "CprHandType.h"
#include "CprDef.h"
class CprHandMaster
{
public:
	static CprHandMaster* CreateMaster(HandType);
	CprHandMaster();
	~CprHandMaster();
	static bool Compare(const CprHand&, const CprHand&);
	static void DetermineType(CprHand&);
	// static void PrintHand(const CprHand&, int pType);
	static bool CheckCollectionCards(const CprCollection&, const CardList&);
	static string traslateType(HandType);

	static CprHand* ContainType(const CprCollection&, HandType);
	static CprHand GetBestHand(const CprCollection&);
	static CprHand GetBestHandUnder(const CprCollection&, const CprHand&);
	static void CalculateSubScore(CprHand&);

protected:
	void recompCardsOfHand(CprHand&, const CardList&);

private:
	virtual bool compareDeeply(const CprHand&, const CprHand&) { return false; }
	virtual bool determineMe(CprHand&) { return false; }
	virtual bool containsMe(const CprCollection&, CprHand&) { return false; }
	virtual bool containsMeUnder(const CprCollection&, const CprHand&, CprHand&, bool = false) { return false; }
	virtual void calcSubScore(CprHand&) {  }
};

