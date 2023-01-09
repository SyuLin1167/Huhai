#include "CameraFps.h"
#include"../Player/Player.h"

// @brief CameraFps�R���X�g���N�^�[ //

CameraFps::CameraFps()
    :ObjectBase(ObjectTag::Camera)
    ,camLookPos{0,0,0}
{
    SetCameraNearFar(CameraNear, CameraFar);                      //�J�����̕`��͈͐ݒ�
    objPos = { 0,10,0 };
}

// @brief CameraFps�X�V���� //

void CameraFps::Update(float deltaTime)
{
    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
    if (player)
    {
        GetMousePoint(&mouseX, &mouseY);
        mouseX = mouseX - 1920 / 2;
        mousePos.x = mouseX;
        mouseY = 1920 / 2 - mouseY;
        mousePos.y = mouseY;
        camLookPos = player->GetPos();
        SetCameraPositionAndTarget_UpVecY(objPos+camLookPos, mousePos);
    }
}