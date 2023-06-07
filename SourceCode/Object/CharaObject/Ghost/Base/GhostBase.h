#pragma once

#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Asset/AssetManager/AssetManager.h"
#include"../../../ObjectBase/ObjectBase.h"
#include"../../../../Asset/Animation/Animation.h"
#include"../../../../Collision/Collision.h"
#include"../../../../Asset/Sound/Sound.h"

/*Ghostの基底クラス*/
class GhostBase:public ObjectBase
{
public:
    /// <summary>
    /// GhostBaseコンストラクタ
    /// </summary>
    GhostBase();

    /// <summary>
    /// GhostBaseデストラクタ
    /// </summary>
    ~GhostBase();

    /// <summary>
    /// アニメーションステータス
    /// </summary>
    enum Anim
    {
        IDLE = 0,                           //待機
        WALK,                                //走り
        SAD,
        MOVE,
    };

    /// <summary>
    /// 当たり判定球取得
    /// </summary>
    /// <returns>当たり判定球</returns>
    Sphere GetColSphere() { return colSphere; }

protected:
    //---アニメーション関連---//
    class Animation* gstAnim;                     //アニメーション
    int animType;                           //アニメーション状態

    class Sound* gstSound;
};
