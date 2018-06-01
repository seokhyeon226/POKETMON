#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame(){}

mainGame::~mainGame(){}

//초기화
HRESULT mainGame::init(void)
{
	//upcasting : 부모클래스를 자식클래스에서 호출한다
	gameNode::init(true);  //게임노드의 init 함수에 타이머 셋팅 및 키매니져 초기화 관련 함수를 실행한다.
	IMAGEMANAGER->addImage("바탕", "우주.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("battle", "battle.bmp", 0, 0, 1536, 79, 16, 1, true, RGB(255, 0, 255));

	//추가
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("missilePF", "missilePF.bmp", 0, 0, 576, 44, 16, 1, true, RGB(255, 0, 255));

	_starScene = new starcraftScene;
	_starScene->init();

	_select = new selectScene;//추가
	_select->init();//추가

	//하나의 게임노드로 윈도우 메세지를 전달하고 싶다
	//그 하나의 노드 로 만든 씬 -> 현재 씬, 그 외 나머지 씬은 동작하지않음.
	_currentScene = _select;//추가

	INIDATA->addData("카오리", "매력도", "100");
	INIDATA->addData("카오리", "나이", "14");

	INIDATA->addData("넵튠", "매력도", "1000");
	INIDATA->addData("넵튠", "나이", "모름");

	INIDATA->iniSave("최애캐들");

	//char* str = INIDATA->loadDataString("최애캐들", "카오리", "나이");
	//int byungsin = INIDATA->loadDataInterger("최애캐들", "넵튠", "매력도");
	return S_OK;
}

//메모리 해제
void mainGame::release(void)
{
	gameNode::release(); //손대지 마셈
}

//연산은 여기서 한다
void mainGame::update(void)	  
{
	gameNode::update();  //손대지 마셈
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_currentScene = _select;
		_currentScene->init();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_currentScene = _starScene;
		_currentScene->init();
	}


	_currentScene->update();
}

//그리는 것은 이제 여기에다
void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== 이 위는 손대지 마시오 =========================
	IMAGEMANAGER->findImage("바탕")->render(getMemDC(), 0, 0);

	_currentScene->render();

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TIMEMANAGER->render(getMemDC());

	//================== 이 아래는 손대지 마시오 ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

