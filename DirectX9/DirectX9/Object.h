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

	//�I�u�W�F�N�g��ށi���g�p�j
	enum objectType
	{
		null,     //��
		standard, //�󂹂�X�^���_�[�h�ȃI�u�W�F�N�g
		fall,     //�������Ă���I�u�W�F�N�g
	};
public:

	//�}�b�v�䗦
	int mapSizeX, mapSizeY;
	//�u���b�N�̃T�C�Y
	const float objectSize = 32.0f;
	//�}�b�v�f�[�^
	vector< vector<int> > mapData;
public:

	int setPosX, setPosY;
	static const int setMaxPosX = 30;
	static const int setMaxPosY = 20;

	Object();
	~Object();

	//�擾�֐�
	int getSetPosX() { return setPosX; }
	int getSetPosY() { return setPosY; }
	float getObjectSize() { return objectSize; }
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
			createMapData >> mapData[y][x];
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