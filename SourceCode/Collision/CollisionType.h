#pragma once

/*コリジョン形状クラス*/
enum class CollisionType
{
	Line,				//線分
	Sphere,				//球体
	Capsule,			//カプセル
	Model				//モデル
};