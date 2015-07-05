#include "FGLQuad.h"

FGLQuad::FGLQuad(FColor *color, FVertex *position, FGLPoint *point1, FGLPoint *point2, FGLPoint *point3, FGLPoint *point4, float xrot, float yrot, float zrot, bool selectable):FGLDrawObject(color, position, xrot, yrot, zrot, true, selectable)
{
	this->points[0] = point1;
	this->points[1] = point2;
	this->points[2] = point3;
	this->points[3] = point4;
}

FGLQuad::~FGLQuad(void)
{
}
void FGLQuad::InternDraw(bool standalone){
	if(standalone){
		glBegin(GL_QUADS);
	}

	for(int i = 0; i < 4; i ++){
		points[i]->Draw(false);
	}
	if(standalone){
		glEnd();
	}
}