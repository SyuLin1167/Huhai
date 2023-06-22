#include "Bed.h"

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../UI/Action/Action.h"
#include"../../../Scene/TitleScene/Title.h"

// �R���X�g���N�^ //

Bed::Bed()
    :ObjBase(ObjectTag::Furniture)
{
    Load();
}

// �f�X�g���N�^ //

Bed::~Bed()
{
    //���f���폜
    AssetManager::ReleaseMesh(objHandle);
}

        // �ǂݍ��ݏ��� //

void Bed::Load()
{

    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Map/Bed/Bed.mv1");
    objPos = { 55,0,20 };
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));

    //�����蔻��ݒ�
    colModel = objHandle;

    //�A�N�V�����{�^������
    ObjManager::Entry(new Action(objPos));
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
        VECTOR movePly = VSub(objPos + VGet(5.0f, 0.0f, 0.0f), player->GetPos());
        movePly = VNorm(movePly);
        player->SetPos(VAdd(player->GetPos(), movePly * objSpeed * deltaTime));

        //���_���A�Q���ɂ���
        ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
        camera->SetPos(player->GetPos() + VGet(0, 14, 0));
        camera->SetDir(VGet(0, 25, 20) - camera->GetPos());
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