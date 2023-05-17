#include "CameraFps.h"
#include"../Player/Player.h"

// @brief CameraFps�R���X�g���N�^�[ //

CameraFps::CameraFps()
    :ObjectBase(ObjectTag::Camera)
    ,camLookPos{0,15,0}
    ,mouseX(0)
    ,mouseY(0)
    ,movePos{0,0,0}
    ,cameraYaw(0)
    ,cameraPitch(-1)
{
    SetCameraNearFar(CameraNear, CameraFar);                                 //�J�����̕`��͈͐ݒ�
    SetMouseDispFlag(FALSE);                                                 //�}�E�X�͔�\��

}

// @brief CameraFps�X�V���� //

void CameraFps::Update(float deltaTime)
{
    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);         //�v���C���[�I�u�W�F�N�g�擾
    if (player)                                                              //�I�u�W�F�N�g�̒��g����łȂ����
    {
        //---�J�������W�ݒ�---//
        objPos = player->GetPos();                                           //�J�����̈ʒu�̓v���C���[�̍��W
        objPos.y = 22.5f;                                                       //�����͖ڐ��̈ʒu

        Move(deltaTime);
        SetCameraPositionAndTarget_UpVecY(objPos, objPos + camLookPos);      //�v���C���[�̈ʒu���璍���_�Ɍ����ăJ�������Z�b�g
        objDir = camLookPos;                                                 //�J�����̐��ʕ����x�N�g��
    }
    SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);                        //�}�E�X���W����ʂ̒��S�ɃZ�b�g
}

// @brief CameraFps�ړ����� //

void CameraFps::Move(float deltaTime)
{
        //---�}�E�X���W����X�N���[�����W�̒��S������---//
        GetMousePoint(&mouseX, &mouseY);                                     //�}�E�X���W�擾
        movePos.x = (float)mouseX - static_cast<float>(SCREEN_WIDTH) / 2;
        movePos.y = (float)mouseY - static_cast<float>(SCREEN_HEIGHT) / 2;

        //---���_�ړ�--//
        if (abs(movePos.x) > 0)                                              //�}�E�X�J�[�\��X�����X���C�h��
        {
            cameraYaw -= movePos.x *deltaTime* DX_PI_F/30;                   //�J�[�\���̈ړ��ʕ����������ɉ�]
        }
        if (abs(movePos.y) > 0)                                              //�}�E�X�J�[�\��Y�����X���C�h��
        {
            cameraPitch -= movePos.y * deltaTime * DX_PI_F/30;               //�J�[�\���̈ړ��ʕ����������ɉ�]
        }

        //---�����_����---//
        camLookPos.x = cosf(cameraYaw);
        camLookPos.y = cameraPitch;
        camLookPos.z = sinf(cameraYaw);
}