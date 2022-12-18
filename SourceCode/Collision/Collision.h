#pragma once
#include<DxLib.h>
#include"../Math/Math.h"

/*球体の構造体*/
struct Sphere
{
    /// <summary>
    /// Sphereコンストラクター
    /// </summary>
    Sphere();

    /// <summary>
    /// Sphereコンストラクター(引数付)
    /// </summary>
    /// <param name="center">中心座標</param>
    /// <param name="radius">半径</param>
    Sphere(const VECTOR& center, float radius);

    /// <summary>
    /// Sphere動作処理
    /// </summary>
    /// <param name="pos">球体のワールド座標</param>
    void Move(const VECTOR& pos);

    VECTOR localCenter;     //球体のローカル中心座標
    VECTOR worldCenter;     //球体のワールド中心座標
    float Radius;          //球体の半径
};

/// <summary>
/// 球体同士の当たり判定
/// </summary>
/// <param name="sphere1">球体1</param>
/// <param name="sphere2">球体2</param>
/// <returns>ぶつかっているかどうか</returns>
bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2);

