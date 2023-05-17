#include "BlendMode.h"

// @brief BlendModeコンストラクタ //

BlendMode::BlendMode()
    :fadeValue(0)
    ,nowFade(false)
    ,nowDark(false)
{
}

// @brief BlendModeデストラクタ //

BlendMode::~BlendMode()
{
}

// @brief フェード加算 //

void BlendMode::AddFade()
{
    if (fadeValue <= 255)                                    //((値が255以下だったら))
    {
        nowFade = true;                                      //フェード中
        fadeValue += fadeSpeed;                       //値に速度を加算
    }
    else                                                            //((上の条件が当てはまらないなら))
    {
        nowFade = false;                                     //フェード中でない
    }

}

// @brief フェード減算 //

void BlendMode::SubFade()
{
    if (fadeValue >= 0)                                      //((値が0以上だったら))
    {
        nowFade = true;                                      //フェード中
        fadeValue -= fadeSpeed;                       //値に速度を減算
    }
    else                                                            //((上の条件が当てはまらないなら))
    {
        nowFade = false;                                     //フェード中でない
    }
}

// @brief フェード //

void BlendMode::Fade()
{
        //～フェード処理～//
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);         //アルファブレンドモード設定
}

// @brief 暗転処理 //

void BlendMode::Darken()
{
    if (nowFade)
    {
        nowDark = false;
    }
    else
    {
        SetDrawBlendMode(DX_BLENDMODE_ADD, darkValue);           //サブブレンドモード
        nowDark = true;
    }
}

// @brief デフォルト //

void BlendMode::NoBlend()
{
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);                      //ノーブレンドモード
}