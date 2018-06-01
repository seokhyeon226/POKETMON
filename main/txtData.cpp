#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{

}

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{

}


//Save
void txtData::txtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;

	char str[128];
	DWORD write;
	//strncpy_s = ���ڿ��� �����ϴ� �Լ�(strncpy�ʹ� ������ �ٸ� ���̴� �ڿ� NULL���� �ֳİ� �ٸ�)
	//���͸� �����ϴ�.
	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);
	//                               �����ȯ                     �׻���ο�����   �Ӽ�����NO
	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//strlen �� ���ڿ� ���� �Լ��� ���� ����ȴ�
	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

char* txtData::vectorArrayCombine(vector<string> vArray)
{
	//���۸� ���ص��� ����, �Ӽ��� ������ �Ӽ��� ���¸�ŭ
	//���� �� �ְ� ���ĺ��ô� ^_^*

	//���۴� �켱 128�� �Ѵ�. ���߿� �ÿ��� ����
	char str[128];

	ZeroMemory(str, sizeof(str));
	//X Axis, Y Axis, CurrentHP, MaxHP
	//100, 100, 100, 100
	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 128, vArray[i].c_str(), 126);
		if (i + 1 < vArray.size()) strcat(str, ",");
	}

	return str;
}


//Load
vector<string> txtData::txtLoad(const char* loadFileName)
{
	HANDLE file;

	char str[128];
	DWORD read;
	//                 �����̸�      ���� ��ȯ  ������� ,���(�ڽ�)���� ���� �ѱ���ΰ�, �׻� ���ο� ������ �����, ��� �Ӽ�(�б� ����, ����, �ü������)�� �������� �ʴ´�, ������ ���ø� ������ ��ȿ�� �ڵ鿡 �Ӽ��� �ִ� BOOL��
	file = CreateFile(loadFileName, GENERIC_READ, FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//DWORD = 32��Ʈ 64��Ʈ ������� �������Ͽ� 1���� ��Ÿ���� ��
	//��������� �ڵ�, �����Ͱ� ����ִ� ���۾����� �ϴ� ����Ʈ��, ������ �ϴ� ����Ʈ ���� �����ϱ�����DWORD������ ������, �񵿱�������� �Ҷ� ��� BOOL��
	ReadFile(file, str, 128, &read, NULL);

	//������ �ڵ��� �ݴ´�.(����, ���μ���, ���� ��) WIN32ȯ�濡�� �ڵ�� ǥ���Ǵ� ��� ���� �ݴ´�.
	//�׷��� ������, �� �귯���� GDI������Ʈ �� ���� �� ����.
	CloseHandle(file);

	return charArraySeparation(str);
}

//���� ������ ���� �߰��߰� ������ �ִ� ��ŭ ������
vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	const char* separator = ",";
	char* token;

	token = strtok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}

