#pragma once

/// <summary>
/// コリジョン形状タイプ
/// </summary>
enum class CollisionType
{
    Line,               //線分
    Sphere,             //球体
    Capsule,            //カプセル
    Model               //モデル
};