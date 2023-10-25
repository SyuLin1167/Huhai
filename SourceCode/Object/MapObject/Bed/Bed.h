#pragma once

#include"../../ObjectBase/ObjBase.h"

/// <summary>
/// ベッドオブジェクト
/// </summary>
class Bed :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Bed();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Bed();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:デルタタイム</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;

private:
    VECTOR sleepPos;                                //睡眠時座標
    const VECTOR SLEEP_AIM_POS=VGet(0, 8, 0);       //睡眠時目線座標
};
