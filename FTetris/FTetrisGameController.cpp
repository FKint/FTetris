#include "FTetrisGameController.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

FTetrisGameController::FTetrisGameController(FTetrisScene *scene, int rows, int cols, FTetrisGameField *field)
{
	this->preblockset = 0;
	this->scene = scene;
	this->field = field;
	this->field->SetController(this);
	this->box = 0;
	this->cols = cols;
	this->rows = rows;

	this->speed = 4;

	this->active = false;
	this->initialized = false;
	this->gamemade = false;
	this->blockdestroyed = true;

	this->linesdestroyingtime = 13;
	this->updateinterval = 50;
	this->actioninterval = 1;
	this->linestoremove = 0;
	//this->StartGame();
}

FTetrisGameController::~FTetrisGameController(void)
{
}
void FTetrisGameController::DrawCubes(){
	for(int i = 0; i < cols * rows; i ++){
		if(box[i]){
			box[i]->Draw();
		}
	}
	if(blockset){
		if(blockset->cubes)
			for(int i = 0; i < 4; i ++)
				if(blockset->cubes[i])
					blockset->cubes[i]->Draw();
	}
}

void FTetrisGameController::Resize(){
	float cubewidth = field->GetCubeWidth();
	float cubeheight = field->GetCubeHeight();
	float boxwidth = field->GetBoxWidth();
	float boxheight = field->GetBoxHeight();
	for(int i = 0; i < cols * rows; i ++){
		if(box[i]){
			int row = (int)(i / cols);
			int col = (int)(i % rows);
			box[i]->SetWidth(cubewidth);
			box[i]->SetHeight(cubeheight);
			box[i]->SetPosition(new FVertex((col + 1) * boxwidth - cubewidth, -((row + 1) * boxheight - cubeheight), 0));
		}
	}
	if(this->blockset)
		blockset->SetDimensions(boxheight, boxwidth, cubewidth, cubeheight);
}
void FTetrisGameController::Update(){
	if(playing){
		ProcessBlockSet();
	}else{
		if(linesdestroying){
			if(this->linesdestroyingstart < this->updates - linesdestroyingtime){
				if(linestoremove){
					RemoveLines(linestoremove, linestoremoveamount);
					linestoremoveamount = 0;
					delete [] linestoremove;
					linestoremove = 0;
				}
				playing = true;
			}
		}
	}
}
void FTetrisGameController::RemoveLines(short* linestoremove, short amount){
	if(linestoremove){
		for(short j = 0; j < amount; j ++){
			short i = linestoremove[j];
			for(int k = i * cols; k < (i + 1) * cols; k++){
				if(box[k] != 0){
					delete box[k];
					box[k] = 0;
				}
			}
			float boxheight = field->GetBoxHeight();
			for(int k = i * cols; k >= 0; k--){
				if(box[k] != 0){
					box[k]->SetPosition(new FVertex(box[k]->GetPosition()->GetX(), box[k]->GetPosition()->GetY() - boxheight, 0)); 
					box[k + cols] = box[k];
					box[k] = 0;
				}
			}
		}
	}
}
void FTetrisGameController::CheckLines(){
	int linesamount = 0;
	if(linestoremove)
		delete [] linestoremove;
	linestoremove = new short[rows];
	for(int i = 0; i < rows; i ++){
		bool rowfull = true;
		for(int j = 0; j < cols; j ++){
			if(!CheckBoxOccupied(j, i)){
				rowfull = false;
				break;
			}
		}
		if(rowfull){
			linestoremove[linesamount] = i;
			linesamount ++;
			for(int k = i * cols; k < (i + 1) * cols; k++){
				if(box[k] != 0){
					box[k]->SetColor(new FColor(.7, .7, .7));
				}else{
					MessageBox(0, "Error, box can't be 0 at checklines.", "", 0);
				}
			}
		}
	}
	int newpoints = 0;
	for(int i = 1; i <= linesamount; i ++){
		newpoints += (i + 1) * 25;
	}
	this->points += newpoints;
	this->linestoremoveamount = linesamount;
	if(linesamount > 0){
		this->linesdestroying = true;
		this->linesdestroyingstart = updates;
		this->playing = false;
		scene->GamePointsChanged(points);
	}

}
FTetrisBlockSet *FTetrisGameController::GenerateBlockSet(){
	bool texture = scene->GetTexture();
	unsigned int textureid = scene->GetTextureId();
	FTetrisBlockSet::BLOCKOPTIONS option = FTetrisBlockSet::I;
	FColor *color = new FColor(0, 0, 0, 1);
	int myoption = rand();
	switch(myoption % 7){
		case 0:
			option = FTetrisBlockSet::I;
			color->SetR(1);
			break;
		case 1:
			option = FTetrisBlockSet::J;
			color->SetG(1);
			break;
		case 2:
			option = FTetrisBlockSet::L;
			color->SetB(1);
			break;
		case 3:
			option = FTetrisBlockSet::O;
			color->SetR(1);
			color->SetB(1);
			break;
		case 4:
			option = FTetrisBlockSet::T;
			color->SetB(1);
			color->SetG(1);
			break;
		case 5:
			option = FTetrisBlockSet::S;
			color->SetR(1);
			color->SetG(1);
			break;
		case 6:
			option = FTetrisBlockSet::Z;
			color->SetR(1);
			color->SetG(1);
			color->SetB(1);
			break;
	}
	FTetrisBlockSet *blockset = new FTetrisBlockSet(0, 0, option, field->GetBoxWidth(), field->GetBoxHeight(), field->GetCubeWidth(), field->GetCubeHeight(), color, false, texture, textureid, false);
	return blockset;
}
void FTetrisGameController::NextTetrisBlockSet(){
	if(!gamedone){
		if(preblockset == 0){
			preblockset = GenerateBlockSet();
		}
		FTetrisBlockSet *blockset = preblockset;
		blockset->SetXPos(short(cols / 2) - 1);
		blockset->SetYPos(0);
		blockset->SetDimensions(field->GetBoxWidth(), field->GetBoxHeight(), field->GetCubeWidth(), field->GetCubeHeight());
		blockset->Set3D(field->Get3D());
		preblockset = GenerateBlockSet();
		scene->PreBlockSetChanged(preblockset);
		for(int i = 0; i < 4; i ++){
			if(CheckBoxOccupied(blockset->x[i] + blockset->GetXPos(), blockset->y[i] + blockset->GetYPos())){
				GameOver();
				this->scene->GameStatusChanged();
				return;
			}
		}
		this->blockset = blockset;
	}	
}
void FTetrisGameController::BlockSetRight(){
	if(right && (lastrightaction < updates - this->actioninterval || !righting)){
		if(blockset){
			this->lastrightaction = updates;
			righting = true;
			bool ok = true;
			for(int i = 0; i < 4; i ++){
				short newx = blockset->x[i] + blockset->GetXPos() + 1;
				if(newx < 0 || newx >= cols){
					ok = false;
					break;
				}
				if(CheckBoxOccupied(newx, blockset->y[i] + blockset->GetYPos())){
					ok = false;
					break;
				}
			}
			if(ok){
				blockset->SetXPos(blockset->GetXPos() + 1);
			}
		}
	}
}
void FTetrisGameController::BlockSetLeft(){
	if(left && (lastleftaction < updates - this->actioninterval || !lefting)){
		if(blockset){
			this->lastleftaction = updates;
			lefting = true;
			bool ok = true;
			for(int i = 0; i < 4; i ++){
				short newx = blockset->x[i] + blockset->GetXPos() - 1;
				if(newx < 0 || newx >= cols){
					ok = false;
					break;
				}
				if(CheckBoxOccupied(newx, blockset->y[i] + blockset->GetYPos())){
					ok = false;
					break;
				}
			}
			if(ok){
				blockset->SetXPos(blockset->GetXPos() - 1);
			}
		}
	}
}
void FTetrisGameController::BlockSetDown(){
	if(down && (lastdownaction < updates - this->actioninterval || !downing)){
		if(blockset){
			this->lastdownaction = updates;
			downing = true;
			bool ok = true;
			for(int i = 0; i < 4; i ++){
				short newy = blockset->y[i] + blockset->GetYPos() + 1;
				if(newy >= rows){
					ok = false;
					break;
				}

				if(CheckBoxOccupied(blockset->x[i] + blockset->GetXPos(), newy)){
					ok = false;
					break;
				}
			}
			if(ok){
				blockset->SetYPos(blockset->GetYPos() + 1);
			}else{
				DismissBlockSet();
				return;
			}
		}
	}
}
void FTetrisGameController::BlockSetRotate(){
	if(rotate){
		if(blockset){
			rotate = false;
			short newx[4];
			short newy[4];
			blockset->Rotate(newx, newy);
			bool ok = true;
			for(int i = 0; i < 4; i ++){
				if(newx[i] + blockset->GetXPos() < 0 || newx[i] + blockset->GetXPos() >= cols){
					ok = false;
					break;
				}
				if(newy[i] + blockset->GetYPos() < 0 || newy[i] + blockset->GetYPos() >= rows){
					ok = false;
					break;
				}
				if(CheckBoxOccupied(newx[i] + blockset->GetXPos(), newy[i] + blockset->GetYPos())){
					ok = false;
					break;
				}
			}
			if(ok){
				for(int i = 0; i < 4; i ++){
					blockset->x[i] = newx[i];
					blockset->y[i] = newy[i];
				}
				blockset->Resized();
			}

		}
	}
}
void FTetrisGameController::ProcessBlockSet(){
	blockdestroyed = false;
	this->BlockSetDown();
	if(!this->playing || blockdestroyed)
		return;
	if(blockset){
		if(updates % (int)(speed * 2) == 0){
			bool ok = true;
			for(int i = 0; i < 4; i ++){
				short newy = blockset->y[i] + blockset->GetYPos() + 1;
				if(newy >= rows){
					ok = false;
					break;
				}
				if(CheckBoxOccupied(blockset->x[i] + blockset->GetXPos(), newy)){
					ok = false;
					break;
				}
			}
			if(ok){
				blockset->SetYPos(blockset->GetYPos() + 1);
			}else{
				DismissBlockSet();
			}
		}
	}
	if(!this->playing || blockdestroyed)
		return;
	this->BlockSetRight();
	if(!this->playing || blockdestroyed)
		return;
	this->BlockSetLeft();
	if(!this->playing || blockdestroyed)
		return;
	this->BlockSetRotate();
}
void FTetrisGameController::DismissBlockSet(){
	if(blockset != 0){
		for(int i = 0; i < 4; i ++){
			if(!CheckBoxOccupied(blockset->x[i] + blockset->GetXPos(), blockset->y[i] + blockset->GetYPos())){
				this->box[(blockset->y[i] + blockset->GetYPos()) * cols + blockset->x[i] + blockset->GetXPos()] = blockset->cubes[i];
			}
		}
		this->blockdestroyed = true;
		CheckLines();
		delete blockset;
		blockset = 0;
		NextTetrisBlockSet();
	}
}
bool FTetrisGameController::CheckBoxOccupied(short x, short y){
	return (box[y * cols + x] != 0);
}
void FTetrisGameController::GameOver(){
	int ranking = this->SubmitScore(points);
	stringstream ss;
	ss << "Game Over\n You finished with " << points << " points.\n";
	if(ranking >= 0)
		ss << "This score comes at place " << ranking + 1 << " in the ranking.";
	else
		ss << "That's not good enough for a place in the ranking.";
	string msg = ss.str();
	const char *message = msg.c_str();
	MessageBox(0, message, "", 0);
	this->playing = false;
	this->gamedone = true;
}

void FTetrisGameController::Action(){
	if(this->active){
		if(this->initialized){
			if(this->updateinterval > 0){
				unsigned int currtick = GetTickCount();
				while((currtick - this->lasttick) >= this->updateinterval){
					this->lasttick += this->updateinterval;
					this->Update();
					this->updates ++;
				}
			}else{
				this->Update();
				this->updates++;
			}
		}
	}
}
void FTetrisGameController::Start(){
	if(!this->initialized){
		initialized = true;
		playing = true;
	}
	this->active = true;
	this->lasttick = GetTickCount();
}
void FTetrisGameController::NewGame(short rows, short cols){
	if(this->box){
		for(int i = 0; i < this->cols * this->rows; i ++){
			if(this->box[i])
				delete this->box[i];
		}
		if(this->box)
			delete this->box;
	}
	this->box = 0;

	this->rows = rows;
	this->cols = cols;
	this->field->SetCols(cols);
	this->field->SetRows(rows);
	this->box = (FTetrisCube**)malloc(sizeof(FTetrisCube*) * cols * rows);
	for(int i = 0; i < cols * rows; i ++){
		box[i] = 0;
	}

	this->points = 0;
	this->blockset = 0;
	this->preblockset = GenerateBlockSet();
	this->updates = 0;
	this->playing = false;
	this->lasttick = GetTickCount();
	this->lastleftaction = 0;
	this->lastrightaction = 0;
	this->lastdownaction = 0;
	this->left = false;
	this->right = false;
	this->down = false;
	this->rotate = false;
	this->righting = false;
	this->lefting = false;
	this->downing = false;
	this->linesdestroying = false;
	this->linesdestroyingstart = 0;
	if(this->linestoremove){
		delete [] this->linestoremove;
	}
	this->linestoremove = 0;
	this->linestoremoveamount = 0;
	this->gamemade = true;
	this->gamestarted = false;
	this->gamedone = false;
	this->scene->GameStatusChanged();
	this->scene->GamePointsChanged(this->points);
}
void FTetrisGameController::StartGame(){
	if(!playing){
		if(!gamemade){
			NewGame(this->rows, this->cols);
		}
		if(!this->initialized){
			Start();
		}
		NextTetrisBlockSet();
		this->updates = 0;
		playing = true;
		this->gamestarted = true;
		this->scene->GameStatusChanged();
	}
}
void FTetrisGameController::Pause(){
	if(active)
		Interrupt();
	else
		Start();
	this->scene->GameStatusChanged();
}
void FTetrisGameController::Set3D(bool d3){
	if(this->blockset){
		this->blockset->Set3D(d3);
	}
	for(int i = 0; i < GetCols() * GetRows(); i ++)
		if(box[i])
			box[i]->Set3D(d3);
}
int FTetrisGameController::SubmitScore(unsigned int points){
	int pointstosaveamount = 5;
	ifstream ifile;
	ifile.open("score.ftetris3d", ios::in/* | ios::binary*/);
	unsigned int *prevscores = new unsigned int[pointstosaveamount];
	short i = 0;
	int lessthan = 0;
	if(ifile.is_open()){
		while(!ifile.eof()){
			ifile >> prevscores[i];
			//char tmpchar;
			//ifile >> tmpchar;
			if(prevscores[i] > points)
				lessthan ++;

			i++;
		}
		ifile.close();
	}
	if(i < pointstosaveamount){
		prevscores[i] = points;
		i++;
	}else{
		if(lessthan < pointstosaveamount){
			unsigned int tmpnewplace = 0;
			unsigned int currconcurrent = prevscores[0];
			for(int j = 0; j < pointstosaveamount; j ++){
				if(points > prevscores[j]){
					if(prevscores[j] < currconcurrent){
						tmpnewplace = j;
						currconcurrent = prevscores[j];
					}
				}
			}
			prevscores[tmpnewplace] = points;
		}else
			lessthan = -1;
	}
	unsigned int *newscores = new unsigned int[pointstosaveamount];
	for(int y = 0; y < i; y++){
		unsigned int currheighest = 0;
		for(int x = 0; x < i;  x++){
			if(prevscores[x] >= prevscores[currheighest])
				currheighest = x;

		}
		newscores[y] = prevscores[currheighest];
		prevscores[currheighest] = 0;
	}
	ofstream ofile;
	ofile.open("score.ftetris3d", ios::out/* | ios::binary */| ios::trunc);
	for(int x = 0; x < i; x ++){
		ofile << newscores[x] << ((x == i - 1)?"":" ");
	}
	ofile.close();
	return lessthan;
}