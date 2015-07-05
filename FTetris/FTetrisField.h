#pragma once
class FTetrisField;
#include "fgldrawobject.h"

class FTetrisField :
	public FGLDrawObject
{
public:
	FTetrisField(int rows, int cols, FColor *color, FVertex *position, float width, float height, float scale, bool d3 = false, float xrot=0, float yrot=0, float zrot=0);
	~FTetrisField(void);
	void SetCols(int cols);
	void SetRows(int rows);
	int GetCols(){return cols;}
	int GetRows(){return rows;}
	float GetBorder(){return border;}
	float GetTotalWidth(){return width * scale;}
	float GetTotalHeight(){return height * scale;}
	float GetScale(){return scale;}
	float GetBoxWidth(){return GetTotalWidth() / (float)cols;}
	float GetBoxHeight(){return GetTotalHeight() / (float)rows;}
	float GetCubeWidth(){return GetTotalWidth() / (float)cols - border;}
	float GetCubeHeight(){return GetTotalHeight() /(float) rows - border;}
	bool Get3D(){return d3;}
	virtual void Set3D(bool d3)=0;
protected:
	int rows;
	int cols;
	float scale;
	float height, width;
	void InternDraw(bool standalone);
	float border;
	float startx;
	float starty;
	virtual void DrawCubes()=0;
	bool d3;
};
