#pragma once
#include"../../../ObjectBase/ObjBase.h"

/// <summary>
/// FixedCameraクラス
/// </summary>
class FixedCamera :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FixedCamera();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FixedCamera();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override ;
};

