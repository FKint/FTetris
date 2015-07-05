#include "FGLPoint.h"

FGLPoint::FGLPoint(float x, float y, float z, float xpos, float ypos, float zpos, float w, FColor *color, bool standalone, bool selectable):FGLDrawObject(color, xpos, ypos, zpos, xrot, yrot, zrot, standalone, selectable), FVertex(x, y, z)
{
	this->w = w;
}
FGLPoint::FGLPoint(FVertex *point, FVertex *position, float w, FColor *color, bool standalone, bool selectable):FVertex(point), FGLDrawObject(color, position, 0, 0, 0, standalone, selectable){
	this->w = w;
}

FGLPoint::~FGLPoint(void)
{
}
void FGLPoint::InternDraw(bool standalone){
	if(standalone){
		glBegin(GL_POINTS);
	}

	glVertex4f(this->GetX(), this->GetY(), this->GetZ(), this->GetW());
	if(standalone){
		glEnd();
	}
}