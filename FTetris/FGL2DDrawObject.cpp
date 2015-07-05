#include "FGL2DDrawObject.h"

FGL2DDrawObject::FGL2DDrawObject(FColor *color, float x, float y, HALIGNMENT hAlign, VALIGNMENT vAlign, float zrot, bool standalone, bool selectable, FGLDrawObject ** subobjects, unsigned int subobjectsamount):FGLDrawObject(color, x, y, 0, 0, 0, zrot, standalone, selectable, subobjects, subobjectsamount, 0)
{
	renderselect = false;
	multipleselectalowed = true;
	this->hAlignment = hAlign;
	this->vAlignment = vAlign;
}
FGL2DDrawObject::FGL2DDrawObject(FColor *color, FVertex *position, HALIGNMENT hAlign, VALIGNMENT vAlign, float zrot, bool standalone, bool selectable, FGLDrawObject ** subobjects, unsigned int subobjectsamount):FGLDrawObject(color, position, 0, 0, zrot, standalone, selectable, subobjects, subobjectsamount, 0){
	renderselect = false;
	multipleselectalowed = true;
	this->hAlignment = hAlign;
	this->vAlignment = vAlign;
}

FGL2DDrawObject::~FGL2DDrawObject(void)
{
}
