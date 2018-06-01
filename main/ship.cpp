#include "stdafx.h"
#include "ship.h"


ship::ship()
{
}


ship::~ship()
{

}

HRESULT ship::init(const char* imageName, int x, int y)
{
	_image = IMAGEMANAGER->findImage(imageName);

	_x = x;
	_y = y;

	_angle = 0.0f;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_speed = 0;
	_radius = _image->getFrameWidth() / 2;

	_bullet = new bullet;
	_bullet->init("bullet", 30, 400);


	return S_OK;
}

void ship::release(void)
{

}

void ship::update(void)
{
	keyControl();
	move();
	bulletMove();//�߰�
}

void ship::render(void)
{
	draw();
	bulletDraw();//�߰�
}


void ship::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);

	char str[128];
	sprintf(str, "%d��, %3.2f", int(_angle * 180 / PI), _speed);
	TextOut(getMemDC(), _rc.left, _rc.top - 15, str, strlen(str));
}

void ship::keyControl(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_angle >= PI2) _angle -= PI2;
		_angle += 0.2f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_angle <= 0) _angle += PI2;
		_angle -= 0.2f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _speed += 0.04f;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _speed -= 0.04f;
}

//������ �ٽ�, ������ ����Ʈ
void ship::move(void)
{
	int frame;			//�̹��� ������ ��ȣ
	float angle;		//�̹��� ����
	//���� 3�ù����� 0��
	//Ư�� �������� �������� ������ �ȴ�
	//1.94(90��)          0.3
	//�� �� ������ 8, 16, 32
	angle = _angle + PI / 16;//_angle + PI16;          //���� �ޱ�(0) + 11.25���� �ޱۿ� ������ �ϸ� 32�������� ���´�(360���� ����ؼ�)
	//1������ = 11.25
	//Ư�� �������� ������� �������� ������ ���ش�
	//16�������� ����(180������ ���ϱ� ����)
	frame = int(angle / PI8);          //���� �ޱ� / 22.5(11.25 / 22.5) ���� 0�� ���´�.
	_image->setFrameX(frame);          //x������ �����̴� setFrameX�� frame�� �ִ´�.

	float elapsedTime = TIMEMANAGER->getElapsedTime();   //�и�������
	float moveSpeed = elapsedTime * 100;                 //�ִϸ��̼� �ӵ�

	_x += cosf(_angle) * _speed * moveSpeed;      //�÷��̾� x�� ���� ����
	_y += -sinf(_angle) * _speed * moveSpeed;	  //�÷��̾� y�� ���� ����

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void ship::bulletFire(void)
{
	float x = _x + cosf(_angle) * 50;
	float y = _y + -sinf(_angle) * 50;

	_bullet->fire(x, y, _angle, 10);
}

void ship::bulletMove(void)
{
	_bullet->update();
}

void ship::bulletDraw(void)
{
	_bullet->render();
}
