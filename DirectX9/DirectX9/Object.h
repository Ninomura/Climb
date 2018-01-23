#pragma once
#include"ExternGV.h"
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

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

	//�I�u�W�F�N�g��ށi���g�p�j
	enum objectType
	{
		null,     //��
		standard, //�󂹂�X�^���_�[�h�ȃI�u�W�F�N�g
		fixed,    //�Œ�I�u�W�F�N�g
		enemy,
	};
	//�}�b�v�f�[�^
	vector< vector<objectType> > mapData;

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
	mapData.~vector();
}

//�}�b�v����
void Object::MapCreate()
{
	//�t�@�C���擾
	ifstream createMapData("MapData/01.txt");
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
	for (int i = 0; i<mapSizeY; i++)
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
			//�ϊ�
			switch (conversion)
			{
			case 0:
				mapData[y][x] = null;
				break;
			case 1:
				mapData[y][x]= standard;
				break;
			case 2:
				mapData[y][x]= fixed;
				break;
			case 3:
				mapData[y][x] = enemy;
				break;
			}
		}
	}

	setPosX = mapSizeX - setMaxPosX;
	setPosY = mapSizeY - setMaxPosY;

	//�t�@�C���̃N���[�Y
	createMapData.close();
}

//���菈���i�d�͏����j
void Object::FallingProcessing()
{

}