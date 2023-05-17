#pragma once

#include"../../../ObjectManager/ObjManager.h"
#include"../../../../Asset/AssetManager/AssetManager.h"
#include"../../../ObjectBase/ObjectBase.h"
#include"../../../../Asset/Animation/Animation.h"
#include"../../../../Collision/Collision.h"

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
        RUN,                                //走り
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

};
