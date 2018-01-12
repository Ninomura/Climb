#pragma once
#include"Object.h"

class Player:private Object
{
private:
	//プレイヤー座標（左上を起点）
	int x, y;
	//所持ブロック数
	int haveBlock;
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

	//ジャンプ処理処理
	void JumpProcessing();

public:

	//サイズ
	const int sizeX = 17;
	const int sizeY = 21;

	Player();
	~Player();

	//取得関数
	float getX() { return x; };
	float getY() { return y; };
	int getHaveBlock() { return haveBlock; };

	//移動処理
	void PlayerMove(DirectInput *pDi);
	//ブロック作成
	void BlockCreate();
	//ブロック破壊
	void BlockBreakDown();
	//落下処理
	void FallingProcess();
};

Player::Player()
{
}

Player::~Player()
{
	haveBlock = 0;
	flagJump = false;
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

//ジャンプ処理
void Player::JumpProcessing()
{
	float jumpSpeedPrev = jumpNowSpeed; //変化を知るために代入
}

//ブロック作成
void Player::BlockCreate()
{

}

//ブロック破壊
void Player::BlockBreakDown()
{

}

//落下処理
void Player::FallingProcess()
{
	//フラグが立っている時処理を実行
	if (flagJump == true) { JumpProcessing(); }
	//重力処理
	jumpNowSpeed += charGravity;

	//当たり判定
	//足元と体で判定
	if (mapData[(int)((y + sizeY) % objectSize)][(int)(x % objectSize)] != 0
	 || mapData[(int)((y + sizeY) % 32)][(int)((x + sizeX) % 32)] != 0
		)
	{
		y = (float)(y % 32 * 32.0f - 0.1f);
	}

}