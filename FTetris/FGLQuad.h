#pragma once
#include "fgldrawobject.h"
#include "FGLPoint.h"

class FGLQuad :
	public FGLDrawObject
{
public:
	FGLQuad(FColor *color, FVertex *position, FGLPoint *point1, FGLPoint *point2, FGLPoint *point3, FGLPoint *point4, float xrot, float yrot, float zrot, bool selectable);
	~FGLQuad(void);
protected:
	FGLPoint *points [4];
	void InternDraw(bool standalone);
};

