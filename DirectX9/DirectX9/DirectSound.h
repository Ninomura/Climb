#pragma once

#define DIRECTSOUND_VERSION 0x800

#pragma comment (lib,"dsound.lib")

#include<dsound.h>

class DirectSound
{
private:
	//�V���O���g���ɂ���
	static DirectSound* pInstance;

	IDirectSound8* pDirectSound8; //�T�E���h�f�o�C�X�i���y�O�����u�j

	void Release();

	//�V���O���g���ɂ��邽�߂ɃN���X�O������s�ł��Ȃ��悤�ɂ���
	DirectSound();//�R���X�g���N�^

	~DirectSound();//�f�X�g���N�^�i�I�u�W�F�N�g����������ۂɌĂяo����Č㏈���Ȃǂ��s�Ȃ��֐��j

	void operator=(const DirectSound& obj) {}//������Z
	DirectSound(const DirectSound& obj) {}//�R�s�[�R���X�g���N�^

public:
	//�C���X�^���X�̎擾
	static DirectSound* GetInstance()
	{
		if (pInstance == NULL)
		{
			pInstance = new DirectSound();
		}
		return pInstance;
	}

	//�f�o�C�X�̍쐬
	//�f�o�C�X�i�O�����u�j
	bool Create(HWND hWnd);

	//�T�E���h�o�b�t�@�̍쐬
	//�T�E���h�o�b�t�@�i���y�f�[�^���ꎞ�I�ɋL������ꏊ�j
	HRESULT CreateSoundBuffer
	(DSBUFFERDESC*pDec, IDirectSoundBuffer**ppBuffer);

};
