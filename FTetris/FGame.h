#pragma once
#include "includes.h"
class FGame;
#include "FCommandListener.h"
#include "FGameUI.h"
#include "IntroScene.h"
#include "FScene.h"

class FGame : public FCommandListener
{
public:
#pragma message("in fgame")
	enum FGameCommand{
		GOTO, NEWGAME, QUIT, ABOUT
	};
	enum FGameGotoCommand{
		NONE, INTRO, BASEMENU, GAME, EXITSCREEN, ABOUTSCREEN, HELP, HIGHSCORES
	};
	FGame(void);
	virtual ~FGame(void);
	void SetBlock(bool blockflag){this->block = blockflag;}
	bool Start(char *title);
	void SetActive(bool activeflag){this->active = activeflag;}
	void Action();
	void Exit();
	FGameUI* GetUI(){return ui;}
	void Command(int command, int extra);
protected:
	bool block;
	bool stopped;
	bool active;
	FGameUI *ui;
	virtual FScene* GoTo(int stat);
	virtual bool MyCommand(int command, int extra) = 0;
	bool changescene;
	int scenetogoto;
};
