/****************************************************************************
FileName   [ CprStage.h ]
Synopsis   [ define each phase in a single stage ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprCollection.h"

class CprStage
{
public:
	CprStage(PlayerList& players, int id);
	~CprStage();
	void start();

private:
	void dealingPhase();
	void strategyPhase();
	void checkXianggongPhase();
	void comparisonPhase();
	void shootingPhase();
	void printScores() const;

	PlayerList& _players;
	int _TrickCount[4][4];
	int _stageId;
};

