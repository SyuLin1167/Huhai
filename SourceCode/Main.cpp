#include<DxLib.h>
#include"Scene/SceneManager/SceneManager.h"
#include"Object/ObjectManager/ObjManager.h"
#include"Asset/AssetManager/AssetManager.h"

int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int)
{

    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, ColorBit);    //画面モードのセット
    SetWindowSizeExtendRate(1.0);

    SetUseDirect3DVersion(DX_DIRECT3D_11);					//使用するDirect3Dのバージョン設定
    ChangeWindowMode(TRUE);									//ウィンドウモードの変更
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);			//画面の解像度と色ビットと深度を設定

	SetFullSceneAntiAliasingMode(4, 2);                     //アンチエイリアスを設定

    //---DXライブラリ初期化---//
	if (DxLib_Init() == -1)
	{
		return -1;											//エラーが起きたら終了
	}

	SetDrawScreen(DX_SCREEN_BACK);                          //描画先を裏画面に変更

	//---Zバッファ設定---//
	SetUseZBuffer3D(TRUE);									//Zバッファを有効にする
	SetWriteZBuffer3D(TRUE);								//Zバッファ絵の書き込みを有効にする

	//---管理クラスの初期化処理---//
	SceneManager* sceneManager = new SceneManager;
	AssetManager::Init();
	ObjManager::Init();

	//標準ライトを無効化
	SetLightEnable(FALSE);
	SetBackgroundColor(150, 150, 150);

	//---シーンループ---//
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)			//ウィンドウが閉じられるか、ESCキーが押されるまで実行
	{
		sceneManager->Update();								//更新処理
		ClearDrawScreen();									//画面を初期化

		sceneManager->Draw();								//描画処理
		ScreenFlip();										//裏画面の内容を表描画に反映
	}

	//---管理クラスの後処理---//
	ObjManager::Finalize();
	AssetManager::Finalize();

	DxLib_End();											//Dxライブラリの後処理

	return 0;												//ソフトの終了
}