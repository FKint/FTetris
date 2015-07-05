#pragma once
#include "fgame.h"

class FTetris :
	public FGame
{
public:
	FTetris(void);
	~FTetris(void);
protected:
	FScene *GoTo(int stat);
	bool MyCommand(int command, int extra);
};
