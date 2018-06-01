#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
	: _timer(NULL)
{
}


timeManager::~timeManager()
{

}

HRESULT timeManager::init(void)
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release(void)
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
	}
}

void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

void timeManager::render(HDC hdc)
{
	char str[256];
	string frameRate;
	//font ��׶��� ���� 2���� �ִ�
	//TRANSPARENT : ����
	//OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);
/*
https://blog.naver.com/alsdn726/221276453749
��ó���� : ������ ������ �̸� ó���Ǵ� ������ ���Ѵ�.����ó������ �Ѵ�. ���� �����Ͻ� 
�ۼ��� �ڵ庸�� ���� ��ó�������� �� ������ ���� ����ȴ�. �����δ�
���� ó���� ���� ��ó���� : #include = ��� ���ϰ� ���� �ܺ� ������ �о ���Խ�ų �� ���
���� ���Ǹ� ���� ��ó���� : #define = ������� �����ϱ� ���� �����(��ũ��)
					      #undef = #define���� �̹� ���ǵ� ��ũ�θ� ��ȿȭ��Ų��
���� ó���� ���� ��ó���� : #if ~ #endif = if���ϰ� ���, ��� ������ ������ ���� ������ ���� �� �ִ�.
						  #ifdef ~ #endif = � ��ũ�ΰ� ���ǵǾ��ִ����� ������. ��ũ�ΰ� ���� �Ǿ� �ִٸ� a�� ������ �ȵǸ�  b�� ������
						  #ifndef = ��������� ��ġ�� ���� ���� ������ ��ũ��
						  #else, else�� ���� �ǹ�
						  #elif else + if
���� ó���� ���� ��ó���� : #error = �ҽ� ���ο� ���� ���� �޼����� ����Ѵ�.
������� ���� ��ó���� : #line = �ҽ��ڵ��� ���ȣ�� �����ϱ� ���� ��(����� �� �� ���� ����)
������ �ɼ� ó���� ���� ��ó���� : #pragma
*/

	//���� debug����϶�(�������� ���� 30�� ������)
#ifdef _DEBUG
	{
		wsprintf(str, "framePerSec (FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}
#else
	{
		wsprintf(str, "framePerSec (FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif

}
