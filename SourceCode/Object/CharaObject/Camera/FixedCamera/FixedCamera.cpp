#include "FixedCamera.h"

// コンストラクタ //

FixedCamera::FixedCamera()
	:ObjBase(ObjectTag::Camera)
{
    objPos = VGet(70, 6, 75);
    objDir = VGet(-10, 10, 25);
}


// 描画処理 //

void FixedCamera::Draw()
{
    //注視点に向けてカメラをセット
    SetCameraPositionAndTarget_UpVecY(objPos, objDir);
}