#pragma once
#include "image.h" //추가

//백버퍼라는 빈 비트맵 이미지를 하나 설정해둔다
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);//추가

//구조부터 바꾼다, 객체지향 프로그래밍을 편하고 쉽게 하기위해 구조를 바꾸자
//여러군대에서 백버퍼를 호출하기보단, 단 하나의 백DC를 만들어두고 거기로 접근을 용이케하는것이 편하다

class gameNode
{
private:
	//전체 지우고 추가
	HDC _hdc;
	bool _managerInit;		         //매니저등을 초기화 할 것이냐
public:
	//전체 지우고 추가
	virtual HRESULT init(void);		//초기화 함수
	virtual HRESULT init(bool managerInit);
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);	    //그려주는 함수

	image* getBackBuffer(void) { return _backBuffer; }//추가
	//MemDC -> 출력해주는 메모리 역활
	HDC getMemDC() { return _backBuffer->getMemDC(); }//추가
	HDC getHDC() { return _hdc; }//추가

	 
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

