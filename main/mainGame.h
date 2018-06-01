#pragma once
#include "gameNode.h"
#include "starcraftScene.h"
#include "selectScene.h"  //�߰�

class mainGame : public gameNode
{
private:
	gameNode* _starScene;	//�߰�
	gameNode* _select;		//�߰�

	gameNode* _currentScene;//�߰�

public:
	mainGame();
	~mainGame();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();
};

