#pragma once
#include"Object.h"

class Player:private Object
{
private:
	//�v���C���[���W�i������N�_�j
	int x, y;
	//�����u���b�N��
	int haveBlock;
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

	//�W�����v��������
	void JumpProcessing();

public:

	//�T�C�Y
	const int sizeX = 17;
	const int sizeY = 21;

	Player();
	~Player();

	//�擾�֐�
	float getX() { return x; };
	float getY() { return y; };
	int getHaveBlock() { return haveBlock; };

	//�ړ�����
	void PlayerMove(DirectInput *pDi);
	//�u���b�N�쐬
	void BlockCreate();
	//�u���b�N�j��
	void BlockBreakDown();
	//��������
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

//�W�����v����
void Player::JumpProcessing()
{
	float jumpSpeedPrev = jumpNowSpeed; //�ω���m�邽�߂ɑ��
}

//�u���b�N�쐬
void Player::BlockCreate()
{

}

//�u���b�N�j��
void Player::BlockBreakDown()
{

}

//��������
void Player::FallingProcess()
{
	//�t���O�������Ă��鎞���������s
	if (flagJump == true) { JumpProcessing(); }
	//�d�͏���
	jumpNowSpeed += charGravity;

	//�����蔻��
	//�����Ƒ̂Ŕ���
	if (mapData[(int)((y + sizeY) % objectSize)][(int)(x % objectSize)] != 0
	 || mapData[(int)((y + sizeY) % 32)][(int)((x + sizeX) % 32)] != 0
		)
	{
		y = (float)(y % 32 * 32.0f - 0.1f);
	}

}