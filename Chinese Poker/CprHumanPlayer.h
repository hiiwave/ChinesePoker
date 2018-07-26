/****************************************************************************
FileName   [ CprHumanPlayer.h ]
Synopsis   [ define user interface for human players ]
****************************************************************************/

#pragma once
#include "CprPlayer.h"
class CprHumanPlayer :
	public CprPlayer
{
public:
	CprHumanPlayer();
	~CprHumanPlayer();
private:
	virtual void playerStrategy();
	void showHelps();
	void readCommands();
	bool parseOneCmd();
	void parseHandCmd();
	bool checkValidStrategy();
	string _command;
};

