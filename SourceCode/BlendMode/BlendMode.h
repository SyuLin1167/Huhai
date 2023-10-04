#pragma once

#include"../GameSetting/GameSetting.h"

/*BlendModeクラス*/
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
    /// フェード
    /// </summary>
    void Fade();

    /// <summary>
    /// 暗転処理
    /// </summary>
    void Darken();

    /// <summary>
    /// デフォルト
    /// </summary>
    void NoBlend();

    /// <summary>
    /// フェードアウト
    /// </summary>
    void AddFade(float deltaTime);

    /// <summary>
    /// フェードイン
    /// </summary>
    void SubFade(float deltaTime);

    /// <summary>
    /// フェードフラグ
    /// </summary>
    /// <returns>フェード中:true|でない:false</returns>
    bool NowFade() { return nowFade; }

private:
    bool nowFade;                   //フェードフラグ
    float fadeValue;                  //フェード値
    float fadeSpeed;                  //フェード速度

    bool nowDark;                   //暗転フラグ
    const int darkValue = 150;      //暗転値
};

