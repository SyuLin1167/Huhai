#pragma once

#include"../Base/GhostBase.h"

/*GhostMoveGimのクラス*/
class GhostMoveGim:public GhostBase
{
public:
    /// <summary>
    /// GhostMoveGimコンストラクター
    /// </summary>
    GhostMoveGim();
	
    /// <summary>
    /// GhostMoveGimコンストラクター
    /// </summary>
    ~GhostMoveGim();

    /// <summary>
    /// GhostMoveGim更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// GhostMoveGim描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// GhostMoveGim衝突時処理
    /// </summary>
    /// <param name="other">:オブジェクト</param>
    void OnCollisionEnter(const ObjectBase* other)override;

private:
    ObjectBase* light;

    bool move;
};

