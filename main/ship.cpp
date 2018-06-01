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
	bulletMove();//추가
}

void ship::render(void)
{
	draw();
	bulletDraw();//추가
}


void ship::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);

	char str[128];
	sprintf(str, "%d도, %3.2f", int(_angle * 180 / PI), _speed);
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

//오늘의 핵심, 오늘의 뽀인트
void ship::move(void)
{
	int frame;			//이미지 프레임 번호
	float angle;		//이미지 각도
	//현제 3시방향이 0도
	//특정 각도별로 프레임이 지정이 된다
	//1.94(90도)          0.3
	//한 원 프레임 8, 16, 32
	angle = _angle + PI / 16;//_angle + PI16;          //현재 앵글(0) + 11.25도를 앵글에 대입을 하면 32프레임이 나온다(360도로 계산해서)
	//1프레임 = 11.25
	//특정 각도별로 지녀야할 프레임의 보정을 해준다
	//16프레임의 절반(180도까지 구하기 위해)
	frame = int(angle / PI8);          //현재 앵글 / 22.5(11.25 / 22.5) 정수 0가 나온다.
	_image->setFrameX(frame);          //x축으로 움직이니 setFrameX에 frame를 넣는다.

	float elapsedTime = TIMEMANAGER->getElapsedTime();   //밀리세컨드
	float moveSpeed = elapsedTime * 100;                 //애니메이션 속도

	_x += cosf(_angle) * _speed * moveSpeed;      //플레이어 x축 각도 조절
	_y += -sinf(_angle) * _speed * moveSpeed;	  //플레이어 y축 각도 조절

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
