#include "stdafx.h"
#include "saveLoadTest.h"


saveLoadTest::saveLoadTest()
{
}


saveLoadTest::~saveLoadTest()
{

}

void saveLoadTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) save();
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) load();
}

void saveLoadTest::save()
{
	//���� �����
	// C - FILE*
	// C++ - ifstream, ofstream
	// WIN32 - CreateFile

	HANDLE file;
	DWORD write;

	char str[128] = "���̵������� �ŵ����� ����";
	//                 �����̸�           ���� ��ȯ  ������� ���(�ڽ�)���� ���� �ѱ���ΰ�, �׻� ���ο� ������ �����, ��� �Ӽ�(�б� ����, ����, �ü������)�� �������� �ʴ´�, ������ ���ø� ������ ��ȿ�� �ڵ鿡 �Ӽ��� �ִ� BOOL��
	file = CreateFile("ĭ��Ű����.txt", GENERIC_WRITE, FALSE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//	     ��������� �ڵ�, �����Ͱ� ����ִ� ���۾����� �ϴ� ����Ʈ��, ������ �ϴ� ����Ʈ ���� �����ϱ�����DWORD������ ������, �񵿱�������� �Ҷ� ��� BOOL��
	//DWORD = 32��Ʈ 64��Ʈ ������� �������Ͽ� 1���� ��Ÿ���� ��
	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);

}

void saveLoadTest::load()
{
	HANDLE file;
	DWORD read;

	char str[128];
	//                                   �б� ��ȯ                 ������ �����ϸ� ����, ��� �Ӽ��� �������� �ʴ´�.
	file = CreateFile("ĭ��Ű����.txt", GENERIC_READ, FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);
	// MB_OK -> ȭ�鿡 Ȯ�ι�ư�� ��µǰ� �Ѵ�.(��ư�� 1���� ��� �ڵ� ��ȯ�� �Ǿ� ���� ��ȯ��ų �ʿ䰡 ����.)
	MessageBox(_hWnd, str, "�� ����ߵ���;", MB_OK);

}
