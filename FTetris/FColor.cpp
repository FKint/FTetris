#include "FColor.h"

FColor::FColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
FColor::FColor(FColor *color){
	this->r = color->GetR();
	this->g = color->GetG();
	this->b = color->GetB();
	this->a = color->GetA();
}

FColor::~FColor(void)
{
}
