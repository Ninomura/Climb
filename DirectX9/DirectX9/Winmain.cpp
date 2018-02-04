
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

#include <tchar.h>


#include"Direct3D.h"

#include "Sprite.h"
#include "Texture.h"

#include "DirectInput.h"

#include"DirectSound.h"
#include"Wave.h"
#include"SoundBuffer.h"

#include"ExternGV.h"
#include"Player.h"
#include"Enemy.h"
#include"Animation.h"

#include <random>

//ウィンドウプロシージャ
LRESULT CALLBACK WndPrc
(
	HWND hWnd,	//ウィンドウのハンドル
	UINT msg,	//メッセージ
	WPARAM wParam,
	LPARAM lParam
)
{
	//メッセージ処理のための関数
	//DispatchMessageによって呼び出される

	//ウィンドウクラスの登録時に
	//各ウィンドウに設定される

	//アプリケーションがメッセージを
	//取得したら呼び出される

	//メッセージの例

	//WM_DESTROY ウィンドウが破棄された
	//			 ×ボタンが押された時など
	//WM_MOVE    ウィンドウが移動
	//WM_SIZE    ウィンドウサイズの変更
	//等

	//特別な処理を必要とする場合
	//または自分で独自の処理を定義したい場合
	//ここでメッセージの種類に応じた
	//処理を行う

	//取りあえず WM_DESTROYが来た時の
	//終了処理のみ定義

	switch (msg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);

		//メッセージキューに
		//新しくWM_QUITメッセージを送る

		//いずれメッセージキューから
		//取り出され
		//メインループが終了する
		//(メインループの終了条件を
		//そのように作る)
		break;
	}

	//独自の処理を行ったら
	//デフォルトのウィンドウプロシージャを実行

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//ウィンドウ設定の名前
static const TCHAR* WC_BASIC = _T("Basic");

//作りたいウィンドウの設定を
//登録する関数
HRESULT RegistClassEx(HINSTANCE hInstance)
{
	//ウィンドウの設定を保存する構造体
	WNDCLASSEX wcex;

	//wcexの先頭アドレスから
	//WNDCLASSEXの長さ分のメモリを
	//全て0で埋める
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	//つまりはwcexが使用しているメモリ領域を
	//全て0で初期化する処理

	//ウィンドウの設定

	//構造体のサイズ
	wcex.cbSize = sizeof(WNDCLASSEX);

	//ウィンドウの設定情報に追加する捕捉を付けないので
	//0で固定
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	//Windowのスタイル
	//それぞれがビット単位のフラグであるため
	//オア演算で合成したものがスタイルの最終的な設定
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	//CS_HREDRAW 横サイズが変わったときウィンドウ全体の再描画
	//   VREDRAW 縦サイズが変わったときウィンドウ全体の再描画
	//   DBLCLKS ダブルクリックが発生したことをウィンドウに通知

	//WinMainのインスタンスハンドル
	wcex.hInstance = hInstance;

	//ウィンドウプロシージャのアドレス
	//関数ポインタの設定
	//ウィンドウプロシージャをOSが呼び出せるようにする
	wcex.lpfnWndProc = (WNDPROC)WndPrc;

	//背景色
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//メニュー　なし
	wcex.lpszMenuName = NULL;

	//ウィンドウクラスの名前　このウィンドウ設定の名前
	wcex.lpszClassName = WC_BASIC;

	//アイコン　デフォルトのを使う
	wcex.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wcex.hIconSm = NULL;

	//カーソル デフォルトのものを使う
	wcex.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	//設定したウィンドウクラスを登録
	//登録したウィンドウ設定でないと
	//ウィンドウを作ることができない
	return RegisterClassEx(&wcex);
	//HRESULT型の実行結果が戻される
}

//登録した設定を基にウィンドウを作成する
HRESULT MakeWindow
(HINSTANCE hInstance,//WinMainの識別子
	HWND &refHWnd,	//ウィンドウの識別子
					//正しくウィンドウの作成ができたら
					//この変数に識別子を代入する
	int width = WindowWidthSize,	//クライアント領域の幅
	int height = WindowHeightSize)	//クライアント領域の高さ
						//クライアント領域はウィンドウ全体から
						//外枠やメニューの部分を除いた物と今は思っておけばOK
{
	//クライアント領域のおおきさを決める
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = width;
	rect.bottom = height;

	//クライアント領域を保持するのに必要な
	//ウィンドウのおおきさを計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE/*TRUE*/);
	//正しく実行されるとrectの値が更新される

	//WS_OVERLAPPEDWINDOWはウィンドウのスタイルの一つ

	//ウィンドウのハンドル
	//ウィンドウの識別に使用する
	HWND hWnd;

	hWnd = CreateWindowEx
	(0,						//ウィンドウ拡張スタイル
		WC_BASIC,				//作りたいウィンドウクラス
								//あらかじめ登録されたもの
		_T("クライム"),			//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW,	//ウィンドウのスタイル
		CW_USEDEFAULT,			//位置x座標 デフォルトの値
		CW_USEDEFAULT,			//位置y座標 デフォルトの値
		rect.right - rect.left,	//ウィンドウ全体の幅
		rect.bottom - rect.top, //ウィンドウ全体の高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューのハンドル
		hInstance,				//WinMainのハンドル

		NULL);					//ウィンドウ作成データ
								//ウィンドウに好きな32ビットのデータを
								//付属させることができる
								//追加情報構造体へのポインタなど
								//を付けるのが無難な使い方か
								//今回は使わない

								//ウィンドウが正しく作れたかをチェック
								//正しく作れたらhWndにNULL以外が入るはず
	if (hWnd == NULL)
	{
		return S_FALSE;//HRESULT型　失敗を表す識別子の一つ
	}

	//ウィンドウをアクティブにして表示
	//hWndでウィンドウの識別をしていることに注目
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//クライアント領域の更新
	UpdateWindow(hWnd);

	//参照渡しになっている引数に
	//ウィンドウの識別ハンドルをコピーする
	//これによって今作ったウィンドウの識別ハンドルを
	//呼び出し元のプログラムで得ることができる
	refHWnd = hWnd;

	//HRESULT型　成功を表す識別子の一つ
	return S_OK;
}


//エントリーポイント
//プログラムの開始関数

int _stdcall WinMain
(HINSTANCE hInstance,	//プログラムを識別するハンドル
	HINSTANCE hPrevInstance,//アプリケーションの前のインスタンスハンドル
							//win32だと常にNULL
	LPSTR lpCmdLine,		//コマンドライン引数
	int nCmdShow)		//ウィンドウの表示状態
{

	if (FAILED(RegistClassEx(hInstance)))
	{
		MessageBox(NULL,
			TEXT("ウィンドウクラス設定失敗"),
			TEXT("テスト-タイトル"),
			MB_OK);
		return 0;
	}

	HWND hWnd = NULL;

	//正しくウィンドウが作成されれば
	//hWndにウィンドウの識別ハンドルが入る
	if (FAILED(MakeWindow(hInstance, hWnd)))
	{
		MessageBox(NULL,
			TEXT("ウィンドウ作成失敗"),
			TEXT("テスト-タイトル"),
			MB_OK);
		return 0;
	}

	//Direct3Dを管理するクラス(シングルトン)への参照を取得
	Direct3D& d3d = Direct3D::GetInstance();

	//Direct3DDeviceの作成を試みる
	if (d3d.TryCreate(hWnd))
	{

	}

	d3d.SetRenderState(RENDERSTATE::RENDER_ALPHABLEND);

	DirectInput * pDi = DirectInput::GetInstance();
	pDi->Init(hWnd);

	//ダイレクトサウンドのデバイス作成
	DirectSound* pDs = DirectSound::GetInstance();
	pDs->Create(hWnd);

	Player player;
	Enemy enemy;
	Object object;

	Animation titleAni;

	//スプライト
	//背景
	Sprite spriteImgBg;
	spriteImgBg.SetSize(WindowWidthSize, WindowHeightSize);
	spriteImgBg.SetPos(WindowWidthSize / 2, WindowHeightSize / 2);
	//タイトルロゴ
	Sprite spriteImgTitleRogo;
	spriteImgTitleRogo.SetSize(900, 528);
	spriteImgTitleRogo.SetPos(WindowWidthSize / 2, WindowHeightSize / 2);
	//オブジェクト
	Sprite spriteImgObject;
	spriteImgObject.SetSize(object.objectSize, object.objectSize);
	//プレイヤー
	Sprite spriteImgPlayer;
	spriteImgPlayer.SetSize(player.getSizeX(), player.getSizeY());
	//ブロー君
	Sprite spriteImgEnemy;

	//テクスチャ設定
	//フレーム
	Texture imgframe;
	imgframe.Load(_T("cl_data/Texture/cl_frame.png"));
	//タイトル
	Texture imgTitle;
	imgTitle.Load(_T("cl_data/Texture/cl_title.png"));
	Texture imgTitleAni;
	imgTitleAni.Load(_T("cl_data/Texture/cl_titleAni.png"));
	imgTitleAni.SetDivide(10, 0);
	//クリア
	Texture imgClear;
	imgClear.Load(_T("cl_data/Texture/cl_clear.png"));
	//背景
	Texture imgBg;
	imgBg.Load(_T("cl_data/Texture/cl_Bg.png"));
	//オブジェクト
	Texture imgObject;
	imgObject.Load(_T("cl_data/Texture/cl_BaseBlock.png"));
	imgObject.SetDivide(4, 1);
	//プレイヤー
	Texture imgPlayer;
	imgPlayer.Load(_T("cl_data/Texture/cl_Player.png"));
	imgPlayer.SetDivide(4, 1);
	imgPlayer.SetNum(2, 0);
	//ブロー君
	Texture imgEnemy_eins;
	imgEnemy_eins.Load(_T("cl_data/Texture/cl_enemy_eins.png"));
	Texture imgEnemy_zwei;
	imgEnemy_zwei.Load(_T("cl_data/Texture/cl_enemy_zwei.png"));
	Texture imgEnemy_drei;
	imgEnemy_drei.Load(_T("cl_data/Texture/cl_enemy_drei.png"));

	//サウンド
	WaveFile titleWave;
	titleWave.Load("cl_data/Sound/cl_titleBGM.wav");
	SoundBuffer titleBGM;
	titleBGM.Create(titleWave);
	titleBGM.Play(true);

	//初期を演算処理に設定
	Game_Mode Mode = StartScreenProcessing;

	MSG msg = {};

	//メインプログラム-------------------------------------------------
	while (msg.message != WM_QUIT)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//仮想キーメッセージを文字メッセージに変換し
			//それをメッセージキューにポストする
			TranslateMessage(&msg);

			//メッセージの割り当て
			//ウィンドウプロシージャでメッセージを処理
			DispatchMessage(&msg);
		}
		else
		{
			pDi->Update();//キー状態の更新
			switch (Mode)
			{
				//スタート画面
			case Game_Mode::StartScreenProcessing:

				if (pDi->KeyJustPressed(DIK_RETURN)) 
				{ 
					titleBGM.Stop();
					Mode = GameStartProcessing; 
				}

				break;

			//初期処理
			case Game_Mode::GameStartProcessing:

				player.~Player();

				object.MapCreate();
				player.PlayerCreate();
				enemy.CreateEnemy(&object);

				//プレイヤー操作に移動
				Mode = PlayerProcessing;
				break;

			//プレイヤー操作
			case Game_Mode::PlayerProcessing:

				//強制終了
				if (pDi->KeyJustPressed(DIK_F1))
				{

					enemy.~Enemy();
					object.~Object();
					player.~Player();

					titleBGM.Play(true);
					Mode = StartScreenProcessing;

					break;
				}

				enemy.MoveEnemy(&object);
				//移動処理
				player.PlayerMove(pDi, &imgPlayer, &object,&enemy);
				//重力処理
				object.FallingProcessing();

				if (player.getGoalFlag() == true)
				{
					enemy.~Enemy();
					object.~Object();
					player.~Player();

					Mode = GameEndProcessing;
				}

				break;

			//ゲーム終了
			case Game_Mode::GameEndProcessing:

				if (pDi->KeyJustPressed(DIK_RETURN)) 
				{
					titleBGM.Play(true);
					Mode = StartScreenProcessing;
				}

				break;
			}

			//描画処理
			if (SUCCEEDED(d3d.BeginScene()))
			{
				d3d.ClearScreen();

				switch (Mode)
				{
				case StartScreenProcessing:
					//タイトル
					titleAni.processing(10, 10);
					imgTitleAni.SetNum(titleAni.getNum(), 0);
					spriteImgBg.Draw(imgTitleAni);
					spriteImgTitleRogo.Draw(imgTitle);
					break;
				case PlayerProcessing:
					//背景
					spriteImgBg.Draw(imgBg);
					//プレイヤー
					spriteImgPlayer.SetPos
					(player.getPosX() + player.getSizeX() / 2.0f,
						player.getPosY() + player.getSizeY() / 2.0f);
					spriteImgPlayer.Draw(imgPlayer);

					//敵
					for (int num = 0; num < enemy.getEnemyNum(); num++)
					{
						spriteImgEnemy.SetSize(enemy.enemyData[num].sizeX, enemy.enemyData[num].sizeY);
						spriteImgEnemy.SetPos(enemy.enemyData[num].posX + enemy.enemyData[num].sizeX / 2.0f,
							enemy.enemyData[num].posY + enemy.enemyData[num].sizeY / 2.0f);

						if (enemy.enemyData[num].hp > 0)
						{
							switch (enemy.enemyData[num].type)
							{
							case enemy.eins:
								spriteImgEnemy.Draw(imgEnemy_eins);
								break;
							case enemy.zwei:
								spriteImgEnemy.Draw(imgEnemy_zwei);
								break;
							case enemy.drei:
								spriteImgEnemy.Draw(imgEnemy_drei);
								break;
							}

						}
					}

					//マップ
					for (int y = 0; y < object.setMaxPosY; y++)
					{
						for (int x = 0; x < object.setMaxPosX; x++)
						{
							spriteImgObject.SetPos
							(x*object.objectSize + object.objectSize / 2,
								y*object.objectSize + object.objectSize / 2);

							switch (object.mapData[y + object.setPosY][x].objectT)
							{
							case object.objectNull:
								break;
							case object.standard:
								imgObject.SetNum(0, 0);
								spriteImgObject.Draw(imgObject);
								break;
							case object.fixed:
								imgObject.SetNum(1, 0);
								spriteImgObject.Draw(imgObject);
								break;
							case object.goal:
								imgObject.SetNum(2, 0);
								spriteImgObject.Draw(imgObject);
								break;
							}
						}
					}
					break;
				case GameEndProcessing:
					spriteImgBg.Draw(imgClear);
					break;
				}
				//フレーム
				spriteImgBg.Draw(imgframe);

				d3d.EndScene();
				//バックバッファをフロントへ反映
				d3d.Present();
			}
		}
	}

	return 0;
};
