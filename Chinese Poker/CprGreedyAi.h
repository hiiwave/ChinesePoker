/****************************************************************************
FileName   [ CprGreedyAi.h ]
Synopsis   [ define a greedy AI strategy ]
****************************************************************************/

#pragma once
#include "CprAiPlayer.h"
class CprGreedyAi :
	public CprAiPlayer
{
public:
	CprGreedyAi();
	~CprGreedyAi();
private:
	virtual void playerStrategy();
};

