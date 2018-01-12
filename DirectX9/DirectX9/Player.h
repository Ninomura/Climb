#pragma once
#include"ExternGV.h"
#include"Object.h"
#include "DirectInput.h"

class Player:private Object
{
private:
	//�����u���b�N��
	int haveBlock;

public:
	//�v���C���[���W�i������N�_�j
	int x, y;
	//�T�C�Y
	const int sizeX = 17;
	const int sizeY = 21;

	//�ړ�����
	const float movingDistance = 2.0f;
	//�W�����v��
	const float jumpStartSpeed = -6.0f;

	//�L�����̏d��
	const float charGravity = 0.25f;
	//�������x
	float jumpNowSpeed;
	//�W�����v�t���O
	bool flagJump;

	Player();
	~Player();

	//�擾�֐�
	float getX() { return x; };
	float getY() { return y; };
	float getSizeX() { return sizeX; };
	float getSizeY() { return sizeY; };
	int getHaveBlock() { return haveBlock; };

	//�v���C���[����
	void PlayerCreate() { y = WindowHeightSize / 2.0f; x = WindowWidthSize / 2.0f; };
	//�ړ�����
	void PlayerMove(DirectInput *pDi);
	//�u���b�N�쐬
	void BlockCreate();
	//�u���b�N�j��
	void BlockBreakDown();

	//�W�����v��������
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

//�u���b�N�쐬
void Player::BlockCreate()
{

}

//�u���b�N�j��
void Player::BlockBreakDown()
{

}

//���菈���i�d�͏����j
void Player::FallingProcessing()
{
	//�t���O�������Ă��鎞���������s
	if (flagJump == true) { JumpProcessing(); }

	//�d�͏���
	jumpNowSpeed += charGravity;
	//���蔲���h�~
	if (jumpNowSpeed > (float)objectSize) { jumpNowSpeed = objectSize - 1.0f; }

	//�����蔻��
	//�����Ƒ̂Ŕ���
	if ((mapData[(int)((y + sizeY) % objectSize)][(int)(x % objectSize)] != 0
		|| mapData[(int)((y + sizeY) % objectSize)][(int)((x + sizeX) % objectSize)] != 0)
		&& jumpNowSpeed <= 0.0f
		)
	{
		y = (float)(y % objectSize * (float)objectSize - 0.1f);
		//�t���O���Z�b�g
		flagJump = false;
		jumpNowSpeed = 0.0f;
	}
	//���Ƒ̂Ŕ���
	else if (mapData[(int)(y % objectSize)][(int)(x % objectSize)] != 0
		|| mapData[(int)(y % objectSize)][(int)((x + sizeX) % objectSize)] != 0
		)
	{
		y = (float)(y % objectSize * (float)objectSize + (float)objectSize + 0.1f);
	}
	//��(�E)�Ŕ���
	else if (mapData[(int)(y % objectSize)][(int)((x + sizeX) % objectSize)] != 0
		|| mapData[(int)((y + sizeY) % objectSize)][(int)((x + sizeX) % objectSize)] != 0
		)
	{
		x = (float)(x % objectSize * (float)objectSize - 0.1f);
	}
	//��(��)�Ŕ���
	else if (mapData[(int)(y % objectSize)][(int)(x % objectSize)] != 0
		|| mapData[(int)((y + sizeY) % objectSize)][(int)(x % objectSize)] != 0
		)
	{
		x = (float)(x % objectSize * (float)objectSize + (float)objectSize + 0.1f);
	}
}