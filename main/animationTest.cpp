#include "stdafx.h"
#include "animationTest.h"


animationTest::animationTest()
{
}


animationTest::~animationTest()
{

}

HRESULT animationTest::init()
{
	_camel = IMAGEMANAGER->addFrameImage("낙타", "camel.bmp", 300, 267, 4, 3, true, RGB(255, 0, 255));

	//디폴트 애니메이션
	_ani1 = new animation;
	_ani1->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(), _camel->getFrameHeight());
	_ani1->setDefPlayFrame(true, false);
	_ani1->setFPS(1);

	//배열 애니메이션
	int arrAni[] = { 1, 10, 2 ,9, 3, 6 };
	_ani2 = new animation;
	_ani2->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(),
		_camel->getFrameHeight());
	_ani2->setPlayFrame(arrAni, 6, false);
	_ani2->setFPS(1);

	//구간 애니메이션
	_ani3 = new animation;
	_ani3->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(),
		_camel->getFrameHeight());
	_ani3->setPlayFrame(2, 8, false, true);
	_ani3->setFPS(1);

	IMAGEMANAGER->addImage("폭발", "explosion.bmp", 832, 62, true, RGB(255, 0, 255));

	_effect = new effect;
	_effect->init(IMAGEMANAGER->findImage("폭발"), 32, 62, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("explosion", "explosion.bmp", 832, 62, 32, 62, 1.0f, 1.0f, 1000);

	return S_OK;
}

void animationTest::release()
{

}

void animationTest::update()
{
	if (KEYMANAGER->isOnceKeyDown('Q')) _ani1->start();
	if (KEYMANAGER->isOnceKeyDown('W')) _ani2->start();
	if (KEYMANAGER->isOnceKeyDown('E')) _ani3->start();
	//getElapsedTime = 밀리세컨이 들어옴
	_ani1->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani3->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);



	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_effect->startEffect(_ptMouse.x, _ptMouse.y);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		EFFECTMANAGER->play("explosion", _ptMouse.x, _ptMouse.y);
	}

	EFFECTMANAGER->play("explosion", RND->getFromIntTo(200, 300), RND->getFromIntTo(200, 300));

	_effect->update();
	EFFECTMANAGER->update();
}

void animationTest::render()
{
	_camel->aniRender(getMemDC(), 100, 100, _ani1);
	_camel->aniRender(getMemDC(), 100, 200, _ani2);
	_camel->aniRender(getMemDC(), 100, 300, _ani3);

	_effect->render();
	EFFECTMANAGER->render();
}
