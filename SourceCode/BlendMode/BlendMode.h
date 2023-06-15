#pragma once
#include<DxLib.h>

    /*BlendModeのクラス*/
class BlendMode
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="FadeSpeed">:フェード速度</param>
    BlendMode(int FadeSpeed = 4);

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
    void AddFade();

    /// <summary>
    /// フェードイン
    /// </summary>
    void SubFade();

    /// <summary>
    /// フェードフラグ
    /// </summary>
    /// <returns>フェード中:true|でない:false</returns>
    bool NowFade() { return nowFade; }

private:
    bool nowFade;                   //フェードフラグ
    int fadeValue;                  //フェード値
    int fadeSpeed;                  //フェード速度

    bool nowDark;                   //暗転フラグ
    const int darkValue = 150;      //暗転値
};

