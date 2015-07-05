#include "FGLDrawObject.h"

FGLDrawObject::FGLDrawObject(FColor *color, float x, float y, float z, float xrot, float yrot, float zrot, bool standalone, bool selectable, FGLDrawObject** subobjects, unsigned int subobjectsamount, unsigned int subnamesamount)
{
	Init(color, new FVertex(x, y, z), xrot, yrot, zrot, standalone, selectable, subobjects, subobjectsamount, subnamesamount);
}
FGLDrawObject::FGLDrawObject(FColor *color, FVertex *position, float xrot, float yrot, float zrot, bool standalone, bool selectable, FGLDrawObject** subobjects, unsigned int subobjectsamount, unsigned int subnamesamount)
{
	Init(color, position, xrot, yrot, zrot, standalone, selectable, subobjects, subobjectsamount, subnamesamount);
}

FGLDrawObject::~FGLDrawObject()
{
	if(this->color != 0)
		delete color;
	if(this->focuscolor != 0)
		delete focuscolor;
	if(this->actioncolor != 0)
		delete actioncolor;
	if(this->subobjects != 0){
		for(unsigned int i = 0; i < subobjectsamount; i++){
			if(subobjects[i] != 0)
				delete subobjects[i];
		}
		delete subobjects;
	}
	if(position != 0)
		delete position;

}
void FGLDrawObject::Init(FColor *color, FVertex *position, float xrot, float yrot, float zrot, bool standalone, bool selectable, FGLDrawObject** subobjects, unsigned int subobjectsamount, unsigned int subnamesamount){
	executable = false;
	multipleselectalowed = true;
	renderselect = true;
	this->focuscolor = 0;
	this->actioncolor = 0;
	this->subnamesamount = subnamesamount;
	this->subobjectsamount = subobjectsamount;
	//this->subobjects = subobjects;

	this->subobjects = subobjectsamount > 0?(FGLDrawObject**)malloc(sizeof(FGLDrawObject*) * subobjectsamount):0;
	if(subobjects){
		for(unsigned int i = 0; i < subobjectsamount; i ++){
			if(subobjects[i]){
				this->subobjects[i] = subobjects[i];
			}else{
				this->subobjects[i] = 0;
			}
		}
	}else{
		for(unsigned int i = 0; i < subobjectsamount; i++){
			this->subobjects[i] = 0;
		}
	}
	this->position = position;
	this->color = color;
	this->standalone = standalone;
	this->selectable = selectable;
	this->draw = true;
	this->status = NORMAL;
	this->xrot = xrot;
	this->yrot = yrot;
	this->zrot = zrot;
}
void FGLDrawObject::Draw(){
	FColor *color = this->color;
	switch(status){
		case FOCUS:
			if(focuscolor != 0)
				color = focuscolor;
			break;
		case ACTION:
			if(actioncolor != 0)
				color = actioncolor;
			break;
	}
	Draw(color, GetStandalone());
}
void FGLDrawObject::Draw(bool standalone){
	FColor *color = this->color;
	switch(status){
		case FOCUS:
			if(focuscolor != 0)
				color = focuscolor;
			break;
		case ACTION:
			if(actioncolor != 0)
				color = actioncolor;
			break;
	}
	Draw(color, standalone);
}
void FGLDrawObject::Draw(FColor *color, bool standalone){
	if(draw){
		if(standalone){
			glPushMatrix();
			glTranslatef(this->GetPosition()->GetX(), this->GetPosition()->GetY(), this->GetPosition()->GetZ());
			//glRotatef(1.0, xrot, yrot, zrot);
			glRotatef(xrot, 1.0, 0.0, 0.0);
			glRotatef(yrot, 0.0, 1.0, 0.0);
			glRotatef(zrot, 0.0, 0.0, 1.0);
		}
		if(color == 0){
			switch(status){
				case FOCUS:
					if(focuscolor != 0)
						color = focuscolor;
					break;
				case ACTION:
					if(actioncolor != 0)
						color = actioncolor;
					break;
				case NORMAL:
				default:
					color = this->color;
			}
		}
		if(color != 0){
			glColor4f(color->GetR(), color->GetG(), color->GetB(), color->GetA());
		}
		InternDraw(standalone);
		for(unsigned int i = 0; i < subobjectsamount; i ++){
			if(subobjects[i] != 0){
				subobjects[i]->Draw(subobjects[i]->GetStandalone());
			}
		}
		if(standalone)
			glPopMatrix();
	}
}
void FGLDrawObject::AddSubObject(FGLDrawObject *subobject){
	for(unsigned int i = 0; i < subobjectsamount; i ++){
		if(subobjects[i] == 0){
			subobjects[i] = subobject;
			return;
		}
	}
	subobjectsamount ++;
	FGLDrawObject **tmpobjects = (FGLDrawObject **)(malloc(sizeof(FGLDrawObject*) * subobjectsamount));
	for(unsigned int i = 0; i < subobjectsamount - 1; i ++){
		tmpobjects[i] = subobjects[i];
	}
	tmpobjects[subobjectsamount - 1] = subobject;
	if(subobjects != 0)
		delete [] subobjects;
	subobjects = tmpobjects;
}
void FGLDrawObject::Command(int command, int extra){
	switch(command){
		case STATUS:
			this->SetStatus(extra);
			break;
		default:
			break;
	}
}
void FGLDrawObject::SetPosition(FVertex *position){
	if(this->position)
		delete this->position;
	this->position = position;
}