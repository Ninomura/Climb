#pragma once
#include"Object.h"
#include "DirectInput.h"
#include"Enemy.h"

class Player:public Object
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
	const float jumpStartSpeed = -8.9f;
	//�L�����̏d��
	const float charGravity = 0.48;
	//�������x
	float jumpNowSpeed;
	//�d�̓t���O�t���O�i�W�����v�t���O�j
	bool gravityFlag;
	//�}�E�X�t���O
	bool Mouseflag;
	//�����蔻��i�d�͏����j
	void FallingProcessing(Object *pObject, Enemy *pEnemy);
public:

	Player() {};
	~Player();

	//�擾�֐�
	float getPosX() { return posX = x; };
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
	void PlayerMove(DirectInput *pDi, Texture *imgPlayer, Object *pObject, Enemy *pEnemy);
	//�u���b�N�쐬
	void BlockCreate(Object *pObject);
	//�u���b�N�j��
	void BlockBreakDown(Object*pObject);

};

Player::~Player()
{
	haveBlock = 0;
	gravityFlag = false;
	Mouseflag = false;
	jumpNowSpeed = 0.0f;
}

//�s������
void Player::PlayerMove(DirectInput *pDi, Texture *imgPlayer, Object *pObject, Enemy *pEnemy)
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
		gravityFlag = !gravityFlag;
		jumpNowSpeed = jumpStartSpeed;
	}

	////���}�E�X�N���b�N��
	//if (pDi->MouseButtonJustPressed(0)
	//	&& gravityFlag == false)
	//{
	//	BlockBreakDown(pObject);
	//}
	////�E�N���b�N��
	//else if (pDi->MouseButtonJustPressed(1)
	//	&& gravityFlag == false
	//	&& haveBlock > 0)
	//{
	//	BlockCreate(pObject);
	//}

	FallingProcessing(pObject, pEnemy);
}

//�u���b�N�쐬
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

//�u���b�N�j��
void Player::BlockBreakDown(Object *pObject)
{
	//if (pObject->mapData[(int)((y + sizeY) / objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)].objectT == fixed)
	//{
	//	pObject->mapData[(int)((y + sizeY) / objectSize)][(int)((x + sizeX / 2.0f - movingDistance) / objectSize)].objectT = objectNull;
	//	haveBlock++;
	//}
}

//�����蔻��i�d�͏����j
void Player::FallingProcessing(Object *pObject, Enemy *pEnemy)
{
	y = posY + (pObject->setPosY*objectSize);

	//�d�͏���
	if (gravityFlag == true)
	{
		jumpNowSpeed += charGravity;
		//���蔲���h�~
		if (jumpNowSpeed > objectSize) { jumpNowSpeed = objectSize - 1.0f; }
		y += jumpNowSpeed;
	}

	gravityFlag = true;

	posY = y - (pObject->setPosY*objectSize);

	//�}�b�v���̂ݔz�񏈗�
	if ((posY >= 0.0f && posY + sizeY < (float)WindowHeightSize - jumpNowSpeed) && (posX >= 0.0f && posX < (float)WindowWidthSize))
	{
		//�����蔻��
		//�����Ƒ̂Ŕ���
		if ((pObject->mapData[(int)((y + sizeY) / objectSize)][(int)((x + movingDistance) / objectSize)].objectT != objectNull
			|| pObject->mapData[(int)((y + sizeY) / objectSize)][(int)((x + sizeX - movingDistance) / objectSize)].objectT != objectNull)
			&& jumpNowSpeed >= 0.0f
			)
		{
			y = (float)((int)((y + sizeY) / objectSize)*objectSize - sizeY);
			//�t���O���Z�b�g
			gravityFlag = !gravityFlag;
			jumpNowSpeed = 0.0f;
		}

		//���Ƒ̂Ŕ���
		if ((pObject->mapData[(int)(y / objectSize)][(int)((x + movingDistance) / objectSize)].objectT != objectNull
			|| pObject->mapData[(int)(y / objectSize)][(int)((x + sizeX - movingDistance) / objectSize)].objectT != objectNull)
			&& jumpNowSpeed < 0.0f
			)
		{
			y = (float)((int)(y / objectSize)*objectSize + sizeY);
			jumpNowSpeed = 0.0f;
		}
		//��(�E)�Ŕ���
		if (pObject->mapData[(int)(y / objectSize)][(int)((x + sizeX) / objectSize)].objectT != objectNull
			|| pObject->mapData[(int)((y + sizeY - 1.0f) / objectSize)][(int)((x + sizeX) / objectSize)].objectT != objectNull)
		{
			x = (float)((int)((x + sizeX + movingDistance) / objectSize)*objectSize - sizeX - 0.1f);
		}
		//��(��)�Ŕ���
		else if (pObject->mapData[(int)(y / objectSize)][(int)((x) / objectSize)].objectT != objectNull
			|| pObject->mapData[(int)((y + sizeY - 1.0f) / objectSize)][(int)((x) / objectSize)].objectT != objectNull)
		{
			x = (float)((int)(((x - movingDistance) / objectSize) + 1.0f)*objectSize);
		}

		//�G�Ƃ̓����蔻��
		for (int num = 0; num < pEnemy->getEnemyNum(); num++)
		{
			//�����Ƒ̂Ŕ���
			if (((y + sizeY >= pEnemy->enemyData[num].y
				&&y + sizeY <= pEnemy->enemyData[num].y + pEnemy->enemyData[num].sizeY)
				&& (x + movingDistance < pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX
					&& x + sizeX - movingDistance> pEnemy->enemyData[num].x))
				&& jumpNowSpeed >= 0.0f
				)
			{
				y = (float)(pEnemy->enemyData[num].y - sizeY);

				if (pEnemy->enemyData[num].returnFlag == false)
				{
					x += pEnemy->movingDistance;
				}
				else
				{
					x -= pEnemy->movingDistance;
				}

				//�t���O���Z�b�g
				gravityFlag = !gravityFlag;
				jumpNowSpeed = 0.0f;
			}

			//��(�E)�Ŕ���
			if ((x + sizeX >= pEnemy->enemyData[num].x
				&&x + sizeX <= pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX / 2.0f)
				&& ((y > pEnemy->enemyData[num].y && y <= pEnemy->enemyData[num].y + pEnemy->enemyData[num].sizeY)
					|| (y + sizeY > pEnemy->enemyData[num].y&& y + sizeY <= pEnemy->enemyData[num].y + pEnemy->enemyData[num].sizeY)))
			{
				x = (float)(pEnemy->enemyData[num].x - sizeX - pEnemy->movingDistance);

				//�G�ƕǂɋ��܂ꂽ��
				if (pObject->mapData[(int)(y / objectSize)][(int)((x) / objectSize)].objectT != objectNull
					|| pObject->mapData[(int)((y + sizeY - 1.0f) / objectSize)][(int)((x) / objectSize)].objectT != objectNull)
				{
					x = (float)((int)(((x - movingDistance) / objectSize) + 1.0f)*objectSize);
					pEnemy->enemyData[num].returnFlag = !pEnemy->enemyData[num].returnFlag;
				}
				//�G�ƓG�ɋ��܂ꂽ��
				for (int num2 = 0; num2 < pEnemy->getEnemyNum(); num2++)
				{
					if (num != num2)
					{
						if ((x <= pEnemy->enemyData[num2].x + pEnemy->enemyData[num2].sizeX
							&&x >= pEnemy->enemyData[num2].x + pEnemy->enemyData[num2].sizeX / 2.0f)
							&& ((y > pEnemy->enemyData[num2].y&& y <= pEnemy->enemyData[num2].y + pEnemy->enemyData[num2].sizeY)
								|| (y + sizeY > pEnemy->enemyData[num2].y&& y + sizeY <= pEnemy->enemyData[num2].y + pEnemy->enemyData[num2].sizeY)))
						{
							pEnemy->enemyData[num].returnFlag = !pEnemy->enemyData[num].returnFlag;
							pEnemy->enemyData[num2].returnFlag = !pEnemy->enemyData[num2].returnFlag;
							break;
						}
					}
				}
				break;
			}
			//��(��)�Ŕ���
			else if ((x <= pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX
				&&x >= pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX / 2.0f)
				&& ((y > pEnemy->enemyData[num].y&& y <= pEnemy->enemyData[num].y + pEnemy->enemyData[num].sizeY)
					|| (y + sizeY > pEnemy->enemyData[num].y&& y + sizeY <= pEnemy->enemyData[num].y + pEnemy->enemyData[num].sizeY)))
			{
				x = (float)(pEnemy->enemyData[num].x + pEnemy->enemyData[num].sizeX + pEnemy->movingDistance);

				//��(�E)�Ŕ���
				if (pObject->mapData[(int)(y / objectSize)][(int)((x + sizeX) / objectSize)].objectT != objectNull
					|| pObject->mapData[(int)((y + sizeY - 1.0f) / objectSize)][(int)((x + sizeX) / objectSize)].objectT != objectNull)
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
							&& ((y > pEnemy->enemyData[num2].y&& y <= pEnemy->enemyData[num2].y + pEnemy->enemyData[num2].sizeY)
								|| (y + sizeY > pEnemy->enemyData[num2].y&& y + sizeY <= pEnemy->enemyData[num2].y + pEnemy->enemyData[num2].sizeY)))
						{
							pEnemy->enemyData[num].returnFlag = !pEnemy->enemyData[num].returnFlag;
							pEnemy->enemyData[num2].returnFlag = !pEnemy->enemyData[num2].returnFlag;
							break;
						}
					}
				}
				break;
			}
		}

		posY = y - (pObject->setPosY*objectSize);

		//�㉺�X�N���[��
		if (posY <= (9 * (objectSize))
			&& jumpNowSpeed <= 0)
		{
			if (pObject->setPosY > 0)
			{
				pObject->setPosY--;
			}
		}
		else if (posY > 11 * (objectSize)
			&& jumpNowSpeed > 0)
		{
			if (pObject->setPosY < pObject->mapSizeY - pObject->setMaxPosY)
			{
				pObject->setPosY++;
			}
		}
		posY = y - (pObject->setPosY*objectSize);
	}
}