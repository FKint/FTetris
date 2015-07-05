#include "FScene.h"
#include "FreeTypeText.h"
FScene::FScene(FGameUI *ui, const unsigned int objectsamount, int updateinterval, bool handleevents):FCommandListener(), FUserInputListener(handleevents)
{
	xtrans = 0;
	ytrans = 0;
	ztrans = -6;
	this->ui = ui;
	this->updateinterval = updateinterval;
	this->initialized = false;
	this->active = false;
	this->lasttick = 0;
	this->objectsamount = objectsamount;
	this->updates = 0;
	if(objectsamount){
		this->objects = (FGLDrawObject**)malloc(sizeof(FGLDrawObject*) * objectsamount);
		for(unsigned int i = 0; i < objectsamount; i++)
			objects[i] = 0;
	}
}

FScene::~FScene(void)
{
	if(objects){
		for(unsigned int i = 0; i < objectsamount; i++){
			if(objects[i]){
				delete objects[i];
				objects[i] = 0;
			}
		}
		if(objects)
			delete objects;
	}
}
void FScene::Start(){
	if(!this->initialized){
		Init();
		initialized = true;
		this->updates = 0;
	}
	this->active = true;
	this->lasttick = GetTickCount();
}
void FScene::Action(){
	if(this->active){
		if(this->initialized){
			if(this->updateinterval > 0){
				unsigned int currtick = GetTickCount();
				while((currtick - this->lasttick) >= this->updateinterval){
					this->lasttick += this->updateinterval;
					this->Update();
					this->updates ++;
				}
			}else{
				this->Update();
				this->updates++;
			}
		}
	}
}
void FScene::Command(int command, int extra){
	this->ui->GetGame()->Command(command, extra);
}
void FScene::Draw(int mode){
	glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor4f(1, 1, 1, 0.5f);
			glTranslatef(xtrans, ytrans, ztrans);
			for(unsigned int i = 0; i < this->objectsamount; i ++){
				glColor3f(.0f, 1.0f, 0.0f);
				if(this->objects[i] != 0){
						this->objects[i]->Draw();
				}
			}
		glPushMatrix();
			SceneDraw();
		glPopMatrix();
	glPopMatrix();
}
bool* FScene::GetObjectsPicked(float x, float y, float width, float height, FGLDrawObject** objects, unsigned int amount, unsigned int *closestelement, unsigned int* deepestelement){
	bool* objectspicked = new bool[amount];
	int* pickedamount = new int;
	unsigned int* pickedobjects = GetPickedObjects(x, y, width, height, objects, amount, pickedamount, closestelement, deepestelement);
	for(unsigned int i = 0; i < amount; i++){
		objectspicked[i] = false;
	}
	for(int i = 0; i < *pickedamount; i++){
		objectspicked[pickedobjects[i]] = true;
	}
	delete pickedamount;
	delete [] pickedobjects;
	return objectspicked;
}
unsigned int* FScene::GetPickedObjects(float x, float y, float width, float height, FGLDrawObject **objects, unsigned int amount, int *pickedamount, unsigned int* closestelement, unsigned int* deepestelement){
	int namesamount = 0;
	for(unsigned int i = 0; i < amount; i ++){
		if(objects[i] != 0){
			namesamount ++;
			namesamount += objects[i]->GetSubNamesAmount();
		}
	}
	namesamount += (amount * 3);
	unsigned int *result = new unsigned int[namesamount];
	
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(namesamount, result);
	glRenderMode(GL_SELECT);
	glInitNames();
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluPickMatrix(x, viewport[3] - y, width, height, viewport);
		gluPerspective(45.0, (float)(viewport[2]-viewport[0])/(float)(viewport[3]-viewport[1]), 0.1, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(xtrans, ytrans, ztrans);
		for(unsigned int i = 0; i < amount; i++){
			if(objects[i] != 0){
				if(objects[i]->GetSelectable() && objects[i]->GetRenderSelect()){
					glPushName(i);
					objects[i]->SelectionDraw();
					glPopName();
				}
			}
		}
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	int picked = glRenderMode(GL_RENDER);

	unsigned int *pickedindices = new unsigned int[picked];
	int tmpindex = 0;
	unsigned int names;
	unsigned int* ptr = result;
	if (picked > 0){
		unsigned int mindepth;
		unsigned int maxdepth;
		mindepth = *(ptr + 1);
		maxdepth = *(ptr + 2);
		*deepestelement = *(ptr + 3);
		*closestelement = *(ptr + 3);
		for(int i = 0; i < picked; i ++){
			names = *ptr;
			ptr++;
			if(*ptr <= mindepth){
				*closestelement = *(ptr + 2);
				mindepth = *ptr;
			}
			ptr++;
			if(maxdepth < *ptr){
				*deepestelement = *(ptr + 1);
				maxdepth = *ptr;
			}
			ptr++;
			pickedindices[tmpindex] = *ptr;
			tmpindex ++;
			ptr += names;
		}
	}
	*pickedamount = picked;

	if(namesamount > 1){
		delete [] result;
	}else{
		delete result;
	}

	return pickedindices;
}
void FScene::ProcessSelectedObjects(short int x, short int y, short int pickwidth, short int pickheight, bool execute){
	if(this->initialized){
		unsigned short x = this->mousex;
		unsigned short y = this->mousey;
		unsigned int selectedindex;
		unsigned int *closestelement = new unsigned int;
		unsigned int *deepestelement = new unsigned int;
		bool* indicesselected = GetObjectsPicked(x, y, pickwidth, pickwidth, this->objects, this->objectsamount, closestelement, deepestelement);
		bool onepicked = false;
		bool theoneselected = false;
		for(unsigned int i = 0; i < objectsamount; i++){
			if(objects[i]){
				if(!indicesselected[i]){
					if(objects[i]->GetDraw()){
						if(objects[i]->GetSelectable()){
							if(!objects[i]->GetRenderSelect()){
								if(objects[i]->CheckPointInElement(x, y)){
									indicesselected[i] = true;
									if(!theoneselected || objects[i]->GetMultipleSelect() == false){
										selectedindex = i;
										theoneselected = true;
									}
								}
							}
						}
					}
				}
				if(indicesselected[i]){
					this->objects[i]->Command(FGLDrawObject::STATUS,FGLDrawObject::FOCUS);
					onepicked = true;
				}else{
					this->objects[i]->Command(FGLDrawObject::STATUS, FGLDrawObject::NORMAL);
				}
			}
		}
		if(onepicked){
			if(execute){
				if(!theoneselected){
					selectedindex = *closestelement;
				}
				this->objects[selectedindex]->Command(FGLDrawObject::STATUS, FGLDrawObject::ACTION);
				if(this->objects[selectedindex]->GetExecutable()){
					this->objects[selectedindex]->Command(FGLDrawObject::EXECUTE, 0);
				}
			}
		}
		delete [] indicesselected;
		delete closestelement;
		delete deepestelement;
	}
}