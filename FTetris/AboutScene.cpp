#include "AboutScene.h"

AboutScene::AboutScene(FGameUI *ui):FScene(ui, 2, 50, true)
{
}
void AboutScene::Init(){
	objects[0] = infotext = new FreeTypeText("This game has been made by Floris Kint. \nThe game is based on Tetris, whose rights are not owned\nby the programmer of this program\n(go to http://www.tetris.com for more information\n about Tetris).\nYou are not allowed to sell this program.\nIt's completely free and it's forbidden\nto earn money with it.For more information, you can \ncontact Floris Kint at kintfloris@gmail.com\nwith subject '3D Tetris'.\n\nHave fun with the game.\n\nFloris Kint", "myfont.ttf", 12, new FColor(1, 1, 1), new FVertex(-1, .8, 0), FGL2DDrawObject::LEFT, FGL2DDrawObject::TOP, 0, false);
	objects[1] = menutext = new FreeTypeCommandText(this, FGame::GOTO, FGame::BASEMENU, "Menu", "myfont.ttf", 20, new FColor(0, 1, 0), new FVertex(-1, -1, 0), FGL2DDrawObject::LEFT, FGL2DDrawObject::BOTTOM, 0);
}

AboutScene::~AboutScene(void)
{
}
void AboutScene::Command(int command, int extra){
	ui->GetGame()->Command(command, extra);
}
void AboutScene::MouseLClick(){
	this->ProcessSelectedObjects(this->mousex, this->mousey, 10, 10, true);
}
void AboutScene::MouseAction(){
	this->ProcessSelectedObjects(this->mousex, this->mousey, 10, 10, false);
}
