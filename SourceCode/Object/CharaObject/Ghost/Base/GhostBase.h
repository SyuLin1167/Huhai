#pragma once

#include"../../../ObjectBase/ObjectBase.h"
#include"../../../../Asset/Animation/Animation.h"
#include"../../../../Asset/Sound/Sound.h"

/*GhostBaseクラス*/
class GhostBase :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GhostBase();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GhostBase();

    /// <summary>
    /// アニメーションタイプ
    /// </summary>
    enum Anim
    {
        IDLE = 0,                           //待機
        WALK,                               //歩き
        SAD,                                //泣き
        MOVE,                               //動作
    };

protected:
    class Animation* gstAnim;       //アニメーション
    int animType;                   //アニメーションタイプ

    class Sound* gstSound;          //サウンド
};