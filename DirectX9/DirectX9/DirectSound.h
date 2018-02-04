#pragma once

#define DIRECTSOUND_VERSION 0x800

#pragma comment (lib,"dsound.lib")

#include<dsound.h>

class DirectSound
{
private:
	//シングルトンにする
	static DirectSound* pInstance;

	IDirectSound8* pDirectSound8; //サウンドデバイス（音楽外部装置）

	void Release();

	//シングルトンにするためにクラス外から実行できないようにする
	DirectSound();//コンストラクタ

	~DirectSound();//デストラクタ（オブジェクトを消去する際に呼び出されて後処理などを行なう関数）

	void operator=(const DirectSound& obj) {}//代入演算
	DirectSound(const DirectSound& obj) {}//コピーコンストラクタ

public:
	//インスタンスの取得
	static DirectSound* GetInstance()
	{
		if (pInstance == NULL)
		{
			pInstance = new DirectSound();
		}
		return pInstance;
	}

	//デバイスの作成
	//デバイス（外部装置）
	bool Create(HWND hWnd);

	//サウンドバッファの作成
	//サウンドバッファ（音楽データを一時的に記憶する場所）
	HRESULT CreateSoundBuffer
	(DSBUFFERDESC*pDec, IDirectSoundBuffer**ppBuffer);

};
