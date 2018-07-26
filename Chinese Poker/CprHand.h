/****************************************************************************
FileName   [ CprHand.h ]
Synopsis   [ define a 3-card or 5-card Hand ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprCard.h"
#include "CprHandType.h"
#include "CprHandMaster.h"
class CprHand
{
	FRIEND_ALL_MASTER;
	friend class CprCollection;
public:
	CprHand();
	CprHand(const CardList&);
	CprHand(const CardList&, HandType);
	~CprHand();
	bool operator <= (const CprHand& hand) const;
	bool operator >= (const CprHand& hand) const;
	
	const CardList& getCards() const;
	void setXianggong();
	void print(int pType = 0) const;
	HandType getType() const;

	/* convenient methods */
	int size() const;
	bool empty() const;
	CprCard& at(int idx);
	CprCard getCard(int idx) const;
	CardList* getACR() const;
	double getSubScore() const;	// 0 ~ 1

	/*other method */
	bool sameWith(const CprHand&);
	void push_Card(const CprCard& c);
	void pop_Card();

	static CprHand GetUltimateHand();
	static CprHand GetUltraPseudoHand();
		// a pseudo hand stronger than ultimate
private:
	CardList _cards;
	HandType _type;
	int _subScoreI = 0;	// ~= 1 ~ 256
};

HandType advanceType(HandType type);