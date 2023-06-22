#include "Furniture.h"

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Model/Model.h"

// �R���X�g���N�^ //

Furniture::Furniture(int tag)
    :ObjBase(ObjectTag::Furniture)
    , furModel(nullptr)
    , furColModel(nullptr)
{
    Load(tag);
}

// �f�X�g���N�^ //

Furniture::~Furniture()
{
    //���f���폜
    AssetManager::ReleaseMesh(objHandle);
}

// �ǂݍ��ݏ��� //

void Furniture::Load(int tag)
{
    //���f���ݒ�
    furModel = new Model;
    furModel->AddModel("../Assets/Map/Furniture/RoomFur.mv1");
    furModel->AddModel("../Assets/Map/Furniture/StageFur.mv1");
    objHandle = furModel->GetModel(tag);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));

    // �����蔻��ݒ�
    furColModel = new Model;
    furColModel->AddModel("../Assets/Map/Furniture/RoomFurCol.mv1");
    furColModel->AddModel("../Assets/Map/Furniture/StageFurCol.mv1");
    colModel = furColModel->GetModel(tag);
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