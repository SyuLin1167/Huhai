#pragma once

#include"../LightBase/LightBase.h"

/*LitLightクラス*/
class LitLight :public LightBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    LitLight();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pos">:ワールド座標</param>
    /// <param name="range">:点灯範囲</param>
    LitLight(VECTOR pos, float range);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~LitLight();

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
    float lightDistance;        //ライトからの距離
    float actionRange;          //反応範囲
};
