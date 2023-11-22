#include "FixedCamera.h"

FixedCamera::FixedCamera()
	:ObjBase(ObjTag::Camera)
{
    objPos = FIRST_POS;
    objDir = FIRST_AIM_POS;
}

FixedCamera::~FixedCamera()
{
    //処理なし
}

void FixedCamera::Update(const float deltaTime)
{
    //処理なし
}

void FixedCamera::Draw()
{
    //注視点に向けてカメラをセット
    SetCameraPositionAndTarget_UpVecY(objPos, objDir);
}