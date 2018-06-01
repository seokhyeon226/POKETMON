#pragma once
class backBuffer
{
	typedef struct tagBackBufferInfo
	{
		DWORD	resID;         //???????????????
		HDC		hMemDC;		   //�ڵ�
		HBITMAP hBit;		   //��Ʈ���ڵ鰪
		HBITMAP hOBit;		   //��Ʈ���ڵ鰪
		float	x;
		float	y;
		int		width;
		int		height;
		BYTE	loadType;
		/*
		BYTE(unsigned char 0 ~255���� �̸� 1����Ʈ) -> WORD(BYTE�� 2�� ���̴� �� 0 ~ 65535����) -> DWORD(WORD�� 2�� ���̴� �� 4����Ʈ ����)
		*/

		tagBackBufferInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			loadType = NULL;
		}
	}backBuffer_INFO, *LPbackBuffer_INFO;

private:
	LPbackBuffer_INFO	_backBufferInfo;
	BOOL			_trans;
	COLORREF		_transColor; 
public:
	backBuffer();
	~backBuffer();

	HRESULT init(int width, int height);
	void release(void);
	void render(HDC hdc, int destX, int destY);

	inline HDC getMemDC() { return _backBufferInfo->hMemDC; }
};

