#pragma once
#include"Object.h"

class Enemy:public Object
{
private:
	//�G��
	int enemyNum;

	float enemySizeX[3]{ 40.0f ,40.0f,0.0f };
	float enemySizeY[3]{ 38.0f ,76.0f,0.0f };

	//�L�����̏d��
	const float enemyGravity = 0.48f;
	//�������x
	float jumpNowSpeed;
	//�d�̓t���O�t���O�i�W�����v�t���O�j
	bool gravityFlag;

	void FallingProcessing(Object *object, int num);
public:

	//�ړ�����
	const float movingDistance = 1.5f;

	typedef struct
	{
		float x, y, sizeX, sizeY, posX, posY;
		int hp;
		bool returnFlag;
		enemyType type;
	} EnemyData;

	//�G�l�~�[���
	vector<EnemyData> enemyData;

	Enemy();
	~Enemy();

	//�擾�֐�
	float getEnemyNum() { return enemyNum; };
	//�K����
	void CreateEnemy(Object *object);
	//�s������
	void MoveEnemy(Object *object);
};

Enemy::Enemy()
{
	enemyNum = 0;
}

Enemy::~Enemy()
{
	enemyData.~vector();
}

void Enemy::CreateEnemy(Object *object)
{
	//�G�̌����擾
	for (int y = 0; y < object->mapSizeY; y++)
	{
		for (int x = 0; x < object->mapSizeX; x++)
		{
			if (object->mapData[y][x].enemyT != enemyNull) { enemyNum++; }
		}
	}
	
	enemyData.resize(enemyNum);
	int num = 0;

	for (int y = 0; y < object->mapSizeY; y++)
	{
		for (int x = 0; x < object->mapSizeX; x++)
		{
			if (object->mapData[y][x].enemyT != enemyNull)
			{
				switch (object->mapData[y][x].enemyT)
				{
				case eins:
					enemyData[num].sizeX = enemySizeX[0];
					enemyData[num].sizeY = enemySizeY[0];
					break;
				case zwei:
					enemyData[num].sizeX = enemySizeX[1];
					enemyData[num].sizeY = enemySizeY[1];
					break;
				case drei:
					enemyData[num].sizeX = enemySizeX[2];
					enemyData[num].sizeY = enemySizeY[2];
					break;
				}
				enemyData[num].x = x*objectSize + enemyData[num].sizeX / 2.0f;
				enemyData[num].y = (y + 1)*objectSize - enemyData[num].sizeY;

				enemyData[num].type = object->mapData[y][x].enemyT;
				enemyData[num].posY = enemyData[num].y - (object->setPosY*objectSize);
				enemyData[num].posX = enemyData[num].x;
				enemyData[num].returnFlag = false;
				enemyData[num].hp = 1;
				object->mapData[y][x].enemyT = enemyNull;
				num++;
			}
		}
	}
}

void Enemy::MoveEnemy(Object *object)
{
	for (int num = 0; num < enemyNum; num++)
	{
		if (enemyData[num].returnFlag == false)
		{
			enemyData[num].x += movingDistance;
		}
		else
		{
			enemyData[num].x -= movingDistance;
		}
	}

	for (int num = 0; num < enemyNum; num++)
	{
		FallingProcessing(object, num);

		//�`��̍X�V
		enemyData[num].posY = enemyData[num].y - (object->setPosY*objectSize);
		enemyData[num].posX = enemyData[num].x;
	}
}

void Enemy::FallingProcessing(Object *pObject, int num)
{

	//�d�͏���
	if (gravityFlag == true)
	{
		jumpNowSpeed += enemyGravity;
		//���蔲���h�~
		if (jumpNowSpeed > objectSize) { jumpNowSpeed = objectSize - 1.0f; }
		enemyData[num].y += jumpNowSpeed;
	}

	gravityFlag = true;

	enemyData[num].posY = enemyData[num].y - (pObject->setPosY*objectSize);

	//�����蔻��
	//�����Ƒ̂Ŕ���
	if ((pObject->mapData[(int)((enemyData[num].y + enemyData[num].sizeY) / objectSize)][(int)((enemyData[num].x + movingDistance) / objectSize)].objectT != objectNull
		|| pObject->mapData[(int)((enemyData[num].y + enemyData[num].sizeY) / objectSize)][(int)((enemyData[num].x + enemyData[num].sizeX - movingDistance) / objectSize)].objectT != objectNull)
		&& jumpNowSpeed >= 0.0f
		)
	{
		enemyData[num].y = (float)((int)((enemyData[num].y + enemyData[num].sizeY) / objectSize)*objectSize - enemyData[num].sizeY);
		//�t���O���Z�b�g
		gravityFlag = false;
		jumpNowSpeed = 0.0f;
	}
	else
	{
		enemyData[num].y = (float)((int)((enemyData[num].y + enemyData[num].sizeY) / objectSize)*objectSize - enemyData[num].sizeY);

		//������������Έ����Ԃ�����
		if (enemyData[num].returnFlag == false)
		{
			enemyData[num].returnFlag = true;
			enemyData[num].x -= movingDistance;
		}
		else
		{
			enemyData[num].returnFlag = false;
			enemyData[num].x += movingDistance;
		}
	}

	//���Ƒ̂Ŕ���
	if ((pObject->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x + movingDistance) / objectSize)].objectT != objectNull
		|| pObject->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x + enemyData[num].sizeX - movingDistance) / objectSize)].objectT != objectNull)
		&& jumpNowSpeed < 0.0f
		)
	{
		enemyData[num].y = (float)((int)(enemyData[num].y / objectSize)*objectSize + enemyData[num].sizeY);
		jumpNowSpeed = 0.0f;
	}
	//�I�u�W�F�N�g�ɓ�����Έ����Ԃ�
	//��(�E)�Ŕ���
	if (pObject->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x + enemyData[num].sizeX) / objectSize)].objectT != objectNull
		|| pObject->mapData[(int)((enemyData[num].y + enemyData[num].sizeY - 1.0f) / objectSize)][(int)((enemyData[num].x + enemyData[num].sizeX) / objectSize)].objectT != objectNull)
	{
		enemyData[num].x = (float)((int)((enemyData[num].x + enemyData[num].sizeX + movingDistance) / objectSize)*objectSize - enemyData[num].sizeX - movingDistance);
		enemyData[num].returnFlag = !enemyData[num].returnFlag;
	}
	//��(��)�Ŕ���
	else if (pObject->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x) / objectSize)].objectT != objectNull
		|| pObject->mapData[(int)((enemyData[num].y + enemyData[num].sizeY - 1.0f) / objectSize)][(int)((enemyData[num].x) / objectSize)].objectT != objectNull)
	{
		enemyData[num].x = (float)((int)(((enemyData[num].x - movingDistance) / objectSize) + 1.0f)*objectSize);
		enemyData[num].returnFlag = !enemyData[num].returnFlag;
	}

	//�G�ƓG�̔���
	for (int num2 = num + 1; num2 < enemyNum; num2++)
	{
		//��(�E)�Ŕ���
		if ((enemyData[num].x + enemyData[num].sizeX >= enemyData[num2].x&&enemyData[num].x + enemyData[num].sizeX <= enemyData[num2].x + enemyData[num2].sizeX / 2.0f)
			&& ((enemyData[num].y > enemyData[num2].y&& enemyData[num].y <= enemyData[num2].y + enemyData[num2].sizeY) || (enemyData[num].y + enemyData[num].sizeY > enemyData[num2].y&& enemyData[num].y + enemyData[num].sizeY <= enemyData[num2].y + enemyData[num2].sizeY)))
		{
			enemyData[num].x = (float)(enemyData[num2].x - enemyData[num].sizeX - movingDistance);
			enemyData[num].returnFlag = !enemyData[num].returnFlag;
			enemyData[num2].returnFlag = !enemyData[num].returnFlag;
			//��(��)�Ŕ���
			if (pObject->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x) / objectSize)].objectT != objectNull
				|| pObject->mapData[(int)((enemyData[num].y + enemyData[num].sizeY - 1.0f) / objectSize)][(int)((enemyData[num].x) / objectSize)].objectT != objectNull)
			{
				enemyData[num].x = (float)((int)(((enemyData[num].x - movingDistance) / objectSize) + 1.0f)*objectSize);
				enemyData[num].returnFlag = !enemyData[num].returnFlag;
			}

			break;
		}

		//��(��)��
		else if ((enemyData[num].x <= enemyData[num2].x + enemyData[num2].sizeX&&enemyData[num].x >= enemyData[num2].x + enemyData[num2].sizeX / 2.0f)
			&& ((enemyData[num].y > enemyData[num2].y&& enemyData[num].y <= enemyData[num2].y + enemyData[num2].sizeY) || (enemyData[num].y + enemyData[num].sizeY > enemyData[num2].y&& enemyData[num].y + enemyData[num].sizeY <= enemyData[num2].y + enemyData[num2].sizeY)))
		{
			enemyData[num].x = (float)(enemyData[num2].x + enemyData[num2].sizeX + movingDistance);
			enemyData[num].returnFlag = !enemyData[num].returnFlag;
			enemyData[num2].returnFlag = !enemyData[num].returnFlag;
			//��(�E)�Ŕ���
			if (pObject->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x + enemyData[num].sizeX) / objectSize)].objectT != objectNull
				|| pObject->mapData[(int)((enemyData[num].y + enemyData[num].sizeY - 1.0f) / objectSize)][(int)((enemyData[num].x + enemyData[num].sizeX) / objectSize)].objectT != objectNull)
			{
				enemyData[num].x = (float)((int)((enemyData[num].x + enemyData[num].sizeX + movingDistance) / objectSize)*objectSize - enemyData[num].sizeX - 0.1f);
				enemyData[num].returnFlag = !enemyData[num].returnFlag;
			}

			break;
		}
	}
}