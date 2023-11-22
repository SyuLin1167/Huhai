#include "BlendMode.h"
#include<DxLib.h>
#include<math.h>
#include"../Object/ObjectBase/ObjBase.h"

BlendMode::BlendMode(float FadeSpeed)
    :fadeValue(0.0f)
    , fadeSpeed(FadeSpeed)
    , nowFade(false)
    , nowDark(false)
{
    // 処理なし
}

BlendMode::~BlendMode()
{
    //処理なし
}

void BlendMode::AddFade(const float deltaTime)
{
    if (fadeValue <= MAX_ALPHA)
    {
        //値が255以下だったらフェードアウトする
        nowFade = true;
        fadeValue += fadeSpeed * deltaTime;
        if (fadeValue <= MIN_ALPHA)
        {
            fadeValue = static_cast<float>(MIN_ALPHA);
        }
    }
    else
    {
        //上の条件に当てはまらないならフェードしない
        nowFade = false;
    }
}

void BlendMode::SubFade(const float deltaTime)
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

void BlendMode::Fade()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeValue));
}

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
        SetDrawBlendMode(DX_BLENDMODE_ADD, DARK_VALUE);
        nowDark = true;
    }
}

void BlendMode::NoBlend()
{
    //ノーブレンドモード
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MIN_ALPHA);
}