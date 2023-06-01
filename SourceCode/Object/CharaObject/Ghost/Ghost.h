#pragma once

#include"Base/GhostBase.h"
#include"../../../Collision/Collision.h"

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

    /// <summary>
    /// Ghost回転処理
    /// </summary>
    void Rotate();

private:
    bool firstMove;
    bool nowMove;
    float moveCount;
    bool rotateNow;
    VECTOR aimDir;

    VECTOR aimPos;
    VECTOR holdPos;

    int lightHandle;
};

