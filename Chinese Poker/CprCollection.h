/****************************************************************************
FileName   [ CprCollection.h ]
Synopsis   [ define cards held by players ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprHand.h"
class CprCollection
{
	FRIEND_ALL_MASTER;
	friend class CprTest;
	friend class CprDealer;
public:
	CprCollection();
	~CprCollection();
	/* setting methods */
	bool settingHand(int, const CprHand &);
	bool settingHand(int, const CardList&);
	bool settingFinalHand();
	void finishSetting();
	void resetHand(int hidx);
	void resetAllHands();
	/* access methods */
	CprHand& hand(int);
	const CprHand& getHand(int) const;
	const CardList& getAvailableCards() const;
	void computeACR();
	const CardList* getACR() const;
	int size() const { return (int)_availCards.size(); }
	/* other methods */
	void printByRank() const;
	void printBySuit() const;
	void showCollection(int pType = 0) const;
	bool isValidSet() const;
	bool isFinalHandLeftOnly() const;
	bool sameWith(const CprCollection& col);


private:
	CardList _cards;
	CardList _availCards;
	HandList _hands;
	CardList _ACR[15];	// availableCardsWithRank

	/* helper */
	bool isCardAvailable(const CprCard&) const;
};

