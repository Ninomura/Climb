#pragma once
#include"Object.h"
#include "DirectInput.h"
#include"Enemy.h"

class Player:public Object
{
private:
	//プレイヤー座標（左上を起点）
	//実数値
	float x, y;
	float posX,posY;
	//所持ブロック数
	int haveBlock;

	//サイズ
	const float sizeX = 22.5f;
	const float sizeY = 34.5f;
	//移動距離
	const float movingDistance = 4.0f;
	//ジャンプ力
	const float jumpStartSpeed = -9.0f;
	//キャラの重力
	const float charGravity = 0.5;
	//落下速度
	float jumpNowSpeed;
	bool goalFlag;
	//重力フラグフラグ（ジャンプフラグ）
	bool gravityFlag;
	//マウスフラグ
	bool Mouseflag;
	//当たり判定（重力処理）
	void FallingProcessing(Object *pObject, Enemy *pEnemy);
public:

	Player() {};
	~Player();

	//取得関数
	float getPosX() { return posX = x; };
	float getPosY() { return posY; };
	float getSizeX() { return sizeX; };
	float getSizeY() { return sizeY; };
	bool getGoalFlag() { return goalFlag; };
	int getHaveBlock() { return haveBlock; };

	//プレイヤー生成
	void PlayerCreate() 
	{ 
		y = 300.0f; x = WindowWidthSize / 2.0f + 100.0f;
		posX = x; posY = y;
	};
	//行動処理
	void PlayerMove(DirectInput *pDi, Texture *imgPlayer, Object *pObject, Enemy *pEnemy);
	//ブロック作成
	void BlockCreate(Object *pObject);
	//ブロック破壊
	void BlockBreakDown(Object*pObject);

};

Player::~Player()
{
	haveBlock = 0;
	goalFlag = false;
	gravityFlag = false;
	Mouseflag = false;
	jumpNowSpeed = 0.0f;
}

//行動処理
void Player::PlayerMove(DirectInput *pDi, Texture *imgPlayer, Object *pObject, Enemy *pEnemy)
{
	//左右移動
	if (pDi->KeyState(DIK_D)
		|| pDi->KeyState(DIK_RIGHT))
	{
		x += movingDistance;
		imgPlayer->SetNum(0, 0);
	}
	else if (pDi->KeyState(DIK_A)
		|| pDi->KeyState(DIK_LEFT))
	{
		x -= movingDistance;
		imgPlayer->SetNum(1, 0);
	}
	else
	{
		imgPlayer->SetNum(2, 0);
	}

	//ジャンプ
	if ((pDi->KeyJustPressed(DIK_W)
		|| pDi->KeyJustPressed(DIK_UP)
			|| pDi->KeyJustPressed(DIK_SPACE))
		&& gravityFlag == false)
	{
		gravityFlag = !gravityFlag;
		jumpNowSpeed = jumpStartSpeed;
	}

	////左マウスクリック時
	//if (pDi->MouseButtonJustPressed(0)
	//	&& gravityFlag == false)
	//{
	//	BlockBreakDown(pObject);
	//}
	////右クリック時
	//else if (pDi->MouseButtonJustPressed(1)
	//	&& gravityFlag == false
	//	&& haveBlock > 0)
	//{
	//	BlockCreate(pObject);
	//}

	FallingProcessing(pObject, pEnemy);
}

//ブロック作成
void Player::BlockCreate(Object *pObject)
{
	//if (pObject->mapData[(int)((y + sizeY/2.0f) / objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)].objectT == objectNull
	//	&&pObject->mapData[(int)((y + sizeY / 2.0f) / objectSize)+1][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)].objectT != objectNull)
	//{
	//	pObject->mapData[(int)((y + sizeY / 2.0f) / objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)].objectT = standard;
	//	y = posY + (pObject->setPosY*objectSize);
	//	y = (float)((int)((y + sizeY / 2.0f) / objectSize)*objectSize - sizeY);
	//	posY = y - (pObject->setPosY*objectSize);
	//	haveBlock--;
	//}
}

//ブロック破壊
void Player::BlockBreakDown(Object *pObject)
{
	//if (pObject->mapData[(int)((y + sizeY) / objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)].objectT == fixed)
	//{
	//	pObject->mapData[(int)((y + sizeY) / objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)].objectT = objectNull;
	//	haveBlock++;
	//}
}

//当たり判定（重力処理）
void Player::FallingProcessing(Object *pObject, Enemy *pEnemy)
{
	y = posY + (pObject->setPosY*objectSize);

	//重力処理
	if (gravityFlag == true)
	{
		jumpNowSpeed += charGravity;
		//すり抜け防止
		if (jumpNowSpeed > objectSize) { jumpNowSpeed = objectSize - 1.0f; }
		y += jumpNowSpeed;
	}

	gravityFlag = true;

	posY = y - (pObject->setPosY*objectSize);

	//マップ内のみ配列処理
	if ((posY >= 0.0f && posY + sizeY < (float)WindowHeightSize - jumpNowSpeed) && (posX >= 0.0f && posX < (float)WindowWidthSize))
	{
		//体(右)で判定
		if (pObject->mapData[(int)(y / objectSize)][(int)((x + sizeX) / objectSize)].objectT == goal
			|| pObject->mapData[(int)((y + sizeY - 0.1f) / objectSize)][(int)((x + sizeX) / objectSize)].objectT == goal)
		{
			goalFlag = !goalFlag;
		}
		//体(左)で判定
		else if (pObject->mapData[(int)(y / objectSize)][(int)((x) / objectSize)].objectT == goal
			|| pObject->mapData[(int)((y + sizeY - 0.1f) / objectSize)][(int)((x) / objectSize)].objectT == goal)
		{
			goalFlag = !goalFlag;
		}

		//当たり判定
		//足元と体で判定
		if ((pObject->mapData[(int)((y + sizeY) / objectSize)][(int)((x + movingDistance + pEnemy->movingDistance) / objectSize)].objectT != objectNull
			|| pObject->mapData[(int)((y + sizeY) / objectSize)][(int)((x + sizeX - movingDistance - pEnemy->movingDistance) / objectSize)].objectT != objectNull)
			&& jumpNowSpeed >= 0.0f
			)
		{
			y = (float)((int)((y + sizeY) / objectSize)*objectSize - sizeY);
			//フラグリセット
			gravityFlag = !gravityFlag;
			jumpNowSpeed = 0.0f;
		}

		//頭と体で判定
		if ((pObject->mapData[(int)(y / objectSize)][(int)((x + movingDistance + pEnemy->movingDistance) / objectSize)].objectT != objectNull
			|| pObject->mapData[(int)(y / objectSize)][(int)((x + sizeX - movingDistance - pEnemy->movingDistance) / objectSize)].objectT != objectNull)
			&& jumpNowSpeed < 0.0f
			)
		{
			y = (float)((int)(y / objectSize)*objectSize + sizeY);
			jumpNowSpeed = 0.0f;
		}
		//体(右)で判定
		if (pObject->mapData[(int)(y / objectSize)][(int)((x + sizeX) / objectSize)].objectT != objectNull
			|| pObject->mapData[(int)((y + sizeY - 0.1f) / objectSize)][(int)((x + sizeX) / objectSize)].objectT != objectNull)
		{
			x = (float)((int)((x + sizeX + movingDistance) / objectSize)*objectSize - sizeX - 0.1f);
		}
		//体(左)で判定
		else if (pObject->mapData[(int)(y / objectSize)][(int)((x) / objectSize)].objectT != objectNull
			|| pObject->mapData[(int)((y + sizeY - 0.1f) / objectSize)][(int)((x) / objectSize)].objectT != objectNull)
		{
			x = (float)((int)(((x - movingDistance) / objectSize) + 1.0f)*objectSize);
		}

		//敵との当たり判定
		for (int num = 0; num < pEnemy->getEnemyNum(); num++)
		{
			//足元と体で判定
			for (float processY = y + sizeY - jumpNowSpeed; processY < y + sizeY; processY += 0.1)
			{
				if ((((processY >= pEnemy->enemyData[num].y
					&&processY <= pEnemy->enemyData[num].y + 1.0f)
					|| (y + sizeY >= pEnemy->enemyData[num].y
						&&y + sizeY <= pEnemy->enemyData[num].y + 1.0f))
					&& (x + movingDistance < pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX
						&& x + sizeX - movingDistance> pEnemy->enemyData[num].x))
					&& jumpNowSpeed >= 0.0f
					)
				{
					y = (float)(pEnemy->enemyData[num].y - sizeY);

					//フラグリセット
					if (gravityFlag != false)
					{
						gravityFlag = !gravityFlag;
					}
					jumpNowSpeed = 0.0f;
					break;
				}
			}

			//体(右)で判定
			if ((x + sizeX >= pEnemy->enemyData[num].x
				&&x + sizeX <= pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX / 2.0f)
				&& ((y >= pEnemy->enemyData[num].y && y <= pEnemy->enemyData[num].y + pEnemy->enemyData[num].sizeY)
					|| (y + sizeY - 1.0f >= pEnemy->enemyData[num].y&& y + sizeY - 1.0f <= pEnemy->enemyData[num].y + pEnemy->enemyData[num].sizeY)))
			{
				x = (float)(pEnemy->enemyData[num].x - sizeX - pEnemy->movingDistance);

				//敵と壁に挟まれた時
				if ((pObject->mapData[(int)(y / objectSize)][(int)(x / objectSize)].objectT != objectNull
					|| pObject->mapData[(int)((y + sizeY - 1.0f) / objectSize)][(int)(x / objectSize)].objectT != objectNull)
					&& pEnemy->enemyData[num].returnFlag == true)
				{
					x = (float)((int)(((x - movingDistance) / objectSize) + 1.0f)*objectSize);
					pEnemy->enemyData[num].returnFlag = !pEnemy->enemyData[num].returnFlag;

				}
				//敵と敵に挟まれた時
				for (int num2 = 0; num2 < pEnemy->getEnemyNum(); num2++)
				{
					if (num != num2)
					{
						if ((x <= pEnemy->enemyData[num2].x + pEnemy->enemyData[num2].sizeX
							&&x >= pEnemy->enemyData[num2].x + pEnemy->enemyData[num2].sizeX / 2.0f)
							&& ((y >= pEnemy->enemyData[num2].y&& y <= pEnemy->enemyData[num2].y + pEnemy->enemyData[num2].sizeY)
								|| (y + sizeY - 1.0f >= pEnemy->enemyData[num2].y&& y + sizeY - 1.0f <= pEnemy->enemyData[num2].y + pEnemy->enemyData[num2].sizeY)))
						{
							pEnemy->enemyData[num].returnFlag = !pEnemy->enemyData[num].returnFlag;
							pEnemy->enemyData[num2].returnFlag = !pEnemy->enemyData[num2].returnFlag;

							if (pEnemy->enemyData[num].returnFlag == false)
							{
								pEnemy->enemyData[num].x += pEnemy->movingDistance;
							}
							else
							{
								pEnemy->enemyData[num].x -= pEnemy->movingDistance;
							}

							if (pEnemy->enemyData[num2].returnFlag == false)
							{
								pEnemy->enemyData[num2].x += pEnemy->movingDistance;
							}
							else
							{
								pEnemy->enemyData[num2].x -= pEnemy->movingDistance;
							}

							break;
						}
					}
				}
			}
			//体(左)で判定
			else if ((x <= pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX
				&&x >= pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX / 2.0f)
				&& ((y >= pEnemy->enemyData[num].y&& y <= pEnemy->enemyData[num].y + pEnemy->enemyData[num].sizeY)
					|| (y + sizeY - 1.0f >= pEnemy->enemyData[num].y&& y + sizeY - 1.0f <= pEnemy->enemyData[num].y + pEnemy->enemyData[num].sizeY)))
			{
				x = (float)(pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX + pEnemy->movingDistance);

				//体(右)で判定
				if ((pObject->mapData[(int)(y / objectSize)][(int)((x + sizeX) / objectSize)].objectT != objectNull
					|| pObject->mapData[(int)((y + sizeY - 1.0f) / objectSize)][(int)((x + sizeX) / objectSize)].objectT != objectNull)
					&& pEnemy->enemyData[num].returnFlag == false)
				{
					x = (float)((int)((x + sizeX + movingDistance) / objectSize)*objectSize - sizeX - 0.1f);
					pEnemy->enemyData[num].returnFlag = !pEnemy->enemyData[num].returnFlag;
				}

				for (int num2 = 0; num2 < pEnemy->getEnemyNum(); num2++)
				{
					if (num != num2)
					{
						if ((x + sizeX >= pEnemy->enemyData[num2].x
							&&x + sizeX <= pEnemy->enemyData[num2].x + pEnemy->enemyData[num2].sizeX / 2.0f)
							&& ((y >= pEnemy->enemyData[num2].y&& y <= pEnemy->enemyData[num2].y + pEnemy->enemyData[num2].sizeY)
								|| (y + sizeY - 1.0f >= pEnemy->enemyData[num2].y&& y + sizeY - 1.0f <= pEnemy->enemyData[num2].y + pEnemy->enemyData[num2].sizeY)))
						{
							pEnemy->enemyData[num].returnFlag = !pEnemy->enemyData[num].returnFlag;
							pEnemy->enemyData[num2].returnFlag = !pEnemy->enemyData[num2].returnFlag;

							if (pEnemy->enemyData[num].returnFlag == false)
							{
								pEnemy->enemyData[num].x += pEnemy->movingDistance;
							}
							else
							{
								pEnemy->enemyData[num].x -= pEnemy->movingDistance;
							}

							if (pEnemy->enemyData[num2].returnFlag == false)
							{
								pEnemy->enemyData[num2].x += pEnemy->movingDistance;
							}
							else
							{
								pEnemy->enemyData[num2].x -= pEnemy->movingDistance;
							}

							break;
						}
					}
				}
			}

			for (float processY = y + sizeY - jumpNowSpeed; processY <= y + sizeY; processY += 0.1)
			{
				if ((((processY >= pEnemy->enemyData[num].y && processY <= pEnemy->enemyData[num].y + 1.0f)
					|| (y + sizeY >= pEnemy->enemyData[num].y && y + sizeY <= pEnemy->enemyData[num].y + 1.0f))
					&& (x + movingDistance < pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX
						&& x + sizeX - movingDistance> pEnemy->enemyData[num].x))
					&& jumpNowSpeed >= 0.0f
					)
				{
					y = (float)(pEnemy->enemyData[num].y - sizeY);

					//フラグリセット
					if (gravityFlag != false)
					{
						gravityFlag = !gravityFlag;
					}
					jumpNowSpeed = 0.0f;
					break;
				}
			}

			if (((y + sizeY >= pEnemy->enemyData[num].y
				&&y + sizeY <= pEnemy->enemyData[num].y + pEnemy->enemyData[num].sizeY)
				&& (x + movingDistance < pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX
					&& x + sizeX - movingDistance> pEnemy->enemyData[num].x))
				&& jumpNowSpeed >= 0.0f)
			{
				if (pEnemy->enemyData[num].returnFlag == false) { x += pEnemy->movingDistance; }
				else { x -= pEnemy->movingDistance; }
			}
		}

		//体(右)で判定
		if (pObject->mapData[(int)(y / objectSize)][(int)((x + sizeX) / objectSize)].objectT != objectNull
			|| pObject->mapData[(int)((y + sizeY - 0.1f) / objectSize)][(int)((x + sizeX) / objectSize)].objectT != objectNull)
		{
			x = (float)((int)((x + sizeX + movingDistance) / objectSize)*objectSize - sizeX - 0.1f);
		}
		//体(左)で判定
		else if (pObject->mapData[(int)(y / objectSize)][(int)((x) / objectSize)].objectT != objectNull
			|| pObject->mapData[(int)((y + sizeY - 0.1f) / objectSize)][(int)((x) / objectSize)].objectT != objectNull)
		{
			x = (float)((int)(((x - movingDistance) / objectSize) + 1.0f)*objectSize);
		}

		posY = y - (pObject->setPosY*objectSize);

		//上下スクロール
		if (posY <= (9 * (objectSize))
			&& jumpNowSpeed <= 0)
		{
			if (pObject->setPosY > 0) { pObject->setPosY--; }
		}
		else if (posY > 11 * (objectSize) && jumpNowSpeed > 0)
		{
			if (pObject->setPosY < pObject->mapSizeY - pObject->setMaxPosY) { pObject->setPosY++; }
		}
		posY = y - (pObject->setPosY*objectSize);
	}
}