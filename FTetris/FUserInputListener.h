#pragma once
#include "includes.h"

class FUserInputListener
{
public:
#pragma message("in fuserinputlistener")
	FUserInputListener(bool handleevents = true);
	~FUserInputListener(void);
	void EventHandler(UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	//input
	bool handleevents;
	//mouse
	unsigned short mouseldownx, mouseldowny;
	bool mouseldown;
	void MouseLDown(unsigned short x, unsigned short y, WPARAM wParam){
		bool click = false;
		if(!mouseldown){
			click = true;
		}
		mouseldown = true;
		mouseldownx = x;
		mouseldowny = y;
		if(click){
			MouseLClick();
		}else{
			MouseAction();
		}
	}
	void MouseLUp(){mouseldown = false; MouseAction();}

	unsigned short mouserdownx, mouserdowny;
	bool mouserdown;
	void MouseRDown(unsigned short x, unsigned short y, WPARAM wParam){
		mouserdown = true;
		mouserdownx = x;
		mouserdowny = y;
		MouseAction();
	}
	void MouseRUp(){mouserdown = false; MouseAction();}
	unsigned short mousemdownx, mousemdowny;
	bool mousemdown;
	void MouseMDown(unsigned short x, unsigned short y, WPARAM wParam){
		mousemdown = true;
		mousemdownx = x;
		mousemdowny = y;
		MouseAction();
	}
	void MouseMUp(){mousemdown = false; MouseAction();}

	void MouseScroll(unsigned short x, unsigned short y, WPARAM wParam){MouseAction();};

	unsigned short mousex, mousey;
	unsigned short prevmousex, prevmousey;
	void MouseMoved(unsigned short x, unsigned short y, WPARAM wParam){
		prevmousex = mousex;
		prevmousey = mousey;
		mousex = x;
		mousey = y;
		MouseAction();
	}
	//end of mouse
	//keyboard
	bool keys[256];
	void SetKey(int key, bool value, LPARAM lParam){this->keys[key] = value; KeyStatusChanged(key); KeyboardAction();}
	//end of keyboard

	//Specific inputhandling
	void ResetMouseButtons();
	virtual void MouseLClick(){}
	virtual void MouseRClick(){}
	virtual void MouseMClick(){}
	virtual void MouseAction(){}
	virtual void KeyboardAction(){}
	virtual void KeyStatusChanged(int key){}
	//end of specific inputhandling
	//end of input
};
