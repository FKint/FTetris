#include "HighScoresScene.h"
#include "includes.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

HighScoresScene::HighScoresScene(FGameUI *ui):FScene(ui, 12, 50, true)
{
}

HighScoresScene::~HighScoresScene(void)
{
}

void HighScoresScene::Init(){
	int pointstosaveamount = 5;
	ifstream ifile;
	ifile.open("score.ftetris3d", ios::in);
	unsigned int *prevscores = new unsigned int[pointstosaveamount];
	for(int j = 0; j < pointstosaveamount; j++)
		prevscores[j] = 0;
	short i = 0;
	if(ifile.is_open()){
		while(!ifile.eof()){
			ifile >> prevscores[i];
			i++;
		}
	}
	ifile.close();
	unsigned int *newscores = new unsigned int[pointstosaveamount];
	for(int y = 0; y < i && y < pointstosaveamount; y++){
		unsigned int currheighest = 0;
		for(int x = 0; x < i && x < pointstosaveamount;  x++){
			if(prevscores[x] >= prevscores[currheighest])
				currheighest = x;

		}
		newscores[y] = prevscores[currheighest];
		prevscores[currheighest] = 0;
	}
	for(int j = 0; j < i; j++){
		stringstream ss;
		ss << newscores[j];
		string tmppoint = ss.str();
		stringstream ss1;
		ss1 << j + 1 << ".";
		string rank = ss1.str();
		objects[2 * j] = new FreeTypeText(rank.c_str(), "myfont.ttf", 15, new FColor(1, 0, 0), new FVertex(-.5, .5 - (j * .2), 0), FGL2DDrawObject::LEFT, FGL2DDrawObject::VCENTER, 0, false);
		objects[2 * j + 1] = new FreeTypeText(tmppoint.c_str(), "myfont.ttf", 15, new FColor(1, 0, 0), new FVertex(.5, .5 - (j * .2), 0), FGL2DDrawObject::RIGHT, FGL2DDrawObject::VCENTER, 0, false);
	}
	if(i == 0)
		objects[0] = new FreeTypeText("No highscores yet", "myfont.ttf", 20, new FColor(1, 0, 0), new FVertex(0, 0, 0), FGL2DDrawObject::HCENTER, FGL2DDrawObject::VCENTER, 0, false);
	objects[pointstosaveamount * 2] = new FreeTypeCommandText(this, FGame::GOTO, FGame::BASEMENU, "Menu", "myfont.ttf", 20, new FColor(0, 1, 0), new FVertex(-1, -1, 0), FGL2DDrawObject::LEFT, FGL2DDrawObject::BOTTOM, 0);
	objects[pointstosaveamount * 2 + 1] = new FreeTypeCommandText(this, RESET, 0, "Reset Highscores", "myfont.ttf", 12, new FColor(1, 0, 0), new FVertex(0, .8, 0), FGL2DDrawObject::HCENTER, FGL2DDrawObject::BOTTOM, 0);
}
void HighScoresScene::MouseAction(){
	this->ProcessSelectedObjects(this->mousex, this->mousey, 10, 10, false);
}
void HighScoresScene::MouseLClick(){
	this->ProcessSelectedObjects(this->mousex, this->mousey, 10, 10, true);
}
void HighScoresScene::Command(int command, int extra){
	switch(command){
		case RESET:
			ResetScores();
			break;
		default:
			this->ui->GetGame()->Command(command, extra);
	}
}
void HighScoresScene::ResetScores(){
	ifstream is;
	is.open("score.ftetris3d");
	if(is.is_open()){
		is.close();
		if(remove("score.ftetris3d") != 0)
			MessageBox(0, "Error at resetting highscores.", "Error", 0);
		else{
			for(int i = 1; i < 10; i+=2){
				if(objects[i])
					((FreeTypeText*)objects[i])->SetText("0");
			}
		}
	}
}