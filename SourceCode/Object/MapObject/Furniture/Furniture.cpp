#include "Furniture.h"

#include"../../../Asset/AssetManager/AssetManager.h"

Furniture::Furniture(FurName tag)
    :ObjBase(ObjTag::Furniture)
{
    Load(tag);
}

Furniture::~Furniture()
{
    //�����Ȃ�
}

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

void Furniture::Update(const float deltaTime)
{
    //�����蔻��X�V
    ColUpdate();
}

void Furniture::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}