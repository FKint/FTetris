#pragma once
class FTetrisGameController;
#include "FTetrisBlockSet.h"
#include "FTetrisScene.h"
#include "FTetrisGameField.h"
#include "FTetrisCube.h"

class FTetrisGameController
{
public:
#pragma message("ftetrsigamecontroller.h")
	FTetrisGameController(FTetrisScene *scene, int rows, int cols, FTetrisGameField *field);
	~FTetrisGameController(void);
	int GetRows(){return rows;}
	void SetRows(int rows);
	void SetCols(int cols);
	int GetCols(){return cols;}
	void DrawCubes();
	void Resize();
	void Update();
	void SetRight(bool down){right = down; righting = down?righting:false;}
	void SetLeft(bool down){left = down; lefting = down?lefting:false;}
	void SetDown(bool down){this->down = down; downing = down?downing:false;}
	void SetRotate(bool down){rotate = down?true:rotate;}
	void Action();
	void Start();
	void Interrupt(){active = false;}
	void SetActive(bool activeflag){
		if(activeflag && !active){
			Start();
		}
		if(active && !activeflag){
			Interrupt();
		}
	}
	bool GetActive(){return active;}
	void BlockSetRight();
	void BlockSetLeft();
	void BlockSetDown();
	void BlockSetRotate();
	void Set3D(bool d3);
	unsigned int GetPoints(){return points;}
	void StartGame();
	void NewGame(short rows, short cols);
	bool GetGameMade(){return gamemade;}
	bool GetGameStarted(){return gamestarted;}
	bool GetGameDone(){return gamedone;}
	FTetrisBlockSet *GetPreBlockSet(){return preblockset;};
	void Pause();
protected:
	int rows, cols;
	FTetrisGameField *field;
	FTetrisCube **box;
	int updates;
	FTetrisBlockSet *blockset;
	FTetrisBlockSet *preblockset;
	void NextTetrisBlockSet();
	unsigned int speed;
	void DismissBlockSet();
	void ProcessBlockSet();
	bool CheckBoxOccupied(short x, short y);
	void GameOver();
	void CheckLines();
	unsigned int points;
	unsigned int lasttick;
	unsigned int updateinterval;
	bool active, initialized;
	unsigned int lastleftaction;
	unsigned int lastrightaction;
	unsigned int lastdownaction;
	unsigned int actioninterval;
	bool right, left, down, rotate;
	bool righting, lefting, downing;
	bool playing;
	unsigned int linesdestroyingstart;
	bool linesdestroying;
	unsigned int linesdestroyingtime;
	short *linestoremove;
	short linestoremoveamount;
	void RemoveLines(short* linestoremove, short amount);
	bool gamemade;
	bool gamestarted;
	bool gamedone;
	FTetrisScene *scene;
	bool blockdestroyed;
	FTetrisBlockSet *GenerateBlockSet();
	int SubmitScore(unsigned int points);
};
