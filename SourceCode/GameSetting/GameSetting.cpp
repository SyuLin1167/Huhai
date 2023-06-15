#include "GameSetting.h"
#include <DxLib.h>
#include"../Scene/SceneBase/SceneBase.h"

//のちに画面サイズの定数をObjBaseからSceneBaseに移動させる
#include"../Object/ObjectBase/ObjectBase.h"

//自身へのポインタ定義
GameSetting* GameSetting::gameSetting = nullptr;

// 初期化処理 //

int GameSetting::Init()
{
    //インスタンスの中身が空だったら中身を宣言する
    if (!gameSetting)
    {
        gameSetting = new GameSetting;
    }

    //ウィンドウの設定
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, ColorBit);
    SetWindowSizeExtendRate(1.0);

    //使用するDirect3Dのバージョン設定
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    //アンチエイリアスを設定
    SetFullSceneAntiAliasingMode(4, 2);

    if (DxLib_Init() == -1)
    {
        //ライブラリ初期化でエラーが起きたら終了
        return -1;
    }

    //描画先を裏画面に変更
    SetDrawScreen(DX_SCREEN_BACK);

    //Zバッファ設定
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    //標準ライトを無効化
    SetLightEnable(FALSE);

    //初期化成功
    return 0;
}

// 後処理 //

void GameSetting::Finalize()
{
    //Dxライブラリの後処理
    DxLib_End();

    //インスタンスの後処理
    delete gameSetting;
}

