#include "stdafx.h"
#include "mainGame.h"

//��ü�������� �ڵ������ ���ܳ��鼭 ���ܳ� ����ε�
//�� ���� ��������� �������� CPP ������ ������ �� �ִµ�
//�������α׷��� Ư¡ �� �ڵ差�� ������ ���� ������
//init ���� cpp
//release ���� cpp
//update ���� cpp
//�浹 ���� cpp 
//������ ������ �ڵ带 ������ + ������ �����ϰ� �ϴ� ����̴�


void mainGame::collision()
{
	for (int i = 0; i < _ship->getHeptahoMissile()->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp,
				&_em->getVMinion()[j]->getRect(),
				&_ship->getHeptahoMissile()->getVBullet()[i].rc))
			{
				_em->removeMinion(j);
				_ship->getHeptahoMissile()->removeMissile(i);
				break;
			}
		}
	}
}