#pragma once
#include<DxLib.h>
#include "../../GameSetting/GameSetting.h"

/// <summary>
/// ブルーム
/// </summary>
class Bloom
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Bloom();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Bloom();

    /// <summary>
    /// スクリーンセット
    /// </summary>
    void SetColoerScreen();

    /// <summary>
    /// 描画準備
    /// </summary>
    void SetBloomGraph();

    /// <summary>
    /// 描画更新処理
    /// </summary>
    void Draw();
private:
    const int DOWN_SCALE = 8;                                       //フィルターを掛ける画像が何分の１か
    const int DOWN_SCALE_WIDTH = (SCREEN_WIDTH / DOWN_SCALE);       //フィルターをかける画像の横幅
    const int DOWN_SCALE_HEIGHT = (SCREEN_HEIGHT / DOWN_SCALE);     //フィルターをかける画像の縦幅

    const int GAUSS_PIXEL = 16;       //ぼかしのピクセル値
    const int GAUSS_PARAM = 200;      //ガウスのぼかし具合
    const int CLIP_PARAM = 230;       //クリップパラメーター
    const int CLIP_ALPHA = 250;       //クリップアルファ値

    int ColorScreen;            //普通の描画結果用スクリーン
    int HighBrightScreen;       //描画結果から高輝度部分抜き出し用スクリーン
    int DownScaleScreen;        //高輝度部分縮小用スクリーン
    int GaussScreen;            //縮小画像ぼかし用スクリーン
};

