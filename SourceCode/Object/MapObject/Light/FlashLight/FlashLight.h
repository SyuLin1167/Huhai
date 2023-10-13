#pragma once
#include"../LightBase/LightBase.h"

/// <summary>
/// FlashLightクラス
/// </summary>
class FlashLight :public LightBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FlashLight();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FlashLight();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;
};
