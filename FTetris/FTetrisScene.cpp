#include "FTetrisScene.h"
#include <sstream>
using namespace std;
#include "FTetrisBlockSet.h"
#include "FTetrisGameController.h"
#include "FTetrisGameField.h"
#include "FreeTypeCommandText.h"
#include "FTetrisPreField.h"
#include "FTextureLoader.h"
#pragma message("ftetrisscene")
FTetrisScene::FTetrisScene(FGameUI *ui, int rows, int cols):FScene(ui, 10, 25, true)
{
	this->rows = rows;
	this->cols = cols;
	this->scale = 2.5;
	unsigned int amount = 1;
	unsigned int *buffer = new unsigned int[amount];
	char *files[] = {
		"textures/smallborder1.bmp"
	};
	int parameters[][3] = {{GL_LINEAR, GL_LINEAR, FGL_IMAGE_2D}};
	if(FOpenGL::FLoadGLTextures(buffer, files, parameters, amount) != amount){
		MessageBox(this->ui->GetHWND(), "Error at loading textures. Make sure the textures are in the .\textures directory.", "Error", 0);
		texture = false;
	}else{
		texture = true;
		textureid = buffer[0];
	}
	autorot = false;
	autorotx = false;
	autoroty = false;
	autorotz = false;

}

FTetrisScene::~FTetrisScene(void)
{
}
void FTetrisScene::Init(){
	objects[0] = mainfield = new FTetrisGameField(0, 1, 1, new FColor(0.3, 0.3, 0.8, .45), new FVertex(-.5, 0, 0), 1, (float)rows / (float)cols, this->scale, true, 0, 0, 0);
	gamecontroller = new FTetrisGameController(this, rows, cols, mainfield);
	objects[1] = prefield = new FTetrisPreField(gamecontroller->GetPreBlockSet(),4,4, new FColor(1, 1, 0, .5), new FVertex(1.2, .5, 0), 1, 1, 1, false, 0, 0, 0);
	objects[2] = pointstext = new FreeTypeText("0", "myfont.ttf", 20, new FColor(0.0, 1.0, .5), new FVertex(.5, .75, 0), FGL2DDrawObject::RIGHT, FGL2DDrawObject::VCENTER, 0, false);
	objects[3] = controltext = new FreeTypeText("Switch 2D/3D: D\nReset View: S\nAutorotate: R\n(Auto)Rotate X/Y/Z: X/Y/Z\nPause: P", "myfont.ttf", 12, new FColor(1, 1, 1), new FVertex(.2, -.2, 0), FGL2DDrawObject::LEFT, FGL2DDrawObject::TOP, 0, false);
	objects[4] = startgametext = new FreeTypeCommandText(this, START, 0, "Start Game", "myfont.ttf", 40, new FColor(1, 0, 1), new FVertex(0, 0, 0), FGL2DDrawObject::HCENTER, FGL2DDrawObject::VCENTER, 0);
	objects[5] = restartgametext = new FreeTypeCommandText(this, RESTART, 0, "Restart", "myfont.ttf", 20, new FColor(1, 0, 0), new FVertex(1, -1, 0), FGL2DDrawObject::RIGHT, FGL2DDrawObject::BOTTOM, 0);
	objects[6] = newgametext = new FreeTypeCommandText(this, NEW, 0, "New Game", "myfont.ttf", 40, new FColor(1.0, 0, 0), new FVertex(0, 0, 0), FGL2DDrawObject::HCENTER, FGL2DDrawObject::VCENTER, 0);
	objects[7] = pausegametext = new FreeTypeCommandText(this, PAUSE, 0, "Pause Game", "myfont.ttf", 20, new FColor(1, 0, 0), new FVertex(0, -1, 0), FGL2DDrawObject::HCENTER, FGL2DDrawObject::BOTTOM, 0);
	objects[8] = menutext = new FreeTypeCommandText(this, FGame::GOTO, FGame::BASEMENU, "Menu", "myfont.ttf", 20, new FColor(0, 1, 0), new FVertex(-1, -1, 0), FGL2DDrawObject::LEFT, FGL2DDrawObject::BOTTOM, 0);
	objects[9] = resetviewtext = new FreeTypeCommandText(this, RESETVIEW, 0, "Reset View", "myfont.ttf", 12, new FColor(1, 0, 0), new FVertex(1, .5, 0), FGL2DDrawObject::RIGHT, FGL2DDrawObject::VCENTER, 0);
	gamecontroller->NewGame(this->rows, this->cols);
	gamecontroller->StartGame();
	GameStatusChanged();
}
void FTetrisScene::GameStatusChanged(){
	if(gamecontroller){
		startgametext->SetDraw(gamecontroller->GetGameMade() && !gamecontroller->GetGameDone() && !gamecontroller->GetGameStarted());
		newgametext->SetDraw(!gamecontroller->GetGameMade() || gamecontroller->GetGameDone());
		mainfield->SetDraw(gamecontroller->GetGameMade());
		pointstext->SetDraw(gamecontroller->GetGameMade());
		prefield->SetDraw(gamecontroller->GetGameMade());
		resetviewtext->SetDraw(gamecontroller->GetGameMade());
		restartgametext->SetDraw(gamecontroller->GetGameMade());
		pausegametext->SetDraw(gamecontroller->GetGameMade()&&!gamecontroller->GetGameDone());
		pausegametext->SetText(gamecontroller->GetActive()?"Pause Game":"Continue Game");
	}
}
void FTetrisScene::GamePointsChanged(int points){
	if(gamecontroller){
		stringstream ss;
		ss << gamecontroller->GetPoints();
		string mystring = ss.str();
		pointstext->SetText(mystring.c_str());
	}
}
void FTetrisScene::Update(){
	if(gamecontroller){
		gamecontroller->Action();
	}
	if(autorot){
		if(this->mainfield){
			if(autorotx)
				mainfield->SetXRot(mainfield->GetXRot() + .5);
			if(autoroty)
				mainfield->SetYRot(mainfield->GetYRot() + .5);
			if(autorotz)
				mainfield->SetZRot(mainfield->GetZRot() + .5);
		}
	}
}
void FTetrisScene::KeyStatusChanged(int key){
	switch(key){
		case VK_LEFT:
			gamecontroller->SetLeft(keys[key]);
			break;
		case VK_RIGHT:
			gamecontroller->SetRight(keys[key]);
			break;
		case VK_DOWN:
			gamecontroller->SetDown(keys[key]);
			break;
		case VK_UP:
			gamecontroller->SetRotate(keys[key]);
			break;
		case 0x50://p
			if(keys[key]){
				gamecontroller->Pause();
				keys[key] = false;
			}
			break;
		case 0x53:
			if(keys[key]){
				Command(RESETVIEW, 0);
			}
			break;
		case VK_F1:
			if(gamecontroller->GetActive())
				this->gamecontroller->Pause();
			this->ui->GetGame()->Command(FGame::ABOUT, 0);
			if(gamecontroller->GetActive())
				this->gamecontroller->Pause();
			keys[key] = false;
			break;
		case 0x58://x
			if(keys[key]){
				if(autorot)
					autorotx = !autorotx;
				else
					this->mainfield->SetXRot(mainfield->GetXRot() + 2);
			}
			break;
		case 0x59://y
			if(keys[key]){
				if(autorot)
					autoroty = !autoroty;
				else
					this->mainfield->SetYRot(mainfield->GetYRot() + 2);
			}
			break;
		case 0x5A://z
			if(keys[key]){
				if(autorot)
					autorotz = !autorotz;
				else
					this->mainfield->SetZRot(mainfield->GetZRot() + 2);
			}
			break;
		case 0x52://r
			if(keys[key])
				this->autorot = !autorot;
			break;
		case 0x44://d
			if(keys[key])
				mainfield->Set3D(!mainfield->Get3D());
	}
}
void FTetrisScene::Command(int command, int extra){
	switch(command){
		case START:
			gamecontroller->StartGame();
			break;
		case RESTART:
			gamecontroller->NewGame(rows, cols);
			gamecontroller->StartGame();
			break;
		case NEW:
			gamecontroller->NewGame(rows, cols);
			break;
		case PAUSE:
			gamecontroller->Pause();
			break;
		case RESETVIEW:
			if(mainfield){
				mainfield->SetXRot(0);
				mainfield->SetYRot(0);
				mainfield->SetZRot(0);
				mainfield->Set3D(false);
			}
			break;
		default:
			FScene::Command(command, extra);
			break;
	}
}
void FTetrisScene::MouseAction(){
	this->ProcessSelectedObjects(this->mousex, this->mousey, 10, 10, false);
}
void FTetrisScene::MouseLClick(){
	this->ProcessSelectedObjects(this->mousex, this->mousey, 10, 10, true);
}
void FTetrisScene::PreBlockSetChanged(FTetrisBlockSet *blockset){
	prefield->SetBlockSet(blockset);
}