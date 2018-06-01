#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame(){}

mainGame::~mainGame(){}

//�ʱ�ȭ
HRESULT mainGame::init(void)
{
	//upcasting : �θ�Ŭ������ �ڽ�Ŭ�������� ȣ���Ѵ�
	gameNode::init(true);  //���ӳ���� init �Լ��� Ÿ�̸� ���� �� Ű�Ŵ��� �ʱ�ȭ ���� �Լ��� �����Ѵ�.
	IMAGEMANAGER->addImage("����", "����.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("battle", "battle.bmp", 0, 0, 1536, 79, 16, 1, true, RGB(255, 0, 255));

	//�߰�
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("missilePF", "missilePF.bmp", 0, 0, 576, 44, 16, 1, true, RGB(255, 0, 255));

	_starScene = new starcraftScene;
	_starScene->init();

	_select = new selectScene;//�߰�
	_select->init();//�߰�

	//�ϳ��� ���ӳ��� ������ �޼����� �����ϰ� �ʹ�
	//�� �ϳ��� ��� �� ���� �� -> ���� ��, �� �� ������ ���� ������������.
	_currentScene = _select;//�߰�

	INIDATA->addData("ī����", "�ŷµ�", "100");
	INIDATA->addData("ī����", "����", "14");

	INIDATA->addData("��ƪ", "�ŷµ�", "1000");
	INIDATA->addData("��ƪ", "����", "��");

	INIDATA->iniSave("�־�ĳ��");

	//char* str = INIDATA->loadDataString("�־�ĳ��", "ī����", "����");
	//int byungsin = INIDATA->loadDataInterger("�־�ĳ��", "��ƪ", "�ŷµ�");
	return S_OK;
}

//�޸� ����
void mainGame::release(void)
{
	gameNode::release(); //�մ��� ����
}

//������ ���⼭ �Ѵ�
void mainGame::update(void)	  
{
	gameNode::update();  //�մ��� ����
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

//�׸��� ���� ���� ���⿡��
void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== �� ���� �մ��� ���ÿ� =========================
	IMAGEMANAGER->findImage("����")->render(getMemDC(), 0, 0);

	_currentScene->render();

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TIMEMANAGER->render(getMemDC());

	//================== �� �Ʒ��� �մ��� ���ÿ� ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

