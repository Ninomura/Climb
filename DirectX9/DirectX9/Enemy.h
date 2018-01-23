#pragma once
#include"Object.h"

class Enemy:public Object
{
private:
	//�G��
	int enemyNum;
	float enemySizeX = 40.0f;
	float enemySizeY = 38.0f;

	//�ړ�����
	const float movingDistance = 2.0f;
	//�L�����̏d��
	const float enemyGravity = 0.48;
	//�������x
	float jumpNowSpeed;
	//�d�̓t���O�t���O�i�W�����v�t���O�j
	bool gravityFlag;

	void FallingProcessing(Object *object, int num);
public:

	typedef struct
	{
		float x, y, posX, posY;
		int hp;
		bool returnFlag;
	} EnemyData;

	//�G�l�~�[���
	vector<EnemyData> enemyData;

	Enemy();
	~Enemy();

	//�擾�֐�
	float getEnemyNum() { return enemyNum; };
	float getEnemySizeX() { return enemySizeX; };
	float getEnemySizeY() { return enemySizeY; };

	void CreateEnemy(Object *object);
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
	for (int y = 0; y < object->mapSizeY; y++)
	{
		for (int x = 0; x < object->mapSizeX; x++)
		{
			if (object->mapData[y][x] == enemy) { enemyNum++; }
		}
	}

	enemyData.resize(enemyNum);
	int num = 0;

	for (int y = 0; y < object->mapSizeY; y++)
	{
		for (int x = 0; x < object->mapSizeX; x++)
		{
			if (object->mapData[y][x] == enemy)
			{
				object->mapData[y][x] = null;
				enemyData[num].y = (y + 1)*objectSize - enemySizeY;
				enemyData[num].x = x*objectSize + enemySizeX / 2.0f;
				enemyData[num].posY = enemyData[num].y - (object->setPosY*objectSize);
				enemyData[num].posX = enemyData[num].x;
				enemyData[num].returnFlag = false;
				enemyData[num].hp = 1;
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

		FallingProcessing(object, num);

		//�`��̍X�V
		enemyData[num].posY = enemyData[num].y - (object->setPosY*objectSize);
		enemyData[num].posX = enemyData[num].x;
	}
}

void Enemy::FallingProcessing(Object *object,int num)
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

	enemyData[num].posY = enemyData[num].y - (object->setPosY*objectSize);

	//�}�b�v���̂ݔz�񏈗�
	if ((enemyData[num].posY >= 0.0f && enemyData[num].posY + enemySizeY < (float)WindowHeightSize - jumpNowSpeed) && (enemyData[num].posX >= 0.0f && enemyData[num].posX < (float)WindowWidthSize))
	{
		//�����蔻��
		//�����Ƒ̂Ŕ���
		if ((object->mapData[(int)((enemyData[num].y + enemySizeY) / objectSize)][(int)((enemyData[num].x + movingDistance) / objectSize)] != null
			|| object->mapData[(int)((enemyData[num].y + enemySizeY) / objectSize)][(int)((enemyData[num].x + enemySizeX - movingDistance) / objectSize)] != null)
			&& jumpNowSpeed >= 0.0f
			)
		{
			enemyData[num].y = (float)((int)((enemyData[num].y + enemySizeY) / objectSize)*objectSize - enemySizeY);
			//�t���O���Z�b�g
			gravityFlag = false;
			jumpNowSpeed = 0.0f;
		}
		else
		{
			enemyData[num].y = (float)((int)((enemyData[num].y + enemySizeY) / objectSize)*objectSize - enemySizeY);

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
		if ((object->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x + movingDistance) / objectSize)] != null
			|| object->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x + enemySizeX - movingDistance) / objectSize)] != null)
			&& jumpNowSpeed < 0.0f
			)
		{
			enemyData[num].y = (float)((int)(enemyData[num].y / objectSize)*objectSize + enemySizeY);
			jumpNowSpeed = 0.0f;
		}
		//��(�E)�Ŕ���
		if (object->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x + enemySizeX + movingDistance) / objectSize)] != null
			|| object->mapData[(int)((enemyData[num].y + enemySizeY - 1.0f) / objectSize)][(int)((enemyData[num].x + enemySizeX + movingDistance) / objectSize)] != null)
		{
			enemyData[num].x = (float)((int)((enemyData[num].x + enemySizeX + movingDistance) / objectSize)*objectSize - enemySizeX - 0.1f);
			enemyData[num].returnFlag = true;
		}
		//��(��)�Ŕ���
		else if (object->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x - movingDistance) / objectSize)] != null
			|| object->mapData[(int)((enemyData[num].y + enemySizeY - 1.0f) / objectSize)][(int)((enemyData[num].x - movingDistance) / objectSize)] != null)
		{
			enemyData[num].x = (float)((int)(((enemyData[num].x - movingDistance) / objectSize) + 1.0f)*objectSize);
			enemyData[num].returnFlag = false;
		}

	}
}