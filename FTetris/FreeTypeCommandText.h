#pragma once
#include "freetypetext.h"
#include "FCommandListener.h"

class FreeTypeCommandText :
	public FreeTypeText
{
public:
	FreeTypeCommandText(FCommandListener *listener, int command, int extra, const char* text, const char* fontfilename, int size, FColor *color, FVertex *position, HALIGNMENT hAlign = LEFT, VALIGNMENT vAlign = TOP, float zrot = 0);
	~FreeTypeCommandText(void);
	void Command(int command, int extra);
protected:
	int command;
	int extra;
	FCommandListener *listener;
};
