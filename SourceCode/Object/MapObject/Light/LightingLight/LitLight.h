#pragma once

#include"../LightBase/LightBase.h"

        /*LitLightクラス*/
class LitLight :public LightBase
{
public:
    /// <summary>
    /// LitLightコンストラクタ
    /// </summary>
    LitLight();

    /// <summary>
    /// LitLightコンストラクタ
    /// </summary>
    /// <param name="lightPos">:ライトのワールド座標</param>
    /// <param name="litRange">:点灯範囲</param>
    LitLight(VECTOR lightPos, float range);

    /// <summary>
    /// LitLightデストラクタ
    /// </summary>
    ~LitLight();

    /// <summary>
    /// LitLight読み込み処理
    /// </summary>
    void Load();

    /// <summary>
    /// LitLight更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// LitLight描画処理
    /// </summary>
    void Draw()override;

private:
    float lightDistance;        //ライトからの距離
    float actionRange;        //反応範囲
};
