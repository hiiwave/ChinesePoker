#pragma once
#include "CprAiPlayer.h"
class CprBruteAi :
	public CprAiPlayer {
public:
	CprBruteAi(double pow, double multi1st);
	~CprBruteAi();
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

