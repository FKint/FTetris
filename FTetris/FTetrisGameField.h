#pragma once
class FTetrisGameField;
#include "ftetrisfield.h"
#include "FTetrisGameController.h"

class FTetrisGameField :
	public FTetrisField
{
public:
	FTetrisGameField(FTetrisGameController *controller, int rows, int cols, FColor *color, FVertex *position, float width, float height, float scale, bool d3 = true, float xrot = 0, float yrot = 0, float zrot = 0);
	~FTetrisGameField(void);
	void SetController(FTetrisGameController *controller){this->controller = controller;}
	void Set3D(bool d3);
protected:
	FTetrisGameController *controller;
	void DrawCubes();
};
