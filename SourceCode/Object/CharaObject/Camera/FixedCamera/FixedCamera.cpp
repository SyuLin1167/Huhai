#include "FixedCamera.h"

/// <summary>
/// コンストラクタ
/// </summary>
FixedCamera::FixedCamera()
	:ObjBase(ObjTag::Camera)
{
    objPos = FIRST_POS;
    objDir = FIRST_AIM_POS;
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
/// <param name="deltaTime">:デルタタイム</param>
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