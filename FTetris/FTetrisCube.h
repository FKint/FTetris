#pragma once
#include "fgldrawobject.h"

class FTetrisCube :
	public FGLDrawObject
{
public:
	FTetrisCube(FColor *color, FVertex *position, float width, float height, float xrot, float yrot, float zrot, bool d3, bool texture = false,unsigned int textureid = 0, bool selectable = true);
	virtual ~FTetrisCube(void);
	void SetWidth(float width){this->width = width;}
	void SetHeight(float height){this->height = height;}
	void Set3D(bool d3){this->d3 = d3;}
protected:
	bool texture;
	unsigned int textureid;
	float width, height;
	void InternDraw(bool standalone);
	bool d3;
};
