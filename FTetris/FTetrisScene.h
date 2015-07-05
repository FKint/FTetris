#pragma once
class FTetrisScene;
#include "fscene.h"
#include "FTetrisBlockSet.h"
#include "FTetrisPreField.h"
#include "FTetrisGameController.h"
#include "FTetrisGameField.h"
#include "FreeTypeText.h"
#include "FreeTypeCommandText.h"

class FTetrisScene :
	public FScene
{
public:
	enum COMMANDS{
		START = 100, RESTART, NEW, PAUSE, RESETVIEW
	};
	FTetrisScene(FGameUI *ui, int rows, int cols);
	~FTetrisScene(void);
	void GamePointsChanged(int points);
	void GameStatusChanged();
	void Command(int command, int extra);
	void PreBlockSetChanged(FTetrisBlockSet *blockset);
	bool GetTexture(){return texture;}
	unsigned int GetTextureId(){return textureid;}
protected:
	void Init();
	void Update();
	int rows, cols;
	float scale;
	FTetrisGameController *gamecontroller;
	void KeyStatusChanged(int key);
	void MouseAction();
	FTetrisGameField *mainfield;
	FTetrisPreField *prefield;
	FreeTypeText *pointstext, *controltext;
	FreeTypeCommandText *newgametext, *startgametext, *restartgametext, *pausegametext, *menutext, *resetviewtext;
	void MouseLClick();
	bool texture;
	unsigned int textureid;
	bool autorot;
	bool autorotz, autorotx, autoroty;
};
