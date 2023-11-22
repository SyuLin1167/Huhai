#include "FpsCamera.h"

#include"../../../ObjectManager/ObjManager.h"
#include"../../Player/Player.h"
#include"../../../../Scene/PauseScene/PauseMenu/PauseMenu.h"

FpsCamera::FpsCamera()
    :ObjBase(ObjTag::Camera)
    , mouseX(0)
    , mouseY(0)
    , movePos(VGet(0,0,0))
    , cameraYaw(0)
    , cameraPitch(-1)
{
    objDir = VGet(5, 0, 0);
    SetCameraNearFar(CameraNear, CameraFar);                                    //�J�����̕`��͈͐ݒ�
    SetMousePoint(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT);
    SetMouseDispFlag(false);                                                    //�}�E�X�͔�\��
}

FpsCamera::~FpsCamera()
{
    //�����Ȃ�
}

void FpsCamera::Update(const float deltaTime)
{
    //�J�����̓v���C���[�̖ڐ��ɂ���
    ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
    if (player)
    {
        objPos = player->GetPos();
        objPos.y = CameraPosY;

        Move(deltaTime);

        //�}�E�X�|�C���^�[�͉�ʂ̒��S
        SetMousePoint(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT);
    }
    else
    {
        isAlive = false;
    }
}

void FpsCamera::Move(float deltaTime)
{
    //�}�E�X�ړ��ʌv��
    GetMousePoint(&mouseX, &mouseY);
    if (mouseX > MIN_MOVE_PARAM && mouseX < SCREEN_WIDTH - MIN_MOVE_PARAM &&
        mouseY > MIN_MOVE_PARAM && mouseY < SCREEN_HEIGHT - MIN_MOVE_PARAM)
    {
        movePos.x = static_cast<float>(mouseX - SCREEN_CENTER_WIDTH);
        movePos.y = static_cast<float>(mouseY - SCREEN_CENTER_HEIGHT);
    }


    //�J�[�\���̈ړ��ʎ擾
    ButtonName buttonName;
    if (abs(movePos.x) > 0)
    {
        cameraYaw -= movePos.x * deltaTime * DX_PI_F /
            (CONTROL_SENSI - PauseMenu::Parameter(buttonName.sensi));
    }
    if (abs(movePos.y) > 0)
    {
        cameraPitch -= movePos.y * deltaTime * DX_PI_F /
            (CONTROL_SENSI - PauseMenu::Parameter(buttonName.sensi));
    }

    //�J�����̕����ݒ�
    objDir.x = cosf(cameraYaw);
    objDir.y = cameraPitch;
    objDir.z = sinf(cameraYaw);
}

void FpsCamera::Draw()
{
    //�J�[�\���̈ړ����������Ɏ��_���ړ�
    SetCameraPositionAndTarget_UpVecY(objPos, objPos + objDir);
}