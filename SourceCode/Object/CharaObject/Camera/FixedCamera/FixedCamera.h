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
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override ;

private:
    const VECTOR FIRST_POS = VGet(70, 6, 75);           //初期座標
    const VECTOR FIRST_AIM_POS = VGet(-10, 10, 25);     //初期目標座標
};

