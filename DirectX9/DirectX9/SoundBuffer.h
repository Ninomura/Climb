#pragma once

#pragma comment(lib,"dsound.lib")

#include<dsound.h>

class WaveFile;

class SoundBuffer
{
private:

	IDirectSoundBuffer8 *pBuffer; //�T�E���h�o�b�t�@

public:
	SoundBuffer();   //�R���X�g���N�^

	~SoundBuffer();  //�f�X�g���N�^

	bool Create(WaveFile& waveFile);

	void Play(bool loop);	//�Đ�

	void Stop();            //��~

	void Release();         //���

};