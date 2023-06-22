#pragma once
#include"../LightBase/LightBase.h"

/*FlashLighitクラス*/
class FlashLight :public LightBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FlashLight();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="lightPos">:ライトのワールド座標</param>
    FlashLight(VECTOR lightPos);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FlashLight();

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
};
