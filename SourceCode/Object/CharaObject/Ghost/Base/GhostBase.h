#pragma once
#include<memory>

#include"../../../ObjectBase/ObjBase.h"
#include"../../../../Asset/Animation/Animation.h"
#include"../../../../Asset/Sound/Sound.h"

/// <summary>
/// 幽霊の基底クラス
/// </summary>
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
    bool isMove;                                    //移動状態

    std::unique_ptr<class Animation> ghostAnim;     //アニメーション
    int animType;                                   //アニメーションタイプ

    std::unique_ptr<class Sound> ghostSound;        //サウンド
};