#pragma once

#include"Base/GhostBase.h"

/* Ghostのクラス */
class Ghost :public GhostBase
{
public:
    /// <summary>
    /// Ghostのコンストラクター
    /// </summary>
    Ghost();

    /// <summary>
    /// Ghostのデストラクター
    /// </summary>
    ~Ghost();

    /// <summary>
    /// Ghost更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Ghost描画処理
    /// </summary>
    void Draw()override;


    /// <summary>
    /// Ghost衝突時処理
    /// </summary>
    /// <param name="other">:オブジェクト</param>
    void OnCollisionEnter(const ObjectBase* other)override;

};

