#pragma once

class FVertex
{
public:
	FVertex(float x, float y, float z);
	FVertex(FVertex* vertex);
	~FVertex(void);
	void SetX(float x){this->x = x;}
	void SetY(float y){this->y = y;}
	void SetZ(float z){this->z = z;}
	float GetX(){return x;}
	float GetY(){return y;}
	float GetZ(){return z;}
protected:
	float x, y, z;
};
