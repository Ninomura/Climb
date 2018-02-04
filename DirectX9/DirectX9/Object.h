#pragma once
#include"ExternGV.h"
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

//�}�b�v�̓����N���X
class Object
{
private:

	//�u���b�N�̏d��
	float objectGravity = 0.25f;
	//�ϊ��p�ϐ�
	int conversion;
public:

	//�`��䗦
	static const int setMaxPosX = 30;
	static const int setMaxPosY = 20;

	//�`��N�_
	int setPosX, setPosY;
	//�}�b�v�䗦
	int mapSizeX, mapSizeY;
	//�u���b�N�̃T�C�Y
	const float objectSize = 32.0f;

	//�I�u�W�F�N�g���
	enum objectType
	{
		objectNull,     //��
		standard, //�󂹂�X�^���_�[�h�ȃI�u�W�F�N�g
		fixed,    //�Œ�I�u�W�F�N�g
		goal,
	};

	//�G���
	enum enemyType
	{
		enemyNull,
		eins,
		zwei,
		drei,
	};

	//�}�b�v���
	typedef struct
	{
		objectType objectT;
		enemyType enemyT;
	}mapType;

	//�}�b�v�f�[�^
	vector< vector<mapType> > mapData;

	Object();
	~Object();

	//�}�b�v����
	void MapCreate();
	//���菈���i�d�͏����j
	void FallingProcessing();
};

Object::Object()
{
}

Object::~Object()
{
	vector< vector<mapType> >().swap(mapData);
}

//�}�b�v����
void Object::MapCreate()
{
	//�t�@�C���擾
	ifstream createMapData("cl_data/MapData/01.txt");
	//�ǂݍ��݊m�F
	if (!createMapData)
	{}
	else
	{}

	//�T�C�Y�擾
	createMapData >> mapSizeX;
	createMapData >> mapSizeY;

	//���I�ɃT�C�Y��ύX
	mapData.resize(mapSizeY);
	for (int i = 0; i < mapSizeY; i++)
	{
		mapData[i].resize(mapSizeX);
	}

	//�f�[�^�擾
	for (int y = 0; y < mapSizeY; y++)
	{
		for (int x = 0; x < mapSizeX; x++)
		{
			//�擾
			createMapData >> conversion;

			mapData[y][x].objectT = objectNull;
			mapData[y][x].enemyT = enemyNull;
			//�ϊ�
			switch (conversion)
			{
			case 1:
				mapData[y][x].objectT = standard;
				break;
			case 2:
				mapData[y][x].objectT = fixed;
				break;
			case 3:
				mapData[y][x].enemyT = eins;
				break;
			case 4:
				mapData[y][x].enemyT = zwei;
				break;
			case 5:
				mapData[y][x].enemyT = drei;
				break;
			case 6:
				mapData[y][x].objectT = goal;
				break;
			}
		}
	}
	//�N�_�v�Z
	setPosX = mapSizeX - setMaxPosX;
	setPosY = mapSizeY - setMaxPosY;

	//�t�@�C���N���[�Y
	createMapData.close();
}

//���菈���i�d�͏����j
void Object::FallingProcessing()
{

}