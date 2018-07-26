/****************************************************************************
FileName   [ CprAiPlayer.h ]
Synopsis   [ define abstract AI interface ]
****************************************************************************/

#pragma once
#include "CprPlayer.h"
class CprAiPlayer :
	public CprPlayer
{
public:
	CprAiPlayer();
	~CprAiPlayer();
private:
	virtual void playerStrategy();
};

