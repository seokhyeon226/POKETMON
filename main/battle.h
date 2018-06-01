#pragma once
#include "ship.h"

class battle : public ship
{
private:
	missilePF* _missile;   //추가
public:
	battle();
	~battle();

	virtual HRESULT init(const char* imageName, int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void keyControl(void);

	virtual void missileFire();//추가
	virtual void missileMove();//추가
	virtual void missileDraw();//추가


};

