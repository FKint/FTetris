#pragma once
#include "includes.h"
//#include <gl/glut.h>
#include "FGLDrawObject.h"
#include "FVertex.h"

class FGLPoint : public FGLDrawObject, public FVertex
{
public:
	FGLPoint(float x, float y, float z, float xpos, float ypos, float zpos, float w = 1.0, FColor *color = 0, bool standalone = false, bool selectable = false);
	FGLPoint(FVertex *point, FVertex *position, float w, FColor *color = 0, bool standalone = false, bool selectable = false);
	~FGLPoint(void);
	float GetW(){return w;}
	void SetW(float w){this->w = w;}
protected:
	float w;
	void InternDraw(bool standalone);
};
