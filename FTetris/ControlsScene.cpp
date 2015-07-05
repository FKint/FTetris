#include "ControlsScene.h"

ControlsScene::ControlsScene(FGameUI *ui):FScene(ui, 2, 50, true)
{
}

ControlsScene::~ControlsScene(void)
{
}
void ControlsScene::Init(){
	objects[0] = controlstext = new FreeTypeText("Tetris 3D by Floris Kint Controls:\n\n   Arrow Left: Move block to the left\n   Arrow Right: Move block to the right\n   Arrow Down: Move block faster downward\n   Arrow Up: Rotate block\n\n   D: Swap 3D/2D View\n   R: Autorotate on/off\n   X: (Auto)rotate around the x-axis\n   Y: (Auto)rotate around the y-axis\n   Z: (Auto)rotate around the z-axis\n   S: Reset view settings\n\n   P: Pause\n   F1: About-dialogue\n   ", "myfont.ttf", 15, new FColor(1, 1, 1), new FVertex(-1, .8, 0), FGL2DDrawObject::LEFT, FGL2DDrawObject::TOP, 0, false);
	objects[1] = menutext = new FreeTypeCommandText(this, FGame::GOTO, FGame::BASEMENU, "Menu", "myfont.ttf", 20, new FColor(0, 1, 0), new FVertex(-1, -1, 0), FGL2DDrawObject::LEFT, FGL2DDrawObject::BOTTOM, 0);
}

void ControlsScene::Command(int command, int extra){
	ui->GetGame()->Command(command, extra);
}
void ControlsScene::MouseLClick(){
	this->ProcessSelectedObjects(this->mousex, this->mousey, 10, 10, true);
}
void ControlsScene::MouseAction(){
	this->ProcessSelectedObjects(this->mousex, this->mousey, 10, 10, false);
}