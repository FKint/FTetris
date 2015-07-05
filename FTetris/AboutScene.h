#pragma once
#include "fscene.h"
#include "FreeTypeCommandText.h"

class AboutScene :
	public FScene
{
public:
	AboutScene(FGameUI *ui);
	~AboutScene(void);
	void Command(int command, int extra);
protected:
	void Init();
	FreeTypeText *infotext;
	FreeTypeCommandText *menutext;
	void MouseAction();
	void MouseLClick();
};
