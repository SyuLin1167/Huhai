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
    ,cameraPitch(0)
{
    SetCameraNearFar(CameraNear, CameraFar);                                            //�J�����̕`��͈͐ݒ�
}

// @brief CameraFps�X�V���� //

void CameraFps::Update(float deltaTime)
{
    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);                    //�v���C���[�I�u�W�F�N�g�擾
    if (player)                                                                         //�I�u�W�F�N�g�̒��g����łȂ����
    {
        //---�J�������W�ݒ�---//
        objPos = player->GetPos();                                                      //�J�����̈ʒu�̓v���C���[�̍��W
        objPos.y = 15;                                                                  //�����͖ڐ��̈ʒu

        Move(deltaTime);
        SetCameraPositionAndTarget_UpVecY(objPos, objPos + camLookPos);      //�v���C���[�̈ʒu���璍���_�Ɍ����ăJ�������Z�b�g
        objDir = camLookPos;                                                   //�J�����̐��ʕ����x�N�g��
    }
    SetMousePoint(ScreenWidth / 2, ScreenHeight / 2);                        //�}�E�X���W����ʂ̒��S�ɃZ�b�g
}

// @brief CameraFps�ړ����� //

void CameraFps::Move(float deltaTime)
{
        GetMousePoint(&mouseX, &mouseY);                                        //�}�E�X���W�擾

        //---�}�E�X���W����X�N���[�����W�̒��S������---//
        movePos.x = mouseX - ScreenWidth / 2;
        movePos.y = mouseY - ScreenHeight / 2;

        //---���_�ړ�--//
        if (abs(movePos.x) > 0)                                                      //�}�E�X�J�[�\��X�����X���C�h��
        {
            cameraYaw -= movePos.x *deltaTime* (float)DX_PI/30;                         //�J�[�\���̈ړ��ʕ����������ɉ�]
        }
        if (abs(movePos.y) > 0)                                                     //�}�E�X�J�[�\��Y�����X���C�h��
        {
            cameraPitch -= movePos.y * deltaTime * (float)DX_PI/30;                     //�J�[�\���̈ړ��̕����������ɉ�]
        }

        //---�����_����---//
        camLookPos.x = cosf(cameraYaw);
        camLookPos.y = cameraPitch;
        camLookPos.z = sinf(cameraYaw);
}
