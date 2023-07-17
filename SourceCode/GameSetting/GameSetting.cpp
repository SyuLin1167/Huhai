#include "GameSetting.h"
#include <DxLib.h>
#include"../Scene/SceneBase/SceneBase.h"

//のちに画面サイズの定数をObjBaseからSceneBaseに移動させる
#include"../Object/ObjectBase/ObjectBase.h"



// 初期化処理 //

int GameSetting::Init()
{
    //ログの非表示
    SetOutApplicationLogValidFlag(false);

    //ウィンドウの設定
    ChangeWindowMode(true);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, ColorBit);
    SetWindowSizeExtendRate(1.0);
    SetMainWindowText("Huhai");

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
    SetUseZBuffer3D(true);
    SetWriteZBuffer3D(true);

    //標準ライトを無効化
    SetLightEnable(false);
    SetUsePixelLighting(true);

    //初期化成功
    return 0;
}

// 後処理 //

void GameSetting::Finalize()
{
    //Dxライブラリの後処理
    DxLib_End();
}

