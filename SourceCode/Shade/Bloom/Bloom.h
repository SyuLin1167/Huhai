#pragma once
#include<DxLib.h>

#include"../../Object/ObjectBase/ObjectBase.h"

#define DOWN_SCALE 8                                    //フィルターを掛ける画像が何分の１か
#define DOWN_SCALE_WIDTH (SCREEN_WIDTH/DOWN_SCALE)         //フィルターをかける画像の横幅
#define DOWN_SCALE_HEIGHT (SCREEN_HEIGHT/DOWN_SCALE)       //フィルターをかける画像の縦幅

/*ブルームのクラス*/
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

    int GaussParam;             //ガウスのぼかし具合
    int ColorScreen;            //普通の描画結果用スクリーン
    int HighBrightScreen;       //描画結果から高輝度部分抜き出し用スクリーン
    int DownScaleScreen;        //高輝度部分縮小用スクリーン
    int GaussScreen;            //縮小画像ぼかし用スクリーン
};

