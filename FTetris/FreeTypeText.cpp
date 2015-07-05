#include "FreeTypeText.h"
#include <math.h>

FreeTypeText::FreeTypeText(const char* text, const char* fontfilename, int size, FColor *color, FVertex *position, HALIGNMENT hAlign, VALIGNMENT vAlign, float zrot, bool selectable):FGL2DDrawObject(color, position, hAlign, vAlign, zrot, true, selectable, 0, 0)
{
	textdata[0] = 0;//width
	textdata[1] = 0;//linesamount
	textdata[2] = 0;//height per line
	font.init(fontfilename, size);
	this->text = 0;
	SetText(text);
}

FreeTypeText::FreeTypeText(const char* text, const char* fontfilename, int size, FColor *color, float x, float y, HALIGNMENT hAlign, VALIGNMENT vAlign, float zrot, bool selectable):FGL2DDrawObject(color, x, y, hAlign, vAlign, zrot, true, selectable, 0, 0)
{
	renderselect = false;
	multipleselectalowed = true;
	textdata[0] = 0;
	textdata[1] = 0;
	textdata[2] = 0;
	font.init(fontfilename, size);
	this->text = 0;
	SetText(text);
}
FreeTypeText::~FreeTypeText(){
	if(text != 0)
		delete [] text;
	font.clean();
}
void FreeTypeText::InternDraw(bool standalone){
	glPushMatrix();
	glLoadIdentity();
	float xpos, ypos;
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	xpos = position->GetX();
	ypos = position->GetY();
	if(viewport[2] < viewport[3]){
		xpos += 1;
		xpos = xpos / 2 * (float)viewport[2];
		ypos += (float)viewport[3] / (float)viewport[2];
		ypos = ypos / ((float)viewport[3] / (float)viewport[2]) * viewport[3];
	}else{
		ypos += 1;
		ypos = ypos / 2 * (float)viewport[3];
		xpos += (float)viewport[2] / (float)viewport[3];
		xpos = xpos / ((float)viewport[2] / (float)viewport[3]) / 2 * (float)viewport[2];
	}
	if(this->hAlignment == FGL2DDrawObject::RIGHT){
		xpos -= textdata[0];
	}else if(this->hAlignment == FGL2DDrawObject::HCENTER){
		xpos -= textdata[0] / 2;
	}
	ypos -= font.h;
	if(this->vAlignment == FGL2DDrawObject::VCENTER){
		ypos +=  textdata[1] * textdata[2] / 2;
	}else if(this->vAlignment == FGL2DDrawObject::BOTTOM){
		ypos += textdata[1] * textdata[2];
	}
	//glTranslatef(this->GetPosition()->GetX(), this->GetPosition()->GetY(), 0);
	glRotatef(zrot, 0, 0, 1.0);
	//glTranslatef(-this->GetPosition()->GetX(), -this->GetPosition()->GetY(), 0);
	float* tmpdata = freetype::print(font, xpos, ypos, text);
	textdata[0] = *tmpdata;
	textdata[1] = *(tmpdata + 1);
	textdata[2] = *(tmpdata + 2);
	delete [] tmpdata;
	glPopMatrix();
}
void FreeTypeText::SetText(const char* input, ...){
	if(input == 0){
		return;
	}
	if(text != 0)
		delete [] text;
	text = new char [FREETYPEFONTMAXSTRLEN];
	va_list ap;
	va_start(ap, input);
		vsprintf_s(text, FREETYPEFONTMAXSTRLEN, input, ap);
	va_end(ap);
	delete [] ap;
	float *buffer = new float[32];
	glFeedbackBuffer(32, GL_2D, buffer);
	glRenderMode(GL_FEEDBACK);
	Draw();
	glRenderMode(GL_RENDER);
	delete [] buffer;
}
void FreeTypeText::SelectionDraw(){
}
void FreeTypeText::GetDimensions(int dimensions[4]){
	GLint	viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float xpos, ypos;
	xpos = position->GetX();
	ypos = position->GetY();
	if(viewport[2] < viewport[3]){
		xpos += 1;
		xpos = (float)viewport[0] + xpos / 2 * (float)viewport[2];
		ypos += (float)viewport[3] / (float)viewport[2];
		ypos = (float)viewport[1] + ypos / ((float)viewport[3] / (float)viewport[2]) * viewport[3];
	}else{
		ypos ++;
		ypos = (float)viewport[1] + ypos / 2 * (float)viewport[3];
		xpos += (float)viewport[2] / (float)viewport[3];
		xpos = (float)viewport[0] + xpos / ((float)viewport[2] / (float)viewport[3]) / 2 * (float)viewport[2];
	}
	if(this->hAlignment == FGL2DDrawObject::RIGHT){
		xpos -= textdata[0];
	}else if(this->hAlignment == FGL2DDrawObject::HCENTER){
		xpos -= textdata[0] / 2;
	}
	ypos -= font.h;
	if(this->vAlignment == FGL2DDrawObject::VCENTER){
		ypos +=  textdata[1] * textdata[2] / 2;
	}else if(this->vAlignment == FGL2DDrawObject::BOTTOM){
		ypos += textdata[1] * textdata[2];
	}
	dimensions[0] = xpos;
	dimensions[1] = (viewport[1] + viewport[3]) - (ypos + font.h);
	dimensions[2] = textdata[0];
	dimensions[3] = textdata[1] * textdata[2];
}
bool FreeTypeText::CheckPointInElement(int x, int y){
	int dimensions[4];
	GetDimensions(dimensions);
	int zrot = (int)this->zrot;
	if(zrot < 0){
		zrot += (((int)(zrot / -360))+1)*360;
	}
	zrot = zrot % 360;
	int left, right, top, bottom;
	if(!(zrot == 0)){
		if(zrot <= 90 && zrot >= 0){
			float w1, w2;
			left = dimensions[0];
			w1 = cos(zrot * PI / 180) * dimensions[2];
			w2 = cos((90 - zrot) * PI / 180) * dimensions[3];
			right = left + w1 + w2;
			top = dimensions[1] - cos((90 - zrot) * PI / 180) * dimensions[2];
			bottom = dimensions[1] + cos(zrot * PI / 180) * dimensions[3];
		}else if(zrot >= 90 && zrot <= 180){
			left = dimensions[0] - cos((180 - zrot) * PI / 180) * dimensions[2];
			right = dimensions[0] + cos((zrot - 90) * PI / 180) * dimensions[3];	
			float h1, h2;
			h1 = cos((zrot - 90) * PI / 180) * dimensions[2];
			h2 = cos((180 - zrot) * PI / 180) * dimensions[3];
			top = dimensions[1] - h1 - h2;
			bottom = dimensions[1];
		}else if(zrot >= 180 && zrot <= 270){
			float w1 = cos((zrot - 180) * PI / 180) * dimensions[2];
			float w2 = cos((270 - zrot) * PI / 180) * dimensions[3];
			left = dimensions[0] - w1 - w2;
			right = dimensions[0];
			top = dimensions[1] - cos((zrot - 180) * PI / 180) * dimensions[3];
			bottom = dimensions[1] + cos((270 - zrot) * PI / 180) * dimensions[2];
		}else{
			left = dimensions[0] - dimensions[3] / cos(zrot * PI / 180);
			right = dimensions[0] + cos((360 - zrot) * PI / 180) * dimensions[2];
			top = dimensions[1];
			float h1, h2;
			h1 = cos((360 - zrot) * PI / 180) * dimensions[2];
			h2 = cos((zrot - 270) * PI / 180) * dimensions[3];
			bottom = dimensions[1] + h1 + h2;
		}
	}else{
		left = dimensions[0];
		right = dimensions[0] + dimensions[2];
		top = dimensions[1];
		bottom = dimensions[1] + dimensions[3];
	}
	if(x > left && x < right && y > top && y < bottom){
		return true;
	}else{
		return false;
	}
}