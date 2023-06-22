#pragma once

#include"../LightBase/LightBase.h"

/*NomalLightクラス*/
class NomalLight :public LightBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    NomalLight();

    /// <summary>
    /// コントラクタ
    /// </summary>
    /// <param name="pos">:ワールド座標</param>
    NomalLight(VECTOR pos);


    /// <summary>
    /// デストラクタ
    /// </summary>
    ~NomalLight();

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
