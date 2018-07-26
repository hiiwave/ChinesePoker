/****************************************************************************
FileName   [ CprGame.h ]
Synopsis   [ define the start of Chinese Poker Game ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprPlayer.h"

class CprGame
{
public:
	CprGame();
	~CprGame();
	void setting();
	void start();
	void end();
private:
	PlayerList _players;
};

