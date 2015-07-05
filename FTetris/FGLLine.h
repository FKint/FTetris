#pragma once
#include "FGLDrawObject.h"
#include "FGLPoint.h"
#include "FVertex.h"

class FGLLine : public FGLDrawObject
{
public:
	FGLLine(FGLPoint *start, FGLPoint *end, FVertex *position, bool standalone = false, bool selectable = false);
	FGLLine(float startx, float starty, float startz, float endx, float endy, float endz, float xpos, float ypos, float zpos, float xrot, float yrot, float zrot, FColor *color = 0, bool standalone = false, bool selectable = false);
	~FGLLine(void);
	FGLPoint *GetStart(){return start;}
	FGLPoint *GetEnd(){return end;}
	void SetColor(FColor *color){start->SetColor(color); end->SetColor(color);}
protected:
	FGLPoint *start;
	FGLPoint *end;
	void InternDraw(bool standalone);
private:
	void Init(FGLPoint *start, FGLPoint *end);
};
