#pragma once
#include"ExternGV.h"
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

//マップの統括クラス
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

	//オブジェクト種類
	enum objectType
	{
		objectNull,     //空
		standard, //壊せるスタンダードなオブジェクト
		fixed,    //固定オブジェクト
		goal,
	};

	//敵種類
	enum enemyType
	{
		enemyNull,
		eins,
		zwei,
		drei,
	};

	//マップ種類
	typedef struct
	{
		objectType objectT;
		enemyType enemyT;
	}mapType;

	//マップデータ
	vector< vector<mapType> > mapData;

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
	vector< vector<mapType> >().swap(mapData);
}

//マップ生成
void Object::MapCreate()
{
	//ファイル取得
	ifstream createMapData("cl_data/MapData/01.txt");
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
	for (int i = 0; i < mapSizeY; i++)
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

			mapData[y][x].objectT = objectNull;
			mapData[y][x].enemyT = enemyNull;
			//変換
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
	//起点計算
	setPosX = mapSizeX - setMaxPosX;
	setPosY = mapSizeY - setMaxPosY;

	//ファイルクローズ
	createMapData.close();
}

//判定処理（重力処理）
void Object::FallingProcessing()
{

}