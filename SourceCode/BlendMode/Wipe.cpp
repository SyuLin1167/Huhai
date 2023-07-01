#include "Wipe.h"
#include<DxLib.h>
#include<math.h>
#include"../Object/ObjectBase/ObjectBase.h"

// コンストラクタ //

Wipe::Wipe(float FadeSpeed)
    :fadeValue(0.0f)
    , fadeSpeed(FadeSpeed)
    , nowFade(false)
    , nowDark(false)
    , screenGraph(MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE))
    , gaussGraph(MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE))
    , gaussValue(0.0f)
{
}

// デストラクタ //

Wipe::~Wipe()
{
}

// フェードアウト //

void Wipe::AddFade(float deltaTime)
{
    if (fadeValue <= 255)
    {
        //値が255以下だったらフェードアウトする
        nowFade = true;
        fadeValue += fadeSpeed * deltaTime;
        if (fadeValue <= 0)
        {
            fadeValue = 0;
        }
    }
    else
    {
        //上の条件に当てはまらないならフェードしない
        nowFade = false;
    }
}

// フェードイン //

void Wipe::SubFade(float deltaTime)
{
    if (fadeValue >= 0)
    {
        //値が0以上だったらフェードインする
        nowFade = true;
        fadeValue -= fadeSpeed * deltaTime;
        if (fadeValue >= 255)
        {
            fadeValue = 255;
        }
    }
    else 
    {
        //上の条件に当てはまらないならフェードしない
        nowFade = false;
    }
}

// フェード //

void Wipe::Fade()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeValue));
}

// 暗転処理 //

void Wipe::Darken()
{
    if (nowFade)
    {
        //フェード中だったら暗転しない
        nowDark = false;
    }
    else
    {
        //フェード中でないなら暗転する
        SetDrawBlendMode(DX_BLENDMODE_ADD, darkValue);
        nowDark = true;
    }
}

// デフォルト //

void Wipe::NoBlend()
{
    //ノーブレンドモード
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 就寝 //

void Wipe::Sleep(float deltaTime)
{
    //瞬きさせる
    if (gaussValue < DX_PI_F*3)
    {
        gaussValue += 0.05f ;
    }
}

// 就寝描画処理 //

void Wipe::SleepDraw()
{
    //描画先を仮画面にして全体を赤にする
    SetDrawScreen(screenGraph);

    //ぼかす
    GraphFilterBlt(screenGraph, gaussGraph, DX_GRAPH_FILTER_GAUSS, 16, 200 * sin(gaussValue));

    //描画先を裏画面に変更
    SetDrawScreen(DX_SCREEN_BACK);

    //画像描画
    DrawGraph(0, 0, gaussGraph, TRUE);
}