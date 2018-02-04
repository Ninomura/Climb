#include"DirectSound.h"
#include"Wave.h"

#include"SoundBuffer.h"

//コンストラクタ
SoundBuffer::SoundBuffer()
{
	pBuffer = NULL;
}

//デストラクタ
SoundBuffer::~SoundBuffer()
{
	Release();
}

//解放処理
void SoundBuffer::Release()
{
	//バッファにデータが有るなら
	if (pBuffer != NULL)
	{
		//解放処理の前に再生を停止する
		Stop();

		pBuffer->Release();
		pBuffer = NULL;
	}
}

bool SoundBuffer::Create(WaveFile& waveFile)
{
	//バッファ作成用の設定　変数
	//desc : description

	DSBUFFERDESC desc = {};

	//チャンネル数で分岐
	//モノラル 1チャンネル
	//ステレオ 2チャンネル

	switch (waveFile.waveFormat.nChannels)
	{
	case 1:  //モノラル
		desc.dwFlags =
			DSBCAPS_CTRL3D |
			DSBCAPS_CTRLVOLUME |
			DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_GETCURRENTPOSITION2 |
			DSBCAPS_CTRLPOSITIONNOTIFY |
			DSBCAPS_STATIC;

		desc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;

		break;

	default:  //ステレオ 3チャンネル以上の場合もある

		if (waveFile.waveFormat.nChannels >= 2)
		{
			desc.dwFlags =
				//DSBCAPS_CTRL3D |//モノラルの設定から抜く
				DSBCAPS_CTRLVOLUME |
				DSBCAPS_CTRLFREQUENCY |
				DSBCAPS_GETCURRENTPOSITION2 |
				DSBCAPS_CTRLPOSITIONNOTIFY |
				DSBCAPS_STATIC |
				DSBCAPS_CTRLPAN;
			//モノラルのフラグ設定から最後の一行が増えただけ

			desc.guid3DAlgorithm = GUID_NULL;
		}

		break;
	}

	//構造体のサイズ
	desc.dwSize = sizeof(DSBUFFERDESC);
	//波形データのサイズ
	desc.dwBufferBytes = waveFile.dataSize;
	//waveファイルフォーマット
	desc.lpwfxFormat = &(waveFile.waveFormat);

	//設定終わり

	//デバイスの取得
	DirectSound*pDirectSound = DirectSound::GetInstance();

	//サウンドバッファ
	//メンバ変数のサウンドバッファと型が違う
	//型名としては8が付いているか付いていないか

	IDirectSoundBuffer* pBuffer_woek = NULL;

	//バッファの作成をDirectSoundクラスにやってもらう
	//waveFile.dataSizeが収まるようなデータ領域の確保
	if (FAILED(pDirectSound->CreateSoundBuffer(&desc, &pBuffer_woek)))
	{
		return false;
		//渡されたwaveデータに問題がある
		//初期化されていない
		//ロードの失敗
		//の可能性
	}

	//サウンドバッファの変換
	//IDirectSoundBufferからIDirectSoundBuffer8に変換
	//第一引数で返還後の方を指定
	//第二引数で返還後のデータをうけとるポインタ
	//なのでvoid**に変換して強引に引数を渡す
	pBuffer_woek->
		QueryInterface(IID_IDirectSoundBuffer8, (void**)&pBuffer);

	//変換出来たら変換元は用済み
	pBuffer_woek->Release();

	//データの書き込み
	unsigned char *block1 = nullptr;
	unsigned char *block2 = nullptr;
	unsigned long blockSize1 = 0;
	unsigned long blockSize2 = 0;

	//バッファをロック
	pBuffer->Lock(
		0, waveFile.dataSize,
		(void**)&block1, &blockSize1,
		(void**)&block2, &blockSize2,
		DSBLOCK_ENTIREBUFFER);

	//バッファに音データコピー
	memcpy(block1, waveFile.pWaveData, waveFile.dataSize);

	//ロック解除
	pBuffer->Unlock(block1, blockSize1, block2, 0);

	return true;

}

//再生開始
void SoundBuffer::Play(bool loop)
{
	if (pBuffer != NULL)
	{
		DWORD loopFlag = (loop ? DSBPLAY_LOOPING : 0);

		//第一引数 reserved 予約済み 0でなければならない
		//第二引数 priority 優先順位
		//         ハードウェアミキシングリソースを割り当てる際に使う。
		//         バッファを作成する際に DSBCAPS_LOCDEFER がフラグとして
		//         設定されていない場合は 0でなければならない
		//
		pBuffer->Play(0, 0, loopFlag);
	}
}

//再生停止
void SoundBuffer::Stop()
{
	if (pBuffer != NULL)
	{
		pBuffer->Stop();
	}
}