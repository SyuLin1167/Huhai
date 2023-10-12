#include "Bloom.h"

#include"../../GameSetting/GameSetting.h"
#include"../../Object/CharaObject/Camera/FpsCamera/FpsCamera.h"
#include"../../Scene/PauseMenu/PauseMenu.h"

/// <summary>
/// コンストラクタ
/// </summary>
Bloom::Bloom()
    :ColorScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, false))
    , HighBrightScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, false))
    , DownScaleScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, false))
    , GaussScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, false))
    , GaussParam(200)
{
    SetBackgroundColor(0, 0, 0);
}

/// <summary>
/// デストラクタ
/// </summary>
Bloom::~Bloom()
{
    //処理なし
}


/// <summary>
/// スクリーンセット
/// </summary>
void Bloom::SetColoerScreen()
{
    if (PauseMenu::HasStatus("Bloom"))
    {
        SetDrawScreen(ColorScreen);
    }
    SetCameraNearFar(CameraNear, CameraFar);
}

/// <summary>
/// 描画準備
/// </summary>
void Bloom::SetBloomGraph() 
{
    if (PauseMenu::HasStatus("Bloom"))
    {
        //描画結果から高輝度部分を抜き出してぼかす
        GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP,
            DX_CMP_LESS, 230, true, GetColor(0, 0, 0), 255);
        GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);
        GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussParam);

        //描画対象を裏画面にする
        SetDrawScreen(DX_SCREEN_BACK);
    }
}

/// <summary>
/// 描画更新処理
/// </summary>
void Bloom::Draw()
{
    if (PauseMenu::HasStatus("Bloom"))
    {
        //通常の画面を描画
        DrawGraph(0, 0, ColorScreen, true);

        //ぼかし画像描画
        SetDrawMode(DX_DRAWMODE_BILINEAR);
        SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
        DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GaussScreen, false);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        SetDrawMode(DX_DRAWMODE_NEAREST);
    }
}