#include "GameSetting.h"
#include <DxLib.h>
#include"../Scene/SceneBase/SceneBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameSetting::GameSetting()
{
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
GameSetting::~GameSetting()
{
    //Dxライブラリの後処理
    DxLib_End();
}

/// <summary>
/// 初期化処理
/// </summary>
/// <returns>初期化できたかどうか</returns>
int GameSetting::Init()
{
    //ログの非表示
    SetOutApplicationLogValidFlag(false);

    //ウィンドウの設定
    ChangeWindowMode(true);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, ColorBit);
    SetWindowSizeExtendRate(1.0);
    SetMainWindowText("Huhai");

    //アンチエイリアスを設定
    SetFullSceneAntiAliasingMode(4, 2);

    // Direct3D9Ex を使用する
    SetUseDirect3DVersion(DX_DIRECT3D_9EX);

    if (DxLib_Init() == -1)
    {
        //ライブラリ初期化でエラーが起きたら終了
        return -1;
    }

    if (GetValidShaderVersion() < 300)
    {
        //シェーダーモデル３．０が使用できない場合は終了
        DxLib_End();
        return 0;
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

