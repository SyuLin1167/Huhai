#pragma once
#include<random>
#include<time.h>

#include"../LightBase/LightBase.h"

/// <summary>
/// BrinkingLightクラス
/// </summary>
class BlinkingLight :public LightBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="scene">:シーン名</param>
    /// <param name="num">:オブジェクト番号</param>
    BlinkingLight(std::string scene, std::string num = "0");

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BlinkingLight();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;

    /// <summary>
    /// 消灯処理
    /// </summary>
    void LightOff();
private:
    float intervalTime;     //インターバル
    float countTimer;       //カウント
    bool isBlinking;        //点滅判定

    const float BLINK_PARAM = 0.001f;                       //点滅値
    const COLOR_F BLINK_COLOR = { 0.8f, 0.8f, 0.8f, 0.8f }; //点滅色
};
