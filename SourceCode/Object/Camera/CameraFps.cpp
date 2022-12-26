#include "CameraFps.h"
#include"../Player/Player.h"

// @brief CameraFps�R���X�g���N�^�[ //

CameraFps::CameraFps()
    :ObjectBase(ObjectTag::Camera)
    ,camLookPos{0,0,0}
{
    SetCameraNearFar(CameraNear, CameraFar);                      //�J�����̕`��͈͐ݒ�
    objPos = { -100,58,0 };
}

// @brief CameraFps�X�V���� //

void CameraFps::Update(float deltaTime)
{
    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
    if (player)
    {
        camLookPos = player->GetPos();
        SetCameraPositionAndTarget_UpVecY(objPos+camLookPos, camLookPos);
    }
}