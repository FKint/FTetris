#include "BaseMenuScene.h"
#include "FreeTypeCommandText.h"
#include "FGLQuad.h"

BaseMenuScene::BaseMenuScene(FGameUI *ui):FScene(ui, 6, 50, true)
{
}

BaseMenuScene::~BaseMenuScene(void)
{
}
void BaseMenuScene::Init(){
	this->menucolor = new FColor(0, 1, .8, 1);
	this->focuscolor = new FColor(0, 1, 0);
	this->actioncolor = new FColor(1, 1, 0);
	this->menufontname = "myfont.ttf";
	this->menuitemsize = 20;
	objects[0] = newgameitem = new FreeTypeCommandText(this, FGame::NEWGAME, 0, "New Game", this->menufontname, menuitemsize, new FColor(menucolor), new FVertex(.8, .6, 0), FGL2DDrawObject::RIGHT, FGL2DDrawObject::VCENTER, 0);
	objects[1] = controlsitem = new FreeTypeCommandText(this, FGame::GOTO, FGame::HELP, "Controls", this->menufontname, menuitemsize, new FColor(menucolor), new FVertex(.8, .4, 0), FGL2DDrawObject::RIGHT, FGL2DDrawObject::VCENTER, 0);
	objects[2] = highscoresitem = new FreeTypeCommandText(this, FGame::GOTO, FGame::HIGHSCORES, "Highscores", this->menufontname, menuitemsize, new FColor(menucolor), new FVertex(.8, .2, 0), FGL2DDrawObject::RIGHT, FGL2DDrawObject::VCENTER, 0);
	objects[3] = aboutitem = new FreeTypeCommandText(this, FGame::GOTO, FGame::ABOUTSCREEN, "About", this->menufontname, menuitemsize, new FColor(menucolor), new FVertex(.8, 0, 0), FGL2DDrawObject::RIGHT, FGL2DDrawObject::VCENTER, 0);
	objects[4] = quititem= new FreeTypeCommandText(this, FGame::QUIT, 0, "Quit", this->menufontname, menuitemsize, new FColor(menucolor), new FVertex(.8, -.2, 0), FGL2DDrawObject::RIGHT, FGL2DDrawObject::VCENTER, 0);
	for(unsigned int i = 0; i < this->objectsamount; i ++){
		if(objects[i]){
			objects[i]->SetFocusColor(new FColor(focuscolor));
			objects[i]->SetActionColor(new FColor(actioncolor));
		}
	}
	//objects[5] = rotatequad = new FGLQuad(new FColor(1.0, 1.0,1.0,0.5), new FVertex(-2.0, 0, 0), new FGLPoint(0, 0, 0, 0, 0, 0, 1.0, 0, false, false), new FGLPoint(1, 0, 0, 0, 0, 0, 1.0, 0, false, false), new FGLPoint(1, 1, 0, 0, 0, 0, 1.0, 0, false, false), new FGLPoint(0, 1, 0, 0, 0, 0, 1.0, 0, false, false), 0, 0, 0, false);
}
void BaseMenuScene::Update(){
	//MessageBox(0, "in basemenuscene update", "", 0);
	//rotatequad->SetXRot(rotatequad->GetXRot() + 3);
}
void BaseMenuScene::MouseAction(){
	this->ProcessSelectedObjects(this->mousex, this->mousey, 10, 10, false);
}
void BaseMenuScene::MouseLClick(){
	this->ProcessSelectedObjects(this->mousex, this->mousey, 10, 10, true);
}