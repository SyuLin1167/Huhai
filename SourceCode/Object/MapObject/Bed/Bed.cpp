#include "Bed.h"

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../CharaObject/Camera/FixedCamera/FixedCamera.h"
#include"../../../UI/Action/Action.h"

// �R���X�g���N�^ //

Bed::Bed()
    :ObjBase(ObjectTag::Furniture)
{
    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Map/Bed/Bed.mv1");
    objPos = { 55,0,20 };
    sleepPos = objPos + VGet(5, 0, 0);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / ONE_HALF_PI * DX_PI_F, 0.0f));

    //�����蔻��ݒ�
    colModel = objHandle;

    //�A�N�V�����{�^������
    ObjManager::Entry(new Action(objPos));
}

// �f�X�g���N�^ //

Bed::~Bed()
{
    //�����Ȃ�
}

        // �X�V���� //

void Bed::Update(float deltaTime)
{
    //�A�N�V�����{�^���������ꂽ��A�Q����
    ObjBase* action = ObjManager::GetFirstObj(ObjectTag::UI);
    if (!action->IsVisible())
    {


        //�v���C���[���x�b�h�Ɉړ�
        colModel = -1;
        ObjBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
        VECTOR movePlyVec = sleepPos - player->GetPos();
        if (abs(VSize(movePlyVec)) >= 0)
        {
            movePlyVec = VNorm(movePlyVec);
            player->SetPos(player->GetPos() + (movePlyVec * objSpeed * deltaTime));
        }

        //���_���A�Q���ɂ���
        VECTOR aimDir = player->GetDir();
        if (aimDir.x > -1)
        {
            aimDir.x -= objSpeed * deltaTime;
        }
        ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
        camera->SetPos(camera->GetPos() - SLEEP_AIM_POS);
        camera->SetDir(aimDir);
    }
    else
    {
        //�����蔻��X�V
        ColUpdate();
    }
}

// �`�揈�� //

void Bed::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}
