#pragma once
class Object
{
private:
	//�}�b�v�䗦
	const static int mapSizeX = 30;
	const static int mapSizeY = 20;

	//�u���b�N�̏d��
	float objectGravity = 0.25f;

protected:
	//�u���b�N�̃T�C�Y
	const int objectSize = 32;
	//�}�b�v�f�[�^
	int mapData[mapSizeY][mapSizeX];

public:
	Object();
	~Object();

	int getMapData();
	void MapCreate();
};

Object::Object()
{
}

Object::~Object()
{
}

int Object::getMapData()
{
	return mapData[mapSizeY][mapSizeX];
}

void Object::MapCreate()
{

}