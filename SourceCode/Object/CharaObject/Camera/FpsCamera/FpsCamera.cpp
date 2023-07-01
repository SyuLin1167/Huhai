#include "FpsCamera.h"

#include"../../../ObjectManager/ObjManager.h"
#include"../../Player/Player.h"

// �R���X�g���N�^ //

FpsCamera::FpsCamera()
    :ObjBase(ObjectTag::Camera)
    , mouseX(0)
    , mouseY(0)
    , movePos{ 0,0,0 }
    , cameraYaw(0)
    , cameraPitch(-1)
{
    objDir = { 0,10,0 };
    SetCameraNearFar(CameraNear, CameraFar);                                    //�J�����̕`��͈͐ݒ�
    SetMouseDispFlag(FALSE);                                                    //�}�E�X�͔�\��
}

// �f�X�g���N�^ //

FpsCamera::~FpsCamera()
{
}

// �X�V���� //

void FpsCamera::Update(float deltaTime)
{
    //�J�����̓v���C���[�̖ڐ��ɂ���
    ObjBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
    if (player)
    {
        objPos = player->GetPos();
        objPos.y = CameraPosY;

        Move(deltaTime);
        SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    else
    {
        isAlive = false;
    }
}

// �ړ����� //

void FpsCamera::Move(float deltaTime)
{
    //�펞�}�E�X�|�C���^�[�͉�ʂ̒��S
    GetMousePoint(&mouseX, &mouseY);
    movePos.x = (float)mouseX - static_cast<float>(SCREEN_WIDTH) / 2;
    movePos.y = (float)mouseY - static_cast<float>(SCREEN_HEIGHT) / 2;

    //�J�[�\���̈ړ��ʎ擾
    if (abs(movePos.x) > 0)
    {
        cameraYaw -= movePos.x * deltaTime * DX_PI_F / 30;
    }
    if (abs(movePos.y) > 0)
    {
        cameraPitch -= movePos.y * deltaTime * DX_PI_F / 30;
    }

    //�J�����̕����ݒ�
    objDir.x = cosf(cameraYaw);
    objDir.y = cameraPitch;
    objDir.z = sinf(cameraYaw);
}

void FpsCamera::Draw()
{
    if (isVisible)
    {
        //�J�[�\���̈ړ����������Ɏ��_���ړ�
        SetCameraPositionAndTarget_UpVecY(objPos, objPos + objDir);
    }
}