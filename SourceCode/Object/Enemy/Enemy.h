#pragma once
#include<DxLib.h>


#include"../ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../ObjectBase/ObjectBase.h"
#include"../../Asset/Animation/Animation.h"
#include"../../Collision/Collision.h"

class Animation;

/* Enemyのクラス */
class Enemy :public ObjectBase
{
public:
    /// <summary>
    /// Enemyのコンストラクター
    /// </summary>
    Enemy();

    /// <summary>
    /// Enemyのデストラクター
    /// </summary>
    ~Enemy();

    /// <summary>
    /// Enemy更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Enemy描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// 当たり判定球取得
    /// </summary>
    /// <returns>当たり判定球</returns>
    Sphere GetColSphere() { return colSphere; }

    /// <summary>
    /// アニメーションステータス
    /// </summary>
    typedef enum Anim
    {
        IDLE = 0,							//待機
        RUN,								//走り
        ATACK								//攻撃
    };
private:
    /// <summary>
    /// Enemy移動処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Move(float deltaTime);

    //---アニメーション関連---//
    Animation* emyAnim;						//アニメーション
    int animType;							//アニメーション状態

    Sphere colSphere;			//当たり判定球
};

