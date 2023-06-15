#include "Furniture.h"

        // �R���X�g���N�^ //

Furniture::Furniture(int furtag)
    :ObjectBase(ObjectTag::Furniture)
    , furModel(nullptr)
    , furColModel(nullptr)
{
    LoadModel(furtag);
}

        // �f�X�g���N�^ //

Furniture::~Furniture()
{
    AssetManager::ReleaseMesh(objHandle);					//���b�V���̍폜
}

        // ���f���ǂݍ��ݏ��� //

void Furniture::LoadModel(int furtag)
{
    //---�}�b�v���f���ǂݍ���---//
    furModel = new Model;
    furModel->AddModel("../Assets/Map/Furniture/RoomFur.mv1");
    furModel->AddModel("../Assets/Map/Furniture/StageFur.mv1");
    objHandle = furModel->SetModel(furtag);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));

    // �����蔻�胂�f���ǂݍ��݁��X�P�[�����O�������蔻����\�z
    furColModel = new Model;
    furColModel->AddModel("../Assets/Map/Furniture/RoomFurCol.mv1");
    furColModel->AddModel("../Assets/Map/Furniture/StageFurCol.mv1");
    colModel = furColModel->SetModel(furtag);
    MV1SetScale(colModel, VGet(0.11f, 0.12f, 0.11f));

    // �\�����f���Ɠ����蔻�胂�f���̈ʒu�������
    MV1SetPosition(colModel, objPos);
}

        // �X�V���� //

void Furniture::Update(float deltaTime)
{
    ColUpdate();
}

        // �`�揈�� //

void Furniture::Draw()
{
    MV1DrawModel(objHandle);
}