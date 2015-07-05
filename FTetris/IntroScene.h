#pragma once
#include "fscene.h"

class IntroScene :
	public FScene
{
public:
	IntroScene(FGameUI *ui);
	~IntroScene(void);
protected:
	void Update();
	void Init();
	void KeyboardAction();
};
