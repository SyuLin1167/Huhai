#include "BlendMode.h"
#include<DxLib.h>
#include<math.h>
#include"../Object/ObjectBase/ObjBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="speed">:フェード速度(デフォルト・80.0)</param>
BlendMode::BlendMode(float FadeSpeed)
    :fadeValue(0.0f)
    , fadeSpeed(FadeSpeed)
    , nowFade(false)
    , nowDark(false)
{
    // 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
BlendMode::~BlendMode()
{
}

/// <summary>
/// フェードアウト
/// </summary>
void BlendMode::AddFade(float deltaTime)
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

/// <summary>
/// フェードイン
/// </summary>
void BlendMode::SubFade(float deltaTime)
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

/// <summary>
/// フェード
/// </summary>
void BlendMode::Fade()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeValue));
}

/// <summary>
/// 暗転処理
/// </summary>
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

/// <summary>
/// デフォルト
/// </summary>
void BlendMode::NoBlend()
{
    //ノーブレンドモード
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}