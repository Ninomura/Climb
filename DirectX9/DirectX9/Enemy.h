#pragma once
#include"Object.h"

class Enemy:public Object
{
private:
	//敵数
	int enemyNum;
	float enemySizeX = 40.0f;
	float enemySizeY = 38.0f;

	//移動距離
	const float movingDistance = 2.0f;
	//キャラの重力
	const float enemyGravity = 0.48;
	//落下速度
	float jumpNowSpeed;
	//重力フラグフラグ（ジャンプフラグ）
	bool gravityFlag;

	void FallingProcessing(Object *object, int num);
public:

	typedef struct
	{
		float x, y, posX, posY;
		int hp;
		bool returnFlag;
	} EnemyData;

	//エネミー情報
	vector<EnemyData> enemyData;

	Enemy();
	~Enemy();

	//取得関数
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

		//描画の更新
		enemyData[num].posY = enemyData[num].y - (object->setPosY*objectSize);
		enemyData[num].posX = enemyData[num].x;
	}
}

void Enemy::FallingProcessing(Object *object,int num)
{

	//重力処理
	if (gravityFlag == true)
	{
		jumpNowSpeed += enemyGravity;
		//すり抜け防止
		if (jumpNowSpeed > objectSize) { jumpNowSpeed = objectSize - 1.0f; }
		enemyData[num].y += jumpNowSpeed;
	}

	gravityFlag = true;

	enemyData[num].posY = enemyData[num].y - (object->setPosY*objectSize);

	//マップ内のみ配列処理
	if ((enemyData[num].posY >= 0.0f && enemyData[num].posY + enemySizeY < (float)WindowHeightSize - jumpNowSpeed) && (enemyData[num].posX >= 0.0f && enemyData[num].posX < (float)WindowWidthSize))
	{
		//当たり判定
		//足元と体で判定
		if ((object->mapData[(int)((enemyData[num].y + enemySizeY) / objectSize)][(int)((enemyData[num].x + movingDistance) / objectSize)] != null
			|| object->mapData[(int)((enemyData[num].y + enemySizeY) / objectSize)][(int)((enemyData[num].x + enemySizeX - movingDistance) / objectSize)] != null)
			&& jumpNowSpeed >= 0.0f
			)
		{
			enemyData[num].y = (float)((int)((enemyData[num].y + enemySizeY) / objectSize)*objectSize - enemySizeY);
			//フラグリセット
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

		//頭と体で判定
		if ((object->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x + movingDistance) / objectSize)] != null
			|| object->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x + enemySizeX - movingDistance) / objectSize)] != null)
			&& jumpNowSpeed < 0.0f
			)
		{
			enemyData[num].y = (float)((int)(enemyData[num].y / objectSize)*objectSize + enemySizeY);
			jumpNowSpeed = 0.0f;
		}
		//体(右)で判定
		if (object->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x + enemySizeX + movingDistance) / objectSize)] != null
			|| object->mapData[(int)((enemyData[num].y + enemySizeY - 1.0f) / objectSize)][(int)((enemyData[num].x + enemySizeX + movingDistance) / objectSize)] != null)
		{
			enemyData[num].x = (float)((int)((enemyData[num].x + enemySizeX + movingDistance) / objectSize)*objectSize - enemySizeX - 0.1f);
			enemyData[num].returnFlag = true;
		}
		//体(左)で判定
		else if (object->mapData[(int)(enemyData[num].y / objectSize)][(int)((enemyData[num].x - movingDistance) / objectSize)] != null
			|| object->mapData[(int)((enemyData[num].y + enemySizeY - 1.0f) / objectSize)][(int)((enemyData[num].x - movingDistance) / objectSize)] != null)
		{
			enemyData[num].x = (float)((int)(((enemyData[num].x - movingDistance) / objectSize) + 1.0f)*objectSize);
			enemyData[num].returnFlag = false;
		}

	}
}