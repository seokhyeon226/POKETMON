#pragma once
#include "gameNode.h"
#include "starcraftScene.h"
#include "selectScene.h"  //추가

class mainGame : public gameNode
{
private:
	gameNode* _starScene;	//추가
	gameNode* _select;		//추가

	gameNode* _currentScene;//추가

public:
	mainGame();
	~mainGame();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();
};

