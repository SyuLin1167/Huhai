#include "FixedCamera.h"

/// <summary>
/// コンストラクタ
/// </summary>
FixedCamera::FixedCamera()
	:ObjBase(ObjTag::Camera)
{
    objPos = VGet(70, 6, 75);
    objDir = VGet(-10, 10, 25);
}

/// <summary>
/// デストラクタ
/// </summary>
FixedCamera::~FixedCamera()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void FixedCamera::Update(const float deltaTime)
{
    //処理なし
}

/// <summary>
/// 描画処理
/// </summary>
void FixedCamera::Draw()
{
    //注視点に向けてカメラをセット
    SetCameraPositionAndTarget_UpVecY(objPos, objDir);
}