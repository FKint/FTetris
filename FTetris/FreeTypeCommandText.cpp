#include "FreeTypeCommandText.h"

FreeTypeCommandText::FreeTypeCommandText(FCommandListener *listener, int command, int extra, const char* text, const char* fontfilename, int size, FColor *color, FVertex *position, HALIGNMENT hAlign, VALIGNMENT vAlign, float zrot):FreeTypeText(text, fontfilename, size, color, position, hAlign, vAlign, zrot, true)
{
	executable = true;
	this->listener = listener;
	this->command = command;
	this->extra = extra;
}

FreeTypeCommandText::~FreeTypeCommandText(void)
{
}
void FreeTypeCommandText::Command(int command, int extra){
	FreeTypeText::Command(command, extra);
	switch(command){
		case EXECUTE:
			if(listener != 0){
				listener->Command(this->command, this->extra);
			}
			break;
		default:
			break;
	}
}
