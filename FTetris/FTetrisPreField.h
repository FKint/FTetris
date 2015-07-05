#pragma once
class FTetrisPreField;
#include "ftetrisfield.h"
#include "FTetrisBlockSet.h"

class FTetrisPreField :
	public FTetrisField
{
public:
	FTetrisPreField(FTetrisBlockSet *blockset, int rows, int cols, FColor *color, FVertex *position, float width, float height, float scale, bool d3 = false, float xrot=0, float yrot=0, float zrot=0);
	~FTetrisPreField(void);
	void SetBlockSet(FTetrisBlockSet *blockset);
	void Set3D(bool d3);
protected:
	FTetrisBlockSet *blockset;
	void DrawCubes();
};
