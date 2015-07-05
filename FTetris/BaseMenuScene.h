#pragma once
#include "fscene.h"
#include "FGLQuad.h"
#include "FreeTypeCommandText.h"

class BaseMenuScene :
	public FScene
{
public:
	BaseMenuScene(FGameUI *ui);
	~BaseMenuScene(void);
protected:
	void Update();
	void Init();
	void MouseAction();
	void MouseLClick();
	char* menufontname;
	FColor *menucolor;
	short menuitemsize;
	FColor *actioncolor;
	FColor *focuscolor;
	FGLQuad *rotatequad;
	FreeTypeCommandText *newgameitem, *controlsitem, *aboutitem, *quititem, *highscoresitem;
};
