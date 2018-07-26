/****************************************************************************
FileName   [ CprPlayer.h ]
Synopsis   [ define CprPlayer class ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprCollection.h"

class CprPlayer
{
	friend CprDealer;
	friend ostream &operator<<(ostream &os, const CprPlayer& player);
public:
	CprPlayer();
	CprPlayer(string id);
	~CprPlayer();
	void strategy();
	const CprHand& getHand(int idx) const;
	CprHand& hand(int idx);
	void winOneTrick(CprPlayer* player);
	void gunShooting(CprPlayer* player);
	void setId(string);
	string getId() const;
	void printId(int pType = 0) const;
	int getScore() const;
	void printScore() const;
	void reset();

protected:
	CprCollection _collection;
	CprCollection& collection();
	const CprCollection& collection() const;
	
private:
	string _id;
	CardList _myCards;
	virtual void playerStrategy() = 0;
	void assertValidStrategy() const;
	int _score = 0;
};

