#pragma once
#include "fgl2ddrawobject.h"
#include "freetype.h"
#define FREETYPEFONTMAXSTRLEN 1024
class FreeTypeText :
	public FGL2DDrawObject
{
public:
	FreeTypeText(const char* text, const char* fontfilename, int size, FColor *color, FVertex *position, HALIGNMENT hAlign = LEFT, VALIGNMENT vAlign = TOP, float zrot = 0, bool selectable = false);
	FreeTypeText(const char* text, const char* fontfilename, int size, FColor *color, float x, float y, HALIGNMENT hAlign = LEFT, VALIGNMENT vAlign = TOP, float zrot = 0, bool selectable = false);
	~FreeTypeText(void);
	void SetText(const char* input, ...);
	void SelectionDraw();
	bool CheckPointInElement(int x, int y);
	void GetDimensions(int dimensions[4]);
protected:
	char *text;
	freetype::font_data font;
	void InternDraw(bool standalone);
	float textdata[3];
};
