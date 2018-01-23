#pragma once
#include"ExternGV.h"
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class Object
{
private:

	//ブロックの重力
	float objectGravity = 0.25f;
	//変換用変数
	int conversion;
public:

	//描画比率
	static const int setMaxPosX = 30;
	static const int setMaxPosY = 20;
	//描画起点
	int setPosX, setPosY;
	//マップ比率
	int mapSizeX, mapSizeY;
	//ブロックのサイズ
	const float objectSize = 32.0f;

	//オブジェクト種類（未使用）
	enum objectType
	{
		null,     //空
		standard, //壊せるスタンダードなオブジェクト
		fixed,    //固定オブジェクト
		enemy,
	};
	//マップデータ
	vector< vector<objectType> > mapData;

	Object();
	~Object();

	//マップ生成
	void MapCreate();
	//判定処理（重力処理）
	void FallingProcessing();
};

Object::Object()
{
}

Object::~Object()
{
	mapData.~vector();
}

//マップ生成
void Object::MapCreate()
{
	//ファイル取得
	ifstream createMapData("MapData/01.txt");
	//読み込み確認
	if (!createMapData)
	{}
	else
	{}

	//サイズ取得
	createMapData >> mapSizeX;
	createMapData >> mapSizeY;

	//動的にサイズを変更
	mapData.resize(mapSizeY);
	for (int i = 0; i<mapSizeY; i++)
	{
		mapData[i].resize(mapSizeX);
	}

	//データ取得
	for (int y = 0; y < mapSizeY; y++)
	{
		for (int x = 0; x < mapSizeX; x++)
		{
			//取得
			createMapData >> conversion;
			//変換
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

	//ファイルのクローズ
	createMapData.close();
}

//判定処理（重力処理）
void Object::FallingProcessing()
{

}