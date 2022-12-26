#include "CameraFps.h"
#include"../Player/Player.h"

// @brief CameraFpsコンストラクター //

CameraFps::CameraFps()
    :ObjectBase(ObjectTag::Camera)
    ,camLookPos{0,0,0}
{
    SetCameraNearFar(CameraNear, CameraFar);                      //カメラの描画範囲設定
    objPos = { -100,58,0 };
}

// @brief CameraFps更新処理 //

void CameraFps::Update(float deltaTime)
{
    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
    if (player)
    {
        camLookPos = player->GetPos();
        SetCameraPositionAndTarget_UpVecY(objPos+camLookPos, camLookPos);
    }
}