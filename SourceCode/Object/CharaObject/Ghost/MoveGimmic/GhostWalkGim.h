#pragma once

#include"../Base/GhostBase.h"

/// <summary>
/// GhostWalkGimクラス
/// </summary>
class GhostWalkGim :public GhostBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GhostWalkGim();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~GhostWalkGim();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// 当たり判定処理
    /// </summary>
    /// <param name="other">:オブジェクト</param>
    void OnCollisionEnter(const ObjBase* other)override;

private:
    const VECTOR COL_LINE_HEIGHT = VGet(0, 5, 0);       //線分高さ
    const VECTOR COL_LINE_FIRST_POS = VGet(7, 0, 0);    //線分始点
};