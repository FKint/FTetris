#include "FTetris.h"
#include "IntroScene.h"
#include "BaseMenuScene.h"
#include "FTetrisScene.h"
#include "AboutScene.h"
#include "ControlsScene.h"
#include "HighScoresScene.h"

FTetris::FTetris(void)
{
}

FTetris::~FTetris(void)
{
}
FScene* FTetris::GoTo(int stat){
	FScene* scene = 0;
	//specify your scenes
	switch(stat){
		case INTRO:
			scene = new IntroScene(this->ui);
			break;
		case BASEMENU:
			scene = new BaseMenuScene(this->ui);
			//scene = new IntroScene(this->ui);
			break;
		case GAME:
			scene = new FTetrisScene(this->ui, 15, 10);
			break;
		case ABOUTSCREEN:
			scene = new AboutScene(this->ui);
			break;
		case HELP:
			scene = new ControlsScene(this->ui);
			break;
		case HIGHSCORES:
			scene = new HighScoresScene(this->ui);
			break;
	}
	//end of specifying
	if(scene == 0){
		//if you haven't specified a scene, go to the standard scene
		scene = FGame::GoTo(stat);
	}
	return scene;
}
bool FTetris::MyCommand(int command, int extra){
	bool commandfullyhandled = false;
	//insert your commands and give tasks, if there's no other task that must be done, set commandfullyhandled to true
	switch(command){
		case NEWGAME:
			this->Command(GOTO, GAME);
			commandfullyhandled = true;
			break;
		case ABOUT:
			MessageBox(this->ui->GetHWND(), "3D Tetris has been made by Floris Kint.\nFor more information, go to the about page.", "About", 0);
			break;
	}
	return commandfullyhandled;
}