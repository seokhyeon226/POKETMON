#include "stdafx.h"
#include "pixelCollision.h"


pixelCollision::pixelCollision(){ }


pixelCollision::~pixelCollision(){ }

HRESULT pixelCollision::init()
{
	//��� ����ƾ ����
	IMAGEMANAGER->addImage("���", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//�� �̹��� ����
	_ball = IMAGEMANAGER->addImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	//���� ��ǥ(�ȼ� �浹�� ���� �ڵ����� ���� ���� �������� ����)
	_x = WINSIZEX / 2 - 150;
	_y = WINSIZEY / 2 + 100;

	//�� �̹��� ������ ��Ʈ�� ����
	//>getWidth() = �̹����� ũ��� ����
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	_probeY = _y + _ball->getHeight() / 2;


	return S_OK;
}

void pixelCollision::release()
{

}

void pixelCollision::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 3;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 3;

	//���ڴ� �����̴� ������Ʈ���� ��ǥ�� ����ؼ� �޾��ش�.
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	_probeY = _y + _ball->getHeight() / 2;

	for (int i = _probeY - 50; i < _probeY + 50; ++i)
	{
		//GetPixel = Ư�� ��ġ��(x,y)�� �ִ� �ȼ��� rgb���� �����ݴϴ�.
		//�� �۾��� �ϱ� ���ؼ��� Select�� ��Ʈ���� ���������� �ľ��ϰ� ��Ʈ���� �̹��� ���۸� ����
		//�ش� ��ġ�� �����ϴ� BYTE���� �����Ͽ� RGB���� �M
		//COLORREF = RGB������ ǥ��
		//RGB�������� ǥ�� = "���"�̶�� �̹����� RGB���� ����
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("���")->getMemDC(), _x, i);

		//GetRValue = ���� ��� �ڵ�
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		//���� RGB������ ����Ÿ ������ �ƴҰ��
		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}

	}
}

void pixelCollision::render()
{
	IMAGEMANAGER->findImage("���")->render(getMemDC());

	_ball->render(getMemDC(), _rc.left, _rc.top);

}


