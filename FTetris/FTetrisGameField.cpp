#include "FTetrisGameField.h"

FTetrisGameField::FTetrisGameField(FTetrisGameController *controller, int rows, int cols, FColor *color, FVertex *position, float width, float height, float scale, bool d3, float xrot, float yrot, float zrot):FTetrisField(rows, cols, color, position, width, height, scale, d3, xrot, yrot, zrot)
{
	this->controller = controller;
}

FTetrisGameField::~FTetrisGameField(void)
{
}

void FTetrisGameField::DrawCubes(){
	if(controller){
		controller->DrawCubes();
	}
}
void FTetrisGameField::Set3D(bool d3){
	this->d3 = d3;
	/*if(controller){
		for(int i = 0; i < controller->GetRows() * controller->GetCols()){
			if(controller->box[i])
				controller->box[i]->Set3D(d3);
		}
	}*/
	controller->Set3D(d3);
}