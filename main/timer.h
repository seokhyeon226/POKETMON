#pragma once
class timer
{
private:
	bool _isHardware;			//�ϵ��� ������ ����
	float _timeScale;           //CPU �� ��ȣ�� ������ �޾������� �ð���(�󸶸�ŭ �ɷȴ���)
	float _timeElapsed;         //�ð��帧 -> tickCount�� ��Ī�� ���� �и������� 0.001fdklasjfdla ��
	/*
	__int64 = 64��Ʈ ����(�޸�8����Ʈ)�̸� long long���� ǥ���� �� �ִ�.
	-9223372036854775808 ~ 9223372036854775807

	unsigned long = �������̸� 4����Ʈ�̸� 0 ~ 4,294,967,295ǥ���Ҽ� �ִ�.
	*/
	__int64 _curTime;              //���� ��ȣ(?)�� ������ ��
	__int64 _lastTime;             //CPU�� ��ȣ�� �������� ���������� �޾����� ���� ��
	__int64 _periodFrequency;      //CPU �����ӵ�

	unsigned long _frameRate;      //�����Ӽӵ�
	unsigned long _FPSframeCount;  //������ī����

	float _FPSTimeElapsed;      //�����ӽð��帧 -> �и�����
	float _worldTime;           //�����ϵ� �� ����ð�

public:
	timer();
	~timer();

	HRESULT init(void);
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;
	/*
	const�� ���̱� �Ǹ� (������ �Ұ�����)������ ������ �б� ���� �Լ��� �ȴ�.
	���������� �����Ͽ� ���� ������ ������ �ִ�.
	*/
	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }

};


