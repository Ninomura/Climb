#pragma once

#pragma comment(lib,"dsound.lib")

#include<dsound.h>

class WaveFile;

class SoundBuffer
{
private:

	IDirectSoundBuffer8 *pBuffer; //サウンドバッファ

public:
	SoundBuffer();   //コンストラクタ

	~SoundBuffer();  //デストラクタ

	bool Create(WaveFile& waveFile);

	void Play(bool loop);	//再生

	void Stop();            //停止

	void Release();         //解放

};