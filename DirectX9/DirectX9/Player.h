#pragma once
#include"ExternGV.h"
#include"Object.h"
#include "DirectInput.h"

class Player:private Object
{
private:
	//所持ブロック数
	int haveBlock;

public:
	//プレイヤー座標（左上を起点）
	int x, y;
	//サイズ
	const int sizeX = 17;
	const int sizeY = 21;

	//移動距離
	const float movingDistance = 2.0f;
	//ジャンプ力
	const float jumpStartSpeed = -6.0f;

	//キャラの重力
	const float charGravity = 0.25f;
	//落下速度
	float jumpNowSpeed;
	//ジャンプフラグ
	bool flagJump;

	Player();
	~Player();

	//取得関数
	float getX() { return x; };
	float getY() { return y; };
	float getSizeX() { return sizeX; };
	float getSizeY() { return sizeY; };
	int getHaveBlock() { return haveBlock; };

	//プレイヤー生成
	void PlayerCreate() { y = WindowHeightSize / 2.0f; x = WindowWidthSize / 2.0f; };
	//移動処理
	void PlayerMove(DirectInput *pDi);
	//ブロック作成
	void BlockCreate();
	//ブロック破壊
	void BlockBreakDown();

	//ジャンプ処理処理
	void JumpProcessing() { float jumpSpeedPrev = jumpNowSpeed; };

	void FallingProcessing();

};

Player::Player()
{
}

Player::~Player()
{
	haveBlock = 0;
	flagJump = false;
	jumpNowSpeed = 0.0f;
}


void Player::PlayerMove(DirectInput *pDi)
{
	if (pDi->KeyState(DIK_D))
	{
		x += movingDistance;
	}
	else if (pDi->KeyState(DIK_A))
	{
		x -= movingDistance;
	}

	if (pDi->KeyState(DIK_W) && flagJump == false)
	{
		flagJump = true;
		jumpNowSpeed = jumpStartSpeed;
	}
}

//ブロック作成
void Player::BlockCreate()
{

}

//ブロック破壊
void Player::BlockBreakDown()
{

}

//判定処理（重力処理）
void Player::FallingProcessing()
{
	//フラグが立っている時処理を実行
	if (flagJump == true) { JumpProcessing(); }

	//重力処理
	jumpNowSpeed += charGravity;
	//すり抜け防止
	if (jumpNowSpeed > (float)objectSize) { jumpNowSpeed = objectSize - 1.0f; }

	//当たり判定
	//足元と体で判定
	if ((mapData[(int)((y + sizeY) % objectSize)][(int)(x % objectSize)] != 0
		|| mapData[(int)((y + sizeY) % objectSize)][(int)((x + sizeX) % objectSize)] != 0)
		&& jumpNowSpeed <= 0.0f
		)
	{
		y = (float)(y % objectSize * (float)objectSize - 0.1f);
		//フラグリセット
		flagJump = false;
		jumpNowSpeed = 0.0f;
	}
	//頭と体で判定
	else if (mapData[(int)(y % objectSize)][(int)(x % objectSize)] != 0
		|| mapData[(int)(y % objectSize)][(int)((x + sizeX) % objectSize)] != 0
		)
	{
		y = (float)(y % objectSize * (float)objectSize + (float)objectSize + 0.1f);
	}
	//体(右)で判定
	else if (mapData[(int)(y % objectSize)][(int)((x + sizeX) % objectSize)] != 0
		|| mapData[(int)((y + sizeY) % objectSize)][(int)((x + sizeX) % objectSize)] != 0
		)
	{
		x = (float)(x % objectSize * (float)objectSize - 0.1f);
	}
	//体(左)で判定
	else if (mapData[(int)(y % objectSize)][(int)(x % objectSize)] != 0
		|| mapData[(int)((y + sizeY) % objectSize)][(int)(x % objectSize)] != 0
		)
	{
		x = (float)(x % objectSize * (float)objectSize + (float)objectSize + 0.1f);
	}
}