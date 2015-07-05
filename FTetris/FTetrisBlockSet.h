#pragma once
class FTetrisBlockSet;
#include "FTetrisCube.h"

class FTetrisBlockSet
{
#pragma message("ftetrisblockset")
public:
	enum BLOCKOPTIONS{
		I, J, L, O, T, S, Z
	};
	FTetrisBlockSet(short xpos, short ypos, BLOCKOPTIONS option, float boxwidth, float boxheight, float cubewidth, float cubeheight, FColor *color, bool d3 = true, bool texture = false, unsigned int textureid = 0, bool selectable = false);
	~FTetrisBlockSet(void);
	short x[4];
	short y[4];
	FTetrisCube **cubes;
	short GetXPos(){return xpos;}
	short GetYPos(){return ypos;}
	void SetXPos(short xpos);
	void SetYPos(short ypos);

	short GetRef(){return ref;}
	BLOCKOPTIONS GetType(){return type;}
	void Rotate(short *xbuffer, short *ybuffer);
	void SetBoxHeight(float boxheight){this->boxheight = boxheight; Resized();}
	void SetBoxWidth(float boxwidth){this->boxwidth = boxwidth; Resized();}
	void SetCubeHeight(float cubeheight){this->cubeheight = cubeheight; Resized();}
	void SetCubeWidth(float cubewidth){this->cubewidth = cubewidth; Resized();}
	void SetDimensions(float boxwidth, float boxheight, float cubewidth, float cubeheight){this->cubeheight = cubeheight; this->cubewidth = cubewidth; this->boxheight = boxheight; this->boxwidth = boxwidth; Resized();}
	void Resized();
	void Set3D(bool d3){this->d3 = d3; for(int i = 0; i < 4; i++){cubes[i]->Set3D(d3);}}
protected:
	short xpos;
	short ypos;
	short ref;
	float boxwidth, boxheight, cubewidth, cubeheight;
	BLOCKOPTIONS type;
	bool d3;
};
