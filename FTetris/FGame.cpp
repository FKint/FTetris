#include "FGame.h"

FGame::FGame(void)
{
	this->block = false;
	this->active = false;
	this->stopped = false;
	changescene = false;
}

FGame::~FGame(void)
{
	delete this->ui;
}
void FGame::Exit(){
	this->stopped = true;
	PostQuitMessage(0);
}
bool FGame::Start(char *title){
	this->ui = new FGameUI(this, "FGame", title, 640, 480, 0, 100, 32, false);
	this->ui->Show();
	this->active = true;
	this->stopped = false;
	BOOL success = true;
	this->Command(GOTO, INTRO);
	MSG msg;
	while(!this->stopped){
		if(((this->block || !this->active) && (GetMessage(&msg, this->ui->GetHWND(), 0, 0) >= 0)) || PeekMessage(&msg, this->ui->GetHWND(), 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT){
				this->stopped = true;
				return !success;
			}else{
				if(msg.message == WM_CLOSE){
					MessageBox(NULL, "close", "", NULL);
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}else{
			if(changescene){
				this->ui->SetScene(this->GoTo(scenetogoto));
				changescene= false;
			}
			this->Action();
		}
	}
	return !success;
}
void FGame::Action(){
	this->ui->Update();
}
void FGame::Command(int command, int extra){
	if(!MyCommand(command, extra)){
		switch(command){
			case GOTO:
				//this->ui->SetScene(this->GoTo(extra));
				changescene = true;
				scenetogoto = extra;
				break;
			case QUIT:
				this->Exit();
				break;
			default:
				break;
		}
	}
}
FScene* FGame::GoTo(int stat){
	FScene *scene;
	switch(stat){
		case INTRO:
		case BASEMENU:
			
		case GAME:
			
		case EXITSCREEN:
			
		case NONE:
		default:
			scene = 0;
	}
	return scene;
}