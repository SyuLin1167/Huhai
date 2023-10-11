#include "Furniture.h"

#include"../../../Asset/AssetManager/AssetManager.h"

// �R���X�g���N�^ //

Furniture::Furniture(FurName tag)
    :ObjBase(ObjTag::Furniture)
{
    Load(tag);
}

// �f�X�g���N�^ //

Furniture::~Furniture()
{
}

// �ǂݍ��ݏ��� //

void Furniture::Load(FurName tag)
{
    //���f���ݒ�

    objHandle = AssetManager::GetMesh(furModel[tag]);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));

    // �����蔻��ݒ�
    colModel = AssetManager::GetMesh(furColModel[tag]);
    MV1SetScale(colModel, VGet(0.11f, 0.12f, 0.11f));
    MV1SetPosition(colModel, objPos);
}

// �X�V���� //

void Furniture::Update(float deltaTime)
{
    //�����蔻��X�V
    ColUpdate();
}

// �`�揈�� //

void Furniture::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}