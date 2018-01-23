#pragma once
#include"Object.h"
#include "DirectInput.h"

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
	const float jumpStartSpeed = -8.5f;
	//キャラの重力
	const float charGravity = 0.48;
	//落下速度
	float jumpNowSpeed;
	//重力フラグフラグ（ジャンプフラグ）
	bool gravityFlag;
	//マウスフラグ
	bool Mouseflag;
public:

	Player() {};
	~Player();

	//取得関数
	float getPosX() { return posX = x; };
	float getPosY() { return posY; };
	float getSizeX() { return sizeX; };
	float getSizeY() { return sizeY; };
	int getHaveBlock() { return haveBlock; };

	//プレイヤー生成
	void PlayerCreate() 
	{ 
		y = 300.0f; x = WindowWidthSize / 2.0f + 100.0f;
		posX = x; posY = y;
	};
	//行動処理
	void PlayerMove(DirectInput *pDi, Texture *imgPlayer, Object *object);
	//ブロック作成
	void BlockCreate(Object *object);
	//ブロック破壊
	void BlockBreakDown(Object*object);
	//当たり判定（重力処理）
	void FallingProcessing(Object *object);

};

Player::~Player()
{
	haveBlock = 10;
	gravityFlag = false;
	Mouseflag = false;
	jumpNowSpeed = 0.0f;
}

//行動処理
void Player::PlayerMove(DirectInput *pDi, Texture *imgPlayer, Object *object)
{
	//左右移動
	if (pDi->KeyState(DIK_D))
	{
		x += movingDistance;
		imgPlayer->SetNum(0, 0);
	}
	else if (pDi->KeyState(DIK_A))
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
		|| (pDi->KeyJustPressed(DIK_SPACE)))
		&& gravityFlag == false)
	{
		gravityFlag = true;
		jumpNowSpeed = jumpStartSpeed;
	}

	//左マウスクリック時
	if (pDi->MouseButtonJustPressed(0)
		&& gravityFlag == false)
	{
		BlockBreakDown(object);
	}
	//右クリック時
	else if (pDi->MouseButtonJustPressed(1)
		&& gravityFlag == false
		&& haveBlock > 0)
	{
		BlockCreate(object);
	}
}

//ブロック作成
void Player::BlockCreate(Object *object)
{
	if (object->mapData[(int)((y + sizeY/2.0f) / objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)] == null
		&&object->mapData[(int)((y + sizeY / 2.0f) / objectSize)+1][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)] != null)
	{
		object->mapData[(int)((y + sizeY / 2.0f) / objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)] = standard;
		y = posY + (object->setPosY*objectSize);
		y = (float)((int)((y + sizeY / 2.0f) / objectSize)*objectSize - sizeY);
		posY = y - (object->setPosY*objectSize);
		haveBlock--;
	}
}

//ブロック破壊
void Player::BlockBreakDown(Object *object)
{
	if (object->mapData[(int)((y + sizeY) / objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)] == standard)
	{
		object->mapData[(int)((y + sizeY) / objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)] = null;
		haveBlock++;
	}
}

//当たり判定（重力処理）
void Player::FallingProcessing(Object *object)
{
	y = posY + (object->setPosY*objectSize);

	//重力処理
	if (gravityFlag == true)
	{
		jumpNowSpeed += charGravity;
		//すり抜け防止
		if (jumpNowSpeed > objectSize) { jumpNowSpeed = objectSize - 1.0f; }
		y += jumpNowSpeed;
	}

	gravityFlag = true;

	posY = y - (object->setPosY*objectSize);

	//マップ内のみ配列処理
	if ((posY >= 0.0f && posY + sizeY < (float)WindowHeightSize - jumpNowSpeed) && (posX >= 0.0f && posX < (float)WindowWidthSize))
	{
		//当たり判定
		//足元と体で判定
		if ((object->mapData[(int)((y + sizeY) / objectSize)][(int)((x + movingDistance) / objectSize)] != null
			|| object->mapData[(int)((y + sizeY) / objectSize)][(int)((x + sizeX - movingDistance) / objectSize)] != null)
			&& jumpNowSpeed >= 0.0f
			)
		{
			y = (float)((int)((y + sizeY) / objectSize)*objectSize - sizeY);
			//フラグリセット
			gravityFlag = false;
			jumpNowSpeed = 0.0f;
		}

		//頭と体で判定
		if ((object->mapData[(int)(y / objectSize)][(int)((x + movingDistance) / objectSize)] != null
			|| object->mapData[(int)(y / objectSize)][(int)((x + sizeX - movingDistance) / objectSize)] != null)
			&& jumpNowSpeed < 0.0f
			)
		{
			y = (float)((int)(y / objectSize)*objectSize + sizeY);
			jumpNowSpeed = 0.0f;
		}
		//体(右)で判定
		if (object->mapData[(int)(y / objectSize)][(int)((x + sizeX + movingDistance) / objectSize)] != null
			|| object->mapData[(int)((y + sizeY - 1.0f) / objectSize)][(int)((x + sizeX + movingDistance) / objectSize)] != null)
		{
			x = (float)((int)((x + sizeX + movingDistance) / objectSize)*objectSize - sizeX - 0.1f);
		}
		//体(左)で判定
		else if (object->mapData[(int)(y / objectSize)][(int)((x - movingDistance) / objectSize)] != null
			|| object->mapData[(int)((y + sizeY - 1.0f) / objectSize)][(int)((x - movingDistance) / objectSize)] != null)
		{
			x = (float)((int)(((x - movingDistance) / objectSize) + 1.0f)*objectSize);
		}

		posY = y - (object->setPosY*objectSize);

		//上下スクロール
		if (posY <= (9 * (objectSize))
			&& jumpNowSpeed <= 0)
		{
			if (object->setPosY > 0)
			{
				object->setPosY--;
			}
		}
		else if (posY > 11 * (objectSize)
			&& jumpNowSpeed > 0)
		{
			if (object->setPosY < object->mapSizeY - object->setMaxPosY)
			{
				object->setPosY++;
			}
		}

		posY = y - (object->setPosY*objectSize);
	}
}