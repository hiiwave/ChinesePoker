/****************************************************************************
FileName   [ CprCard.h ]
Synopsis   [ define a single card ]
****************************************************************************/

#pragma once
#include "CprDef.h"

class CprCard
{
	friend ostream& operator << (ostream&, const CprCard&);
	friend istream& operator >> (istream&, CprCard&);
public:
	CprCard();
	CprCard(int id);
	~CprCard();
	int suit() const;
	int rank() const;
	int rankA() const;
	int getCardId() const;
	bool operator <= (const CprCard&) const;
	bool operator <  (const CprCard&) const;
	bool operator == (const CprCard&) const;
	bool operator != (const CprCard&) const;
private:
	static int SuitFromChar(const char c);
	static int RankFromChar(const char c);
	void setting(int suit, int rank);
	int _cardId;	// 1 - 52
};

// in CprCard.h
// global function prototypes
bool c_less(const CprCard&, const CprCard&);
bool c_greater(const CprCard&, const CprCard&);
bool c_ordinal(const CprCard&, const CprCard&);


