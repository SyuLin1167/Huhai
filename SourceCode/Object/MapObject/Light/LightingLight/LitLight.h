#pragma once

#include"../LightBase/LightBase.h"

/*LitLightクラス*/
class LitLight :public LightBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="scene">:シーン名</param>
    /// <param name="num">:オブジェクト番号</param>
    LitLight(std::string scene, std::string num = "0");

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~LitLight();

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
    float lightDistance;        //ライトからの距離
    const float ACTION_RANGE = 55.0f;          //反応範囲
};
