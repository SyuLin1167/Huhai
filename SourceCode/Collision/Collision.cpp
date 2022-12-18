#include "Collision.h"

// @brief Sphereコンストラクター //

Sphere::Sphere()
    :localCenter()
    ,worldCenter()
    ,Radius(0.0f)
{
}

// @brief Sphereコンストラクター(引数付)

Sphere::Sphere(const VECTOR& center,float radius)
    :localCenter(center)
    ,worldCenter(center)
    ,Radius(radius)
{
}

// @brief Sphere動作処理 //
void Sphere::Move(const VECTOR& pos)
{
    worldCenter = localCenter + pos;
}

// @brief 球体同士の当たり判定 //

bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
{
    return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.Radius,
        sphere2.worldCenter, sphere2.Radius);
}