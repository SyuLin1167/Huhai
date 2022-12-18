#pragma once
#include<DxLib.h>


#include"../ObjectBase/ObjectBase.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Collision/Collision.h"

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
    void Update(float deltaTime);

    /// <summary>
    /// Enemy描画処理
    /// </summary>
    void Draw();

    /// <summary>
    /// 当たり判定球取得
    /// </summary>
    /// <returns>当たり判定球</returns>
    Sphere GetColSphere() { return colSphere; }

private:

    Sphere colSphere;			//当たり判定球
};

