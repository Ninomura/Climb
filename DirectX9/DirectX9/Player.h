#pragma once
#include"Object.h"
#include "DirectInput.h"

class Player
{
private:
	//�v���C���[���W�i������N�_�j
	//�����l
	float x, y;
	float posX,posY;
	//�����u���b�N��
	int haveBlock;

	//�T�C�Y
	const float sizeX = 22.5f;
	const float sizeY = 34.5f;
	//�ړ�����
	const float movingDistance = 4.0f;
	//�W�����v��
	const float jumpStartSpeed = -8.5f;
	//�L�����̏d��
	const float charGravity = 0.48;
	//�������x
	float jumpNowSpeed;
	//�d�̓t���O�t���O�i�W�����v�t���O�j
	bool gravityFlag;
	//�}�E�X�t���O
	bool Mouseflag;
public:

	Player() {};
	~Player();

	//�擾�֐�
	float getPosX() { return posX = x;; };
	float getPosY() { return posY; };
	float getSizeX() { return sizeX; };
	float getSizeY() { return sizeY; };
	int getHaveBlock() { return haveBlock; };

	//�v���C���[����
	void PlayerCreate() 
	{ 
		y = 300.0f; x = WindowWidthSize / 2.0f + 100.0f;
		posX = x; posY = y;
	};
	//�s������
	void PlayerMove(DirectInput *pDi, Texture *imgPlayer);
	//�u���b�N�쐬
	void BlockCreate(Object *object);
	//�u���b�N�j��
	void BlockBreakDown(DirectInput *pDi, Object*object);
	//�����蔻��i�d�͏����j
	void FallingProcessing(Object *object);

};

Player::~Player()
{
	haveBlock = 0;
	gravityFlag = false;
	Mouseflag = false;
	jumpNowSpeed = 0.0f;
}

//�s������
void Player::PlayerMove(DirectInput *pDi, Texture *imgPlayer)
{
	//���E�ړ�
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

	//�W�����v
	if ((pDi->KeyJustPressed(DIK_W)
		|| (pDi->KeyJustPressed(DIK_SPACE)))
		&& gravityFlag == false)
	{
		gravityFlag = true;
		jumpNowSpeed = jumpStartSpeed;
	}

	if (Mouseflag == false && pDi->MouseButton(0))
	{

	}
}

//�u���b�N�쐬
void Player::BlockCreate(Object *object)
{

}

//�u���b�N�j��
void Player::BlockBreakDown(DirectInput *pDi, Object *object)
{
	//if (Mouseflag == false && pDi->MouseButton(0))
	//{
	//}
}

//�����蔻��i�d�͏����j
void Player::FallingProcessing(Object *object)
{
	y = posY + (object->setPosY*object->objectSize);

	//�d�͏���
	if (gravityFlag == true)
	{
		jumpNowSpeed += charGravity;
		//���蔲���h�~
		if (jumpNowSpeed > object->objectSize) { jumpNowSpeed = object->objectSize - 1.0f; }
		y += jumpNowSpeed;
	}

	gravityFlag = true;

	//�}�b�v���̂ݔz�񏈗�
	if (posY >= 0.0f && posY <= (float)WindowHeightSize&&posX >= 0.0f && posX <= (float)WindowWidthSize)
	{
		//�����蔻��
		//�����Ƒ̂Ŕ���
		if ((object->mapData[(int)((y + sizeY) / object->objectSize)][(int)((x + movingDistance) / object->objectSize)] != 0
			|| object->mapData[(int)((y + sizeY) / object->objectSize)][(int)((x + sizeX - movingDistance) / object->objectSize)] != 0)
			&& jumpNowSpeed >= 0.0f
			)
		{
			y = (float)((int)((y + sizeY) / object->objectSize)*object->objectSize - sizeY);
			//�t���O���Z�b�g
			gravityFlag = false;
			jumpNowSpeed = 0.0f;
		}

		//���Ƒ̂Ŕ���
		if ((object->mapData[(int)(y / object->objectSize)][(int)((x + movingDistance) / object->objectSize)] != 0
			|| object->mapData[(int)(y / object->objectSize)][(int)((x + sizeX - movingDistance) / object->objectSize)] != 0)
			&& jumpNowSpeed < 0.0f
			)
		{
			y = (float)((int)(y / object->objectSize)*object->objectSize + sizeY);
			jumpNowSpeed = 0.0f;
		}
		//��(�E)�Ŕ���
		if (object->mapData[(int)(y / object->objectSize)][(int)((x + sizeX + movingDistance) / object->objectSize)] != 0
			|| object->mapData[(int)((y + sizeY - 1.0f) / object->objectSize)][(int)((x + sizeX + movingDistance) / object->objectSize)] != 0)
		{
			x = (float)((int)((x + sizeX + movingDistance) / object->objectSize)*object->objectSize - sizeX - 0.1f);
		}
		//��(��)�Ŕ���
		else if (object->mapData[(int)(y / object->objectSize)][(int)((x - movingDistance) / object->objectSize)] != 0
			|| object->mapData[(int)((y + sizeY - 1.0f) / object->objectSize)][(int)((x - movingDistance) / object->objectSize)] != 0)
		{
			x = (float)((int)(((x - movingDistance) / object->objectSize) + 1.0f)*object->objectSize);
		}
	}

	posY = y - (object->setPosY*object->objectSize);

	//�㉺�X�N���[��
	if (posY <= (9 * (object->objectSize))
		&& gravityFlag == false)
	{
		if (object->setPosY > 0)
		{
			object->setPosY--;
		}
	}
	else if (posY > 11 * (object->objectSize)
		&& gravityFlag == false)
	{
		if (object->setPosY < object->mapSizeY - object->setMaxPosY)
		{
			object->setPosY++;
		}
	}

	posY = y - (object->setPosY*object->objectSize);
}