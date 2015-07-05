#pragma once
//#include <windows.h>
//#include <gl/glut.h>
class FGLDrawObject;
#include "includes.h"
#include "FCommandListener.h"
#include "FColor.h"
#include "FVertex.h"

class FGLDrawObject : public FCommandListener
{
public:
	#pragma message("in fgldrawobject")
	enum Status{
		NORMAL,
		FOCUS,
		ACTION
	};
	enum Commands{
		STATUS,
		HIDE,
		SHOW,
		EXECUTE
	};
	FGLDrawObject(FColor *color, float x, float y, float z, float xrot, float yrot, float zrot, bool standalone = false, bool selectable = false, FGLDrawObject** subobjects = 0, unsigned int subobjectsamount = 0, unsigned int subnamesamount = 0);
	FGLDrawObject(FColor *color, FVertex *position, float xrot, float yrot, float zrot, bool standalone = false, bool selectable = false, FGLDrawObject** subobjects = 0, unsigned int subobjectsamount = 0, unsigned int subnamesamount = 0);
	virtual ~FGLDrawObject(void);
	void Draw(FColor *color, bool standalone);
	void Draw();
	void Draw(bool standalone);
	void Draw(FColor *color);
	virtual void SelectionDraw(){Draw();};
	void SetColor(FColor *color){this->color = color;}
	void SetFocusColor(FColor *color){this->focuscolor = color;}
	void SetActionColor(FColor *color){this->actioncolor = color;}
	FColor * GetColor(){return color;}
	FColor* GetFocusColor(){return focuscolor;}
	FColor* GetActionColor(){return actioncolor;}
	bool GetStandalone(){return standalone;}
	void SetStandalone(bool standalone){this->standalone = standalone;}
	void SetSelectable(bool selectable){this->selectable = selectable;}
	bool GetSelectable(){return selectable;}
	bool GetRenderSelect(){return renderselect;}
	bool GetMultipleSelect(){return multipleselectalowed;}
	bool GetExecutable(){return executable;}
	bool GetDraw(){return draw;}
	unsigned int GetStatus(){return status;}
	FVertex* GetPosition(){return position;}
	void SetPosition(FVertex *position);
	virtual bool CheckPointInElement(int x, int y){return false;};

	void AddSubObject(FGLDrawObject *subobject);
	FGLDrawObject **GetSubObjects(){return subobjects;};
	unsigned int GetSubObjectsAmount(){return subobjectsamount;}
	unsigned int GetSubNamesAmount(){return subnamesamount;}

	void Command(int command, int extra);
	
	void SetXRot(float xrot){this->xrot = xrot;}
	void SetYRot(float yrot){this->yrot = yrot;}
	void SetZRot(float zrot){this->zrot = zrot;}
	float GetXRot(){return xrot;}
	float GetYRot(){return yrot;}
	float GetZRot(){return zrot;}
	void SetDraw(bool draw){this->draw = draw;}
protected:
	void SetStatus(unsigned int status = 0){this->status = status;}
	void Init(FColor *color, FVertex *position, float xrot, float yrot, float zrot, bool standalone, bool selectable, FGLDrawObject** subobjects, unsigned int subobjectsamount, unsigned int subnamesamount);
	bool standalone;
	bool executable;
	FColor *color;
	FColor *focuscolor;
	FColor *actioncolor;
	virtual void InternDraw(bool standalone){};
	bool selectable;
	bool multipleselectalowed;
	bool renderselect;
	bool draw;
	unsigned int status;

	FVertex *position;
	float xrot;
	float yrot;
	float zrot;

	FGLDrawObject **subobjects;
	unsigned int subobjectsamount;
	unsigned int subnamesamount;
};
