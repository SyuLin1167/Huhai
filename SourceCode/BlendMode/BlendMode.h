#pragma once
#include<DxLib.h>

/*BlendModeのクラス*/
class BlendMode
{
public:
    /// <summary>
    /// BlendModeコンストラクタ
    /// </summary>
    BlendMode(int fadespeed = 4);

    /// <summary>
    /// BlendModeデストラクタ
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
    /// フェード加算
    /// </summary>
    void AddFade();

    /// <summary>
    /// フェード減算
    /// </summary>
    void SubFade();

    /// <summary>
    /// フェードフラグ
    /// </summary>
    /// <returns>:フェード中かどうか</returns>
    bool NowFade() { return nowFade; }

private:


    bool nowFade;                           //fadeフラグ
    int fadeValue;                          //fade値
    int fadeSpeed;                //fade速度

    bool nowDark;                           //darkフラグ
    const int darkValue = 150;              //dark値

    static BlendMode* blend;                //BlendModeの実体
};

