#pragma once

//using namespace std;　stringを使用する際に std:: を省略できるが
//ヘッダー内でusing namespace を使用するのは良くないので使用しない
//※このヘッダーを読み込んだファイル全てで有効になるから

#pragma comment(lib,"dsound.lib")//ダウレクトサウンド
#include<dsound.h>//ダイレクトサウンド

#include<tchar.h>
#include<string>


//1つのWave形式の音声データファイルを読み込んで保持するクラス
class WaveFile
{
	//SoundBufferクラスからこのクラスのprivateなメンバに
	//アクセスできるようにする
	friend class SoundBuffer;

private:
	//読み込んだ（読み込もうとしている）
	//Waveファイルの記録のされ方
	WAVEFORMATEX waveFormat;

	int dataSize;//波形データのデータ量
	byte* pWaveData;//波形データ（音声データ）

public:
	//コンストラクタ
	WaveFile();
	//デストラクタ
	~WaveFile();

	//解放処理
	void Release();

	//ファイルロード
	bool Load(TCHAR*filePath);
	bool Load(std::string filePath);

};