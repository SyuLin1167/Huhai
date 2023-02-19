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
    /// Bloom初期化処理
    /// </summary>
    static void Init();

    /// <summary>
    /// スクリーンセット
    /// </summary>
    static void SetColoerScreen();

    /// <summary>
    /// Bloom描画更新処理
    /// </summary>
    static void DrawUpdate();
private:
    /// <summary>
    /// コンストラクター(シングルトン)
    /// </summary>
    Bloom();

    /// <summary>
    /// デストラクター
    /// </summary>
	~Bloom();

    static int GaussParam;             //ガウスのぼかし具合
    static int ColorScreen;            //普通の描画結果を書き込むスクリーン
    static int HighBrightScreen;       //普通の描画結果から高輝度部分を抜き出した結果を書き込むスクリーン
    static int DownScaleScreen;        //高輝度部分を縮小した結果を書き込むスクリーン
    static int GaussScreen;            //縮小画像をガウスフィルタでぼかした結果を書き込むスクリーン

    static Bloom* bloom;               //Bloomの実態
};

