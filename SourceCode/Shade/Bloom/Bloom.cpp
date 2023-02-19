#include "Bloom.h"
#include"../../Object/CharaObject/Camera/CameraFps.h"

Bloom* Bloom::bloom = nullptr;
int Bloom::GaussParam;
int Bloom::ColorScreen;
int Bloom::HighBrightScreen;
int Bloom::DownScaleScreen;
int Bloom::GaussScreen;

// @brief Bloomコンストラクター //

Bloom::Bloom()
{
    bloom = nullptr;

    //---スクリーンの作成---//
    ColorScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);                   //通常の描画結果を書き込むスクリーン作成
    HighBrightScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);              //上の結果から高輝度部分を抜き出した結果を書き込むスクリーン作成
    DownScaleScreen = MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, FALSE);        //高輝度部分を縮小した結果を書き込むスクリーン作成
    GaussScreen = MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, FALSE);            //縮小画像をガウスフィルタでぼかした結果を書き込むスクリーン作成

    SetBackgroundColor(255, 255, 255);                                              //ClearDrawScreen時にセットした色で画面を塗りつぶす

    GaussParam = 500;                                                               //ガウスのぼかし具合
}

// @briefb Bloomデストラクター //

Bloom::~Bloom()
{
    bloom = nullptr;
}

// @brief Bloom初期化処理 //

void Bloom::Init()
{
    if (!bloom)
    {
        bloom = new Bloom;
    }
}

// @brief スクリーンセット //

void Bloom::SetColoerScreen()
{
    SetDrawScreen(ColorScreen);
}

// @brief Bloom描画更新処理 //

void Bloom::DrawUpdate() 
{
    GraphFilterBlt(ColorScreen, HighBrightScreen,
        DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE,
        GetColor(0, 0, 0), 255);                                                    //描画結果から高輝度部分のみを抜き出した画像を得る
    GraphFilterBlt(HighBrightScreen,DownScaleScreen,
        DX_GRAPH_FILTER_DOWN_SCALE,DOWN_SCALE);                                     //高輝度部分を８分の１に縮小した画像を得る
    GraphFilterBlt(DownScaleScreen, GaussScreen,
        DX_GRAPH_FILTER_GAUSS, 16, GaussParam);                                     //８分の１に縮小した画像をガウスフィルタでぼかす

    SetDrawScreen(DX_SCREEN_BACK);                                                  //描画対象を裏画面にする
    ClearDrawScreenZBuffer();

    //---描画モード設定---//
    SetDrawMode(DX_DRAWMODE_BILINEAR);                                              //描画モードをバイリニアフィルタリングにする
    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);                                        //描画ブレンドモードを加算にする

    //---ぼかし画像描画---//
    DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GaussScreen, FALSE);         //高輝度部分を縮小してぼかした画像描画
    DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GaussScreen, FALSE);         //画面いっぱいに2回描画する
    
    //---描画モード後処理---//
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);                                    //ブレンドモードを無しにする
    SetDrawMode(DX_DRAWMODE_NEAREST);                                               //描画モードをニアレストにする

    //---途中経過描画---//
    DrawExtendGraph(180 * 0 + 24, 320, 180 * 0 + 24 + 160, 120 + 320, HighBrightScreen, FALSE);
    DrawExtendGraph(180 * 1 + 24, 320, 180 * 1 + 24 + 160, 120 + 320, DownScaleScreen, FALSE);
    DrawExtendGraph(180 * 2 + 24, 320, 180 * 2 + 24 + 160, 120 + 320, GaussScreen, FALSE);
}