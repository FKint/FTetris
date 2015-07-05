#include "FTetrisPreField.h"

FTetrisPreField::FTetrisPreField(FTetrisBlockSet *blockset, int rows, int cols, FColor *color, FVertex *position, float width, float height, float scale, bool d3, float xrot, float yrot, float zrot):FTetrisField(rows, cols, color, position, width, height, scale, d3, xrot, yrot, zrot)
{
	SetBlockSet(blockset);
}

FTetrisPreField::~FTetrisPreField(void)
{
}
void FTetrisPreField::SetBlockSet(FTetrisBlockSet *blockset){
	this->blockset = blockset;
	if(blockset){
		blockset->SetXPos(1);
		blockset->SetYPos(1);
		blockset->SetDimensions(GetBoxWidth(), GetBoxHeight(), GetCubeWidth(), GetCubeHeight());
		blockset->Set3D(this->Get3D());
	}
}
void FTetrisPreField::DrawCubes(){
	if(blockset){
		for(int i = 0; i < 4; i++){
			blockset->cubes[i]->Draw();
		}
	}
}
void FTetrisPreField::Set3D(bool d3){
	this->d3 = d3;
	blockset->Set3D(d3);
}