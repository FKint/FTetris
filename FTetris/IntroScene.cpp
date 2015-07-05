#include "IntroScene.h"
#include "FreeTypeText.h"

IntroScene::IntroScene(FGameUI *ui):FScene(ui, 1, 50, true)
{
}

IntroScene::~IntroScene(void)
{
	
}
void IntroScene::KeyboardAction(){
	if(this->keys[0x1B]){
		this->keys[0x1B] = false;
		this->ui->GetGame()->Command(FGame::GOTO, FGame::BASEMENU);
	}
}
void IntroScene::Init(){
	objects[0] = new FreeTypeText("FTetris By Floris Kint", "myfont.ttf", 15, new FColor(1.0, 0, 0, .0), new FVertex(0, 0, 0), FGL2DDrawObject::HCENTER, FGL2DDrawObject::VCENTER, 0, false);
}
void IntroScene::Update(){
	//objects[0]->SetZRot(objects[0]->GetZRot() + 5);
	objects[0]->SetColor(new FColor(objects[0]->GetColor()->GetR(), objects[0]->GetColor()->GetG(), objects[0]->GetColor()->GetB(), objects[0]->GetColor()->GetA()+.015));
	if(/*this->updates == 60*/objects[0]->GetColor()->GetA() >= 1 && active){
		this->ui->GetGame()->Command(FGame::GOTO, FGame::BASEMENU);
		this->SetActive(false);
	}
}