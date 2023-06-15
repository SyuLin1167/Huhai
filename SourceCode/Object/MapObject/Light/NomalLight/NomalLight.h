#pragma once

#include"../LightBase/LightBase.h"

        /*NomalLightクラス*/
class NomalLight :public LightBase
{
public:
    /// <summary>
    /// NomalLightコンストラクタ
    /// </summary>
    NomalLight();

    /// <summary>
    /// NomalLightコントラクタ
    /// </summary>
    /// <param name="lightPos">:ライトのワールド座標</param>
    NomalLight(VECTOR lightPos);


    /// <summary>
    /// NomalLightデストラクタ
    /// </summary>
    ~NomalLight();

    /// <summary>
    /// NomalLight読み込み処理
    /// </summary>
    void Load();

    /// <summary>
    /// NomalLight更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;


    /// <summary>
    /// NomalLight描画処理
    /// </summary>
    void Draw()override;
};
