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
	void PlayerMove(DirectInput *pDi, Texture *imgPlayer, Object *object);
	//�u���b�N�쐬
	void BlockCreate(Object *object);
	//�u���b�N�j��
	void BlockBreakDown(Object*object);
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
void Player::PlayerMove(DirectInput *pDi, Texture *imgPlayer, Object *object)
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

	//�}�E�X�N���b�N��
	if (pDi->MouseButtonJustPressed(0)
		&& gravityFlag == false)
	{
		BlockBreakDown(object);
	}

	//�}�E�X�N���b�N��
	if (pDi->MouseButtonJustPressed(1)
		&& gravityFlag == false
		&& haveBlock > 0)
	{
		BlockCreate(object);
	}
}

//�u���b�N�쐬
void Player::BlockCreate(Object *object)
{
	if (object->mapData[(int)((y + sizeY/2.0f) / object->objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / object->objectSize)] == object->null)
	{
		object->mapData[(int)((y + sizeY / 2.0f) / object->objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / object->objectSize)] = object->standard;
		y = posY + (object->setPosY*object->objectSize);
		y = (float)((int)((y + sizeY / 2.0f) / object->objectSize)*object->objectSize - sizeY);
		posY = y - (object->setPosY*object->objectSize);
		haveBlock--;
	}
}

//�u���b�N�j��
void Player::BlockBreakDown(Object *object)
{
	if (object->mapData[(int)((y + sizeY) / object->objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / object->objectSize)] == object->standard)
	{
		object->mapData[(int)((y + sizeY) / object->objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / object->objectSize)] = object->null;
		haveBlock++;
	}
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

	posY = y - (object->setPosY*object->objectSize);

	//�}�b�v���̂ݔz�񏈗�
	if ((posY >= 0.0f && posY + sizeY < (float)WindowHeightSize - jumpNowSpeed) && (posX >= 0.0f && posX < (float)WindowWidthSize))
	{
		//�����蔻��
		//�����Ƒ̂Ŕ���
		if ((object->mapData[(int)((y + sizeY) / object->objectSize)][(int)((x + movingDistance) / object->objectSize)] != object->null
			|| object->mapData[(int)((y + sizeY) / object->objectSize)][(int)((x + sizeX - movingDistance) / object->objectSize)] != object->null)
			&& jumpNowSpeed >= 0.0f
			)
		{
			y = (float)((int)((y + sizeY) / object->objectSize)*object->objectSize - sizeY);
			//�t���O���Z�b�g
			gravityFlag = false;
			jumpNowSpeed = 0.0f;
		}

		//���Ƒ̂Ŕ���
		if ((object->mapData[(int)(y / object->objectSize)][(int)((x + movingDistance) / object->objectSize)] != object->null
			|| object->mapData[(int)(y / object->objectSize)][(int)((x + sizeX - movingDistance) / object->objectSize)] != object->null)
			&& jumpNowSpeed < 0.0f
			)
		{
			y = (float)((int)(y / object->objectSize)*object->objectSize + sizeY);
			jumpNowSpeed = 0.0f;
		}
		//��(�E)�Ŕ���
		if (object->mapData[(int)(y / object->objectSize)][(int)((x + sizeX + movingDistance) / object->objectSize)] != object->null
			|| object->mapData[(int)((y + sizeY - 1.0f) / object->objectSize)][(int)((x + sizeX + movingDistance) / object->objectSize)] != object->null)
		{
			x = (float)((int)((x + sizeX + movingDistance) / object->objectSize)*object->objectSize - sizeX - 0.1f);
		}
		//��(��)�Ŕ���
		else if (object->mapData[(int)(y / object->objectSize)][(int)((x - movingDistance) / object->objectSize)] != object->null
			|| object->mapData[(int)((y + sizeY - 1.0f) / object->objectSize)][(int)((x - movingDistance) / object->objectSize)] != object->null)
		{
			x = (float)((int)(((x - movingDistance) / object->objectSize) + 1.0f)*object->objectSize);
		}

		posY = y - (object->setPosY*object->objectSize);

		//�㉺�X�N���[��
		if (posY <= (9 * (object->objectSize))
			&& jumpNowSpeed <= 0)
		{
			if (object->setPosY > 0)
			{
				object->setPosY--;
			}
		}
		else if (posY > 11 * (object->objectSize)
			&& jumpNowSpeed > 0)
		{
			if (object->setPosY < object->mapSizeY - object->setMaxPosY)
			{
				object->setPosY++;
			}
		}

		posY = y - (object->setPosY*object->objectSize);
	}
}