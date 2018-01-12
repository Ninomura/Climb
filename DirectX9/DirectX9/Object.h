#pragma once
class Object
{
private:
	//マップ比率
	const static int mapSizeX = 30;
	const static int mapSizeY = 20;

	//ブロックの重力
	float objectGravity = 0.25f;

protected:
	//ブロックのサイズ
	const int objectSize = 32;
	//マップデータ
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