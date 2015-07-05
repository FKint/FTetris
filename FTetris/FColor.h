#pragma once

class FColor
{
public:
	FColor(float r, float g, float b, float a = 1.0);
	FColor(FColor *color);
	~FColor(void);
	float GetR(){return r;}
	float GetG(){return g;}
	float GetB(){return b;}
	float GetA(){return a;}
	void SetR(float r){this->r = r;}
	void SetG(float g){this->g = g;}
	void SetB(float b){this->b = b;}
	void SetA(float a){this->a = a;}
protected:
	float r, g, b, a;

};
