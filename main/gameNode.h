#pragma once
#include "image.h" //�߰�

//����۶�� �� ��Ʈ�� �̹����� �ϳ� �����صд�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);//�߰�

//�������� �ٲ۴�, ��ü���� ���α׷����� ���ϰ� ���� �ϱ����� ������ �ٲ���
//�������뿡�� ����۸� ȣ���ϱ⺸��, �� �ϳ��� ��DC�� �����ΰ� �ű�� ������ �������ϴ°��� ���ϴ�

class gameNode
{
private:
	//��ü ����� �߰�
	HDC _hdc;
	bool _managerInit;		         //�Ŵ������� �ʱ�ȭ �� ���̳�
public:
	//��ü ����� �߰�
	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);	    //�׷��ִ� �Լ�

	image* getBackBuffer(void) { return _backBuffer; }//�߰�
	//MemDC -> ������ִ� �޸� ��Ȱ
	HDC getMemDC() { return _backBuffer->getMemDC(); }//�߰�
	HDC getHDC() { return _hdc; }//�߰�

	 
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

