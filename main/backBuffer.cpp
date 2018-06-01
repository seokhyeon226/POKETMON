#include "stdafx.h"
#include "backBuffer.h"

backBuffer::backBuffer()
	: _backBufferInfo(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}

backBuffer::~backBuffer()
{
}

HRESULT backBuffer::init(int width, int height)
{
	//�̹��� ������ ���� �ִ�!? �� ������ �ض�
	if (_backBufferInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_backBufferInfo = new backBuffer_INFO;
	_backBufferInfo->resID = 0;
	_backBufferInfo->hMemDC = CreateCompatibleDC(hdc);//�� DC������ ����
	_backBufferInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);//ũ�� ��ŭ�� �� ��Ʈ�� ���� ����
	_backBufferInfo->hOBit = (HBITMAP)SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hBit);
	_backBufferInfo->width = width;
	_backBufferInfo->height = height;

	if (_backBufferInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void backBuffer::release(void)
{
	//�̹��� ������ �ִٸ�
	if (_backBufferInfo)
	{
		SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hOBit);
		DeleteObject(_backBufferInfo->hBit);
		DeleteDC(_backBufferInfo->hMemDC);

		SAFE_DELETE(_backBufferInfo);
	}
}

void backBuffer::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,				//����� ������ DC == backDC
			destX,							//����� ��ǥ X	  == backDC�� ������ ��ǥ
			destY,							//����� ��ǥ Y
			_backBufferInfo->width,			//����� ũ��
			_backBufferInfo->height,		//����� ũ��
			_backBufferInfo->hMemDC,		//������ DC
			0, 0,							//�����ؿ� ��ǥ
			_backBufferInfo->width,			//�����ؿ� ũ��
			_backBufferInfo->height,
			_transColor);					//�� Į��
	}
	else
	{
		//��Ʈ�� == ����ۿ� �ִ� �� �������� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, destX, destY,
			_backBufferInfo->width, _backBufferInfo->height,
			_backBufferInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
