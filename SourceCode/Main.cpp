#include"DxLib.h"
#include"Scene/SceneManager/SceneManager.h"
#include"Object/ObjectManager/ObjManager.h"
#include"Asset/AssetManager/AssetManager.h"

int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int)
{

	SetGraphMode(ScreenWidth, ScreenHeight, ColorBit);		//画面モードのセット


	//---DXライブラリ初期化---//
	SetUseDirect3DVersion(DX_DIRECT3D_11);					//使用するDirect3Dのバージョン設定
	ChangeWindowMode(TRUE);									//ウィンドウモードの変更
	if (DxLib_Init() == -1)
	{
		return -1;											//エラーが起きたら終了
	}

	//---Zバッファ設定---//
	SetUseZBuffer3D(TRUE);									//Zバッファを有効にする
	SetWriteZBuffer3D(TRUE);								//Zバッファ絵の書き込みを有効にする

	//---管理クラスの初期化処理---//
	SceneManager* sceneManager = new SceneManager();
	ObjManager::Init();
	AssetManager::Init();

	//標準ライトを無効化
	//SetLightEnable(FALSE);

	// Ｘ軸にマイナス方向のディレクショナルタイプのライトの作成
	int LightHandle = CreatePointLightHandle(VGet(0.0f, 50.0f, 0.0f),100.0f,0.0f,0.0f,0.002f);
	
	

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