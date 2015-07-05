#pragma once
#include "fgldrawobject.h"

class FGL2DDrawObject :
	public FGLDrawObject
{
public:
	enum HALIGNMENT{
		LEFT, HCENTER, RIGHT
	};
	enum VALIGNMENT{
		TOP, VCENTER, BOTTOM
	};
	FGL2DDrawObject(FColor *color, float x, float y, HALIGNMENT hAlign = LEFT, VALIGNMENT vAlign = TOP, float zrot = 0, bool standalone = true, bool selectable = false, FGLDrawObject ** subobjects = 0, unsigned int subobjectsamount = 0);
	FGL2DDrawObject(FColor *color, FVertex *position, HALIGNMENT hAlign, VALIGNMENT vAlign = TOP, float zrot = 0, bool standalone = true, bool selectable = false, FGLDrawObject ** subobjects = 0, unsigned int subobjectsamount = 0);
	void SetHAlignment(HALIGNMENT halign){this->hAlignment = halign;}
	void SetVAlignment(VALIGNMENT valign){this->vAlignment = valign;}
	virtual ~FGL2DDrawObject(void);
protected:
	virtual bool CheckPointInElement(int x, int y)=0;
	virtual void GetDimensions(int dimensions[4])=0;
	HALIGNMENT hAlignment;
	VALIGNMENT vAlignment;
};
