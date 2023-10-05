#pragma once

#include"../LightBase/LightBase.h"

/*NomalLightクラス*/
class NomalLight :public LightBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="scene">:シーン名</param>
    /// <param name="num">:オブジェクト番号</param>
    NomalLight(std::string scene, std::string num = "0");


    /// <summary>
    /// デストラクタ
    /// </summary>
    ~NomalLight();

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
