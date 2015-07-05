#include "FGLLine.h"

FGLLine::FGLLine(FGLPoint *start, FGLPoint *end, FVertex *position, bool standalone, bool selectable):FGLDrawObject(0, position, xrot, yrot, zrot, standalone, selectable){
	Init(start, end);
}
FGLLine::FGLLine(float startx, float starty, float startz, float endx, float endy, float endz, float xpos, float ypos, float zpos, float xrot, float yrot, float zrot, FColor *color, bool standalone, bool selectable):FGLDrawObject(color, xpos, ypos, zpos, xrot, yrot, zrot, standalone, selectable)
{
	Init(new FGLPoint(startx, starty, startz, xpos, ypos, zpos, 1.0 ,color, false), new FGLPoint(endx, endy, endz, xpos, ypos, zpos, 1.0, color, false));
}

FGLLine::~FGLLine(void)
{
}
void FGLLine::Init(FGLPoint *start, FGLPoint *end){
	this->start = start;
	this->end = end;
}
void FGLLine::InternDraw(bool standalone){
	if(standalone){
		glBegin(GL_LINES);
	}
	start->Draw(false);
	end->Draw(false);
	
	if(standalone){
		glEnd();
	}
}
