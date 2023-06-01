#include "Bloom.h"
#include"../../Object/CharaObject/Camera/CameraFps.h"

Bloom* Bloom::bloom = nullptr;

// @brief Bloomコンストラクター //

Bloom::Bloom()
    :ColorScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE))
    , HighBrightScreen(MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE))
    , DownScaleScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, FALSE))
    , GaussScreen(MakeScreen(DOWN_SCALE_WIDTH, DOWN_SCALE_HEIGHT, FALSE))
    , GaussParam(100)
{
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
    SetDrawScreen(bloom->ColorScreen);
}

// @brief Bloom描画準備 //

void Bloom::SetBloomGraph() 
{
    //int GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_BRIGHT_CLIP,
    //  int CmpType = クリップタイプ( DX_CMP_LESS:CmpParam以下をクリップ  又は  DX_CMP_GREATER:CmpParam以上をクリップ ), 
    // int CmpParam = クリップパラメータ( 0 ～ 255 ), int ClipFillFlag = クリップしたピクセルを塗りつぶすかどうか( TRUE:塗りつぶす  FALSE:塗りつぶさない ),
    // unsigned int ClipFillColor = クリップしたピクセルに塗る色値( GetColor で取得する )( ClipFillFlag が FALSE の場合は使用しない ),
    // int ClipFillAlpha = クリップしたピクセルに塗るα値( 0 ～ 255 )( ClipFillFlag が FALSE の場合は使用しない ) ) ;
    GraphFilterBlt(bloom->ColorScreen, bloom->HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP,
        DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);                                                                               //描画結果から高輝度部分のみを抜き出した画像を得る
    GraphFilterBlt(bloom->HighBrightScreen, bloom->DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);         //高輝度部分を８分の１に縮小した画像を得る
    GraphFilterBlt(bloom->DownScaleScreen, bloom->GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, bloom->GaussParam);                                     //８分の１に縮小した画像をガウスフィルタでぼかす

    SetDrawScreen(DX_SCREEN_BACK);                                                  //描画対象を裏画面にする
}

void Bloom::Draw()
{
    DrawGraph(0, 0, bloom->ColorScreen, TRUE);

    //---描画モード設定---//
    SetDrawMode(DX_DRAWMODE_BILINEAR);                                              //描画モードをバイリニアフィルタリングにする
    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);                                        //描画ブレンドモードを加算にする

    //---ぼかし画像描画---//
    DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bloom->GaussScreen, FALSE);         //高輝度部分を縮小してぼかした画像描画

    //---描画モード後処理---//
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);                                    //ブレンドモードを無しにする
    SetDrawMode(DX_DRAWMODE_NEAREST);                                               //描画モードをニアレストにする

    //---途中経過描画---//
    //DrawExtendGraph(180 * 0 + 24, 320, 180 * 0 + 24 + 160, 120 + 320, bloom->HighBrightScreen, FALSE);
    //DrawExtendGraph(180 * 1 + 24, 320, 180 * 1 + 24 + 160, 120 + 320, bloom->DownScaleScreen, FALSE);
    //DrawExtendGraph(180 * 2 + 24, 320, 180 * 2 + 24 + 160, 120 + 320, bloom->GaussScreen, FALSE);
}