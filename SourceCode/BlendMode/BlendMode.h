#pragma once

#include"../GameSetting/GameSetting.h"

/// <summary>
/// スクリーンのブレンド
/// </summary>
class BlendMode
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="speed">:フェード速度(デフォルト・80.0)</param>
    BlendMode(float speed = 80.0f);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BlendMode();

    /// <summary>
    /// 暗転処理
    /// </summary>
    void Darken();
    
    /// <summary>
    /// フェードアウト
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void AddFade(const float deltaTime);

    /// <summary>
    /// フェードイン
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void SubFade(const float deltaTime);

    /// <summary>
    /// フェード
    /// </summary>
    void Fade();

    /// <summary>
    /// フェードフラグ
    /// </summary>
    /// <returns>フェード中:true|でない:false</returns>
    bool NowFade() { return nowFade; }

    /// <summary>
    /// デフォルト
    /// </summary>
    void NoBlend();

private:
    const int MAX_ALPHA = 250;      //最大α
    const int MIN_ALPHA = 0;        //最少α

    bool nowFade;                   //フェードフラグ
    float fadeValue;                //フェード値
    float fadeSpeed;                //フェード速度

    bool nowDark;                   //暗転フラグ
    const int DARK_VALUE = 150;      //暗転値
};

