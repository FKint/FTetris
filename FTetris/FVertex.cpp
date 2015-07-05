#include "FVertex.h"

FVertex::FVertex(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
FVertex::FVertex(FVertex *vertex){
	this->SetX(vertex->GetX());
	this->SetY(vertex->GetY());
	this->SetZ(vertex->GetZ());
}


FVertex::~FVertex(void)
{
}
