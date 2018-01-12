#pragma once //インクルードガード

#define WindowHeightSize 640 //ウィンドウのY幅
#define WindowWidthSize  960  //ウィンドウのX幅

//ゲームのモード
enum Game_Mode
{
	StartScreenProcessing,   //スタート画面の設定
	GameStartProcessing,     //初期処理
	PlayerProcessing,        //プレイヤー操作
	GameEndProcessing,       //最終処理
};