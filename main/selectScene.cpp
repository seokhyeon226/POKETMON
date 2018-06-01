#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{

}

HRESULT selectScene::init()
{

	return S_OK;
}

void selectScene::release()
{

}

void selectScene::update()
{

}

void selectScene::render()
{
	TextOut(getMemDC(), WINSIZEX / 2, 100, "ºø∑∫∆Æ æ¿¿Ãø‰!", strlen("ºø∑∫∆Æ æ¿¿Ãø‰!"));
}

