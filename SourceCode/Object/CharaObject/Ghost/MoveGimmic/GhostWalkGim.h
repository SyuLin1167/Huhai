#pragma once

#include"../Base/GhostBase.h"

/*GhostWalkGimのクラス*/
class GhostWalkGim:public GhostBase
{
public:
    /// <summary>
    /// GhostWalkGimコンストラクター
    /// </summary>
    GhostWalkGim();
	
    /// <summary>
    /// GhostWalkGimコンストラクター
    /// </summary>
    ~GhostWalkGim();

    /// <summary>
    /// GhostWalkGim更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// GhostWalkGim描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// GhostWalkGim衝突時処理
    /// </summary>
    /// <param name="other">:オブジェクト</param>
    void OnCollisionEnter(const ObjectBase* other)override;

private:
    ObjectBase* light;

    bool move;
};

