#include "FUserInputListener.h"

FUserInputListener::FUserInputListener(bool handleevents)
{
	this->handleevents = handleevents;
	this->mouseldown = false;
	this->mouseldownx = 0;
	this->mouseldowny = 0;
	this->mouserdown = false;
	this->mouserdownx = 0;
	this->mouserdowny = 0;
	this->mousemdown = false;
	this->mousemdownx = 0;
	this->mousemdowny = 0;
	this->mousey = 0;
	this->mousex = 0;
	for(int i = 0; i < 256; i ++)
		this->keys[i] = false;
}

FUserInputListener::~FUserInputListener(void)
{
}
void FUserInputListener::EventHandler(UINT uMsg, WPARAM wParam, LPARAM lParam){
	if(handleevents){
		switch(uMsg){
			case WM_MOUSELEAVE:
				this->ResetMouseButtons();
				break;
			case WM_MOUSEMOVE:
				this->MouseMoved(LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_LBUTTONDOWN:
				this->MouseLDown(LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_LBUTTONUP:
				this->MouseLUp();
				break;
			case WM_KEYDOWN:
				this->SetKey(wParam, true, lParam);
				break;
			case WM_KEYUP:
				this->SetKey(wParam, false, lParam);
				break;
			default:
				break;
		}
	}
}
void FUserInputListener::ResetMouseButtons(){
	this->mouseldown = false;
	this->mouserdown = false;
	this->mousemdown = false;

}