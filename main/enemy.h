#pragma once
#include "gameNode.h"

class enemy : public gameNode {
protected:
	image * _imageName;
	RECT _rc;

	//������ ��ȣ�� ���� �δ� ������
	int _currentFrameX;
	int _currentFrameY;

	int _count;				//ī��Ʈ
	int _fireCount;			//�߻� ī��Ʈ
	int _rndFireCount;		//�����ϰ� �߻��ϱ� ���� ��ġ
public:
	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	void move();		//������ �Լ�
	void draw();		//�׷��ִ� �Լ�

	bool bulletCountFire();	//�Ѿ� �߻� ī��Ʈ �Լ�

	inline RECT getRect() { return _rc; }


};

