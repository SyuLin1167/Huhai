#pragma once
#include<random>
#include<time.h>

#include"../LightBase/LightBase.h"

        /*BlinkingLighitクラス*/
class BlinkingLight :public LightBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BlinkingLight();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pos">:ワールド座標</param>
    BlinkingLight(VECTOR pos);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BlinkingLight();

    /// <summary>
    /// 読み込み処理
    /// </summary>
    void Load();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

private:
    float intervalTime;     //インターバル
    float countTimer;       //カウント
    bool isBlinking;        //点滅判定
};
