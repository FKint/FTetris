#pragma once
#include "fscene.h"
#include "FreeTypeCommandText.h"

class ControlsScene :
	public FScene
{
public:
	ControlsScene(FGameUI *ui);
	~ControlsScene(void);
protected:
	void Init();
	FreeTypeText *controlstext, *controlstext2;
	FreeTypeCommandText *menutext;
	void Command(int command, int extra);
	void MouseAction();
	void MouseLClick();
};
