#pragma once

#include"../GameSetting/GameSetting.h"

/*Wipeクラス*/
class Wipe
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="speed">:フェード速度(デフォルト・80.0)</param>
    Wipe(float speed = 80.0f);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Wipe();

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

    /// <summary>
    /// 就寝
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Sleep(float deltaTime);

    /// <summary>
    /// 就寝描画処理
    /// </summary>
    void SleepDraw();

private:
    bool nowFade;                   //フェードフラグ
    float fadeValue;                  //フェード値
    float fadeSpeed;                  //フェード速度

    bool nowDark;                   //暗転フラグ
    const int darkValue = 150;      //暗転値

    int screenGraph;                //仮画面
    int gaussGraph;                 //ぼかし用画面
    float gaussValue;               //ぼかし値
};

