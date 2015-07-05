#pragma once
#include "fscene.h"
#include "FreeTypeCommandText.h"

class HighScoresScene :
	public FScene
{
public:
	enum COMMANDS{
		RESET = 100
	};
	HighScoresScene(FGameUI *ui);
	~HighScoresScene(void);
	void Command(int command, int extra);
protected:
	void Init();
	void MouseAction();
	void MouseLClick();
	void ResetScores();
};
