#include "Bed.h"
#include"../../../UI/Action/Action.h"

// @brief Bed�R���X�g���N�^ //

Bed::Bed()
    :ObjectBase(ObjectTag::Furniture)
{
    Load();
}

// @brief Bed�f�X�g���N�^ //

Bed::~Bed()
{
    AssetManager::ReleaseMesh(objHandle);                                               //���f�����b�V���̍폜
}

// @brief Bed�ǂݍ��ݏ��� //

void Bed::Load()
{
    objPos = { 55,0,20 };                                                               //�������W�ݒ�

    //---���f���ǂݍ���---//
    objHandle = AssetManager::GetMesh("../Assets/Map/Bed/Bed.mv1");                     //���f���ǂݍ���

    MV1SetPosition(objHandle, objPos);                                                  //���f���̍��W�ݒ�
    MV1SetScale(objHandle, objScale);                                                   //���f���̃T�C�Y�ݒ�
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));        //���f���̌����ݒ�

    ObjManager::Entry(new Action(objPos));
}

// @brief Bed�X�V���� //

void Bed::Update(float deltaTime)
{
    ObjectBase* action = ObjManager::GetFirstObj(ObjectTag::UI);
    if (!action->IsVisible())
    {
        colModel = -1;
        ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
        VECTOR movePly = VSub(objPos + VGet(5.0f, 0.0f, 0.0f), player->GetPos());
        movePly = VNorm(movePly);
        player->SetPos(VAdd(player->GetPos(), movePly));

        ObjectBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
        SetCameraPositionAndTarget_UpVecY(camera->GetPos() - VGet(0, 8, 0), VGet(0, 25, 20));
    }
    else
    {
        colModel = objHandle;                                                               //�����蔻��̃��f���̓I�u�W�F�N�g�̃��f��
        ColUpdate();                                                                        //�����蔻��X�V
    }
}

// @brief Bed�`�揈�� //

void Bed::Draw()
{
    MV1DrawModel(objHandle);                                                            //���f���`��
}