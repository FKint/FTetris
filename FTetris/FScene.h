#pragma once
class FScene;
#include "includes.h"
#include "FCommandListener.h"
#include "FUserInputListener.h"
class FGameUI;

#include "FGLDrawObject.h"



class FScene : public FCommandListener, public FUserInputListener
{
public:
#pragma message("in fscene.h")
	FScene(FGameUI *ui, const unsigned int objectsamount, int updateinterval = 0, bool handleevents = true);
	~FScene(void);
	void Draw(int mode = GL_RENDER);
	void SetUI(FGameUI *ui){this->ui = ui;}
	void Action();
	void Start();
	void Interrupt(){active = false;}
	void SetActive(bool activeflag){
		if(activeflag && !active){
			Start();
		}
		if(active && !activeflag){
			Interrupt();
		}
	}
	void Command(int command, int extra);
protected:
	FGLDrawObject **objects;
	unsigned int objectsamount;
	void SceneDraw(){};
	unsigned int* GetPickedObjects(float x, float y, float width, float height, FGLDrawObject **objects, unsigned int amount, int *pickedamount, unsigned int* closestelement, unsigned int* deepestelement);
	bool* GetObjectsPicked(float x, float y, float width, float height, FGLDrawObject **objects, unsigned int amount, unsigned int* closestelement, unsigned int* deepestelement);
	FGameUI *ui;
	bool active;

	virtual void Update(){};
	virtual void Init(){};
	void ProcessSelectedObjects(short int x, short int y, short int pickwidth, short int pickheight, bool execute);

	unsigned int lasttick;
	unsigned int updateinterval;
	bool initialized;
	unsigned int updates;
	float xtrans, ytrans, ztrans;
};
#include "FGameUI.h"
