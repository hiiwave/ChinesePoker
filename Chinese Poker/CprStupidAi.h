#pragma once
#include "CprAiPlayer.h"
class CprStupidAi :
	public CprAiPlayer 
{
public:
	CprStupidAi();
	~CprStupidAi();
private:
	virtual void playerStrategy();
};

