#include "stdafx.h"
#include "mainGame.h"

//��������
HINSTANCE	_hInstance;		//�ν��Ͻ� �ڵ�
HWND		_hWnd;			//�ڵ�

LPCSTR _lpszClass = TEXT("Neptune Window API");

POINT _ptMouse;

//����
mainGame _mg;

//�Լ��� ������ Ÿ��
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;		//�޽��� ����ü
	WNDCLASS	wndClass;		//������ ���� ����ü

	_hInstance = hInstance;

	//������ ������ ���� �����Ѵ�
	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��� ��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//Ŀ�� ������ ���
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//���� ������ ���
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ� ��ȣ
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;							    //������ Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//������ �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ â ��Ÿ��

																	//������ ���� ���
	RegisterClass(&wndClass);

	//������ ���� ������ â ����

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,		//������ ��Ÿ��
		WINSTARTX,					//������ â ������ǥ X
		WINSTARTY,					//������ â ������ǥ Y
		WINSIZEX,					//������ ����ũ��
		WINSIZEY,					//������ ����ũ��
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	//Ŭ���̾�Ʈ ���� ������
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//������ ������ â�� ȭ�鿡 ���������ش�(�����ش�)
	ShowWindow(_hWnd, cmdShow);

	//GetMessage : �޽����� ������ �׶� ó���Ѵ�
	//PeekMessage : �޽����� ������ �ʾƵ� ���Ϲ��� �����ִ�.

	//���ΰ����� �����ϸ� �ʱ�ȭ�� �����ϸ�    -------------------------------------------------�߰�
	if (FAILED(_mg.init()))
	{
		//����ǰŶ�
		return 0;
	}
	/*
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);		//Ű���� �Է� �� �� �޽��� ó�� ���
		DispatchMessage(&message);		//������ �����쿡 �޽����� �������ִ� ����
	}
	*/
	while (true)
	{
		//PM_REMOVE = �޼��� ť���� �޼��� ����
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			//WM_QUIT = ���α׷� ����
			if (message.message == WM_QUIT) break;

			TranslateMessage(&message);		//Ű���� �Է� �� �� �޽��� ó�� ���
			DispatchMessage(&message);		//������ �����쿡 �޽����� �������ִ� ����
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_mg.update();
			_mg.render();
		}
	}

	_mg.release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//������ ������ �������� ���ش�
	AdjustWindowRect(&winRect, WINSTYLE, false);

	//������ ��ġ�� ������
	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);


}