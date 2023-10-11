#pragma once

#include"../GameSetting/GameSetting.h"

/// <summary>
/// BlendModeクラス
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
    void AddFade(float deltaTime);

    /// <summary>
    /// フェードイン
    /// </summary>
    void SubFade(float deltaTime);

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
    bool nowFade;                   //フェードフラグ
    float fadeValue;                  //フェード値
    float fadeSpeed;                  //フェード速度

    bool nowDark;                   //暗転フラグ
    const int darkValue = 150;      //暗転値
};

