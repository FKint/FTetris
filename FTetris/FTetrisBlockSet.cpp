#include "FTetrisBlockSet.h"

FTetrisBlockSet::FTetrisBlockSet(short xpos, short ypos, FTetrisBlockSet::BLOCKOPTIONS option, float boxwidth, float boxheight, float cubewidth, float cubeheight, FColor *color, bool d3, bool texture, unsigned int textureid, bool selectable){
	this->d3 = d3;
	this->type = option;
	this->cubes = 0;
	this->boxwidth = boxwidth;
	this->boxheight = boxheight;
	this->cubewidth = cubewidth;
	this->cubeheight = cubeheight;
	switch (option){
		case FTetrisBlockSet::I:
			x[0] = -1;
			x[1] = 0;
			x[2] = 1;
			x[3] = 2;
			y[0] = 0;
			y[1] = 0;
			y[2] = 0;
			y[3] = 0;
			ref = 1;
			break;
		case FTetrisBlockSet::J:
			x[0] = -1;
			x[1] = 0;
			x[2] = 1;
			x[3] = 1;
			y[0] = 0;
			y[1] = 0;
			y[2] = 0;
			y[3] = 1;
			ref = 1;
			break;
		case FTetrisBlockSet::L:
			x[0] = -1;
			x[1] = -1;
			x[2] = 0;
			x[3] = 1;
			y[0] = 1;
			y[1] = 0;
			y[2] = 0;
			y[3] = 0;
			ref = 2;
			break;
		case FTetrisBlockSet::O:
			x[0] = 0;
			x[1] = 1;
			x[2] = 0;
			x[3] = 1;
			y[0] = 0;
			y[1] = 0;
			y[2] = 1;
			y[3] = 1;
			ref = 0;
			break;
		case FTetrisBlockSet::S:
			x[0] = -1;
			x[1] = 0;
			x[2] = 0;
			x[3] = 1;
			y[0] = 1;
			y[1] = 1;
			y[2] = 0;
			y[3] = 0;
			ref = 2;
			break;
		case FTetrisBlockSet::Z:
			x[0] = -1;
			x[1] = 0;
			x[2] = 0;
			x[3] = 1;
			y[0] = 0;
			y[1] = 0;
			y[2] = 1;
			y[3] = 1;
			ref = 1;
			break;
		case FTetrisBlockSet::T:
			x[0] = -1;
			x[1] = 0;
			x[2] = 0;
			x[3] = 1;
			y[0] = 0;
			y[1] = 0;
			y[2] = 1;
			y[3] = 0;
			ref = 1;
			break;
		default:
			x[0] = 0;
			x[1] = 0;
			x[2] = 0;
			x[3] = 0;
			y[0] = 0;
			y[1] = 0;
			y[2] = 0;
			y[3] = 0;
			ref = -1;
	}
	this->xpos = xpos;
	this->ypos = ypos;
	cubes = (FTetrisCube**)malloc(sizeof(FTetrisCube*) * 4);
	for(int i = 0; i < 4; i++){
		cubes[i] = new FTetrisCube(new FColor(color), new FVertex((x[i] + xpos) * boxwidth + boxwidth - cubewidth, -(y[i] + ypos) * boxheight + boxheight - cubeheight, 0), cubewidth, cubeheight, 0, 0, 0, d3, texture, textureid, selectable);
	}
	delete color;
}

FTetrisBlockSet::~FTetrisBlockSet(void)
{
}


void FTetrisBlockSet::SetXPos(short xpos){
	/*for(int i = 0; i < 4; i ++){
		cubes[i]->SetPosition(new FVertex((x[i] + xpos) * boxwidth, -(y[i] + ypos) * boxheight, 0));
	}*/
	this->xpos = xpos;
	Resized();
}
void FTetrisBlockSet::SetYPos(short ypos){
	/*for(int i = 0; i < 4; i++){
		cubes[i]->SetPosition(new FVertex((x[i] + xpos) * boxwidth, -(y[i] + ypos) * boxheight, 0));
	}*/
	this->ypos = ypos;
	Resized();
}
void FTetrisBlockSet::Rotate(short *xbuffer, short *ybuffer){
	bool counter = false;
	switch(this->type){
		case FTetrisBlockSet::O:
			for(int i = 0; i < 4; i ++){
				xbuffer[i] = x[i];
				ybuffer[i] = y[i];
			}
			return;
		case FTetrisBlockSet::I:
			if(y[0] - y[3] != 0)
				counter = true;
			break;
		case FTetrisBlockSet::S:
		case FTetrisBlockSet::Z:
			if((x[0] - x[3] > 1) || (x[0] - x[3] < -1)){
				counter = true;
			}
			break;
		case FTetrisBlockSet::T:
		case FTetrisBlockSet::J:
		case FTetrisBlockSet::L:
			break;
		default:
			break;
	}
	for(int i = 0; i < 4; i ++){
		if(counter){
			xbuffer[i] = y[i] - y[GetRef()] + x[GetRef()];
			ybuffer[i] = x[GetRef()] - x[i] + y[GetRef()];
		}else{
			xbuffer[i] = x[GetRef()] + y[GetRef()] - y[i];
			ybuffer[i] = y[GetRef()] - x[GetRef()] + x[i];
		}				
	}
}
void FTetrisBlockSet::Resized(){
	for(int i = 0; i < 4; i ++){
		if(cubes[i] != 0){
			cubes[i]->SetWidth(cubewidth);
			cubes[i]->SetHeight(cubeheight);
			cubes[i]->SetPosition(new FVertex((x[i] + GetXPos()) * boxwidth + (boxwidth - cubewidth) / 2, -(y[i] + GetYPos()) * boxheight - (boxheight - cubeheight) / 2, 0));
		}
	}
}