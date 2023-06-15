#include "BlendMode.h"

    // コンストラクタ //

BlendMode::BlendMode(int FadeSpeed)
    :fadeValue(0)
    , fadeSpeed(FadeSpeed)
    , nowFade(false)
    , nowDark(false)
{
}

    // デストラクタ //

BlendMode::~BlendMode()
{
}

    // フェードアウト //

void BlendMode::AddFade()
{
    if (fadeValue <= 255)
    {
        //値が255以下だったらフェードアウトする
        nowFade = true;
        fadeValue += fadeSpeed;
    }
    else
    {
        //上の条件に当てはまらないならフェードしない
        nowFade = false;
    }
}

    // フェードイン //

void BlendMode::SubFade()
{
    if (fadeValue >= 0)
    {
        //値が0以上だったらフェードインする
        nowFade = true;
        fadeValue -= fadeSpeed;
    }
    else
    {
        //上の条件に当てはまらないならフェードしない
        nowFade = false;
    }
}

    // フェード //

void BlendMode::Fade()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
}

    // 暗転処理 //

void BlendMode::Darken()
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

void BlendMode::NoBlend()
{
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);                      //ノーブレンドモード
}