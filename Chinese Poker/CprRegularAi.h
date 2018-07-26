/****************************************************************************
FileName   [ CprRegularAi.h ]
Synopsis   [ define a regular AI strategy ]
****************************************************************************/

#pragma once
#include "CprAiPlayer.h"
class CprRegularAi :
	public CprAiPlayer
{
public:
	CprRegularAi(double pow = 2.0, double multi1st = 5.0);
	~CprRegularAi();
private:
	virtual void playerStrategy();
	static const int RepeatTime = 20;
	double calculateScore();
	double ST(const CprHand&);
	double ST(HandType);
	double _pow;
	double _mult1st;
	static int RegularCount;
};

