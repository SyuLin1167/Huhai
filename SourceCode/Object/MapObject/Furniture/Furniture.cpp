#include "Furniture.h"

#include"../../../Asset/AssetManager/AssetManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag">:�^�O</param>
Furniture::Furniture(FurName tag)
    :ObjBase(ObjTag::Furniture)
{
    Load(tag);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Furniture::~Furniture()
{
    //�����Ȃ�
}

/// <summary>
/// �ǂݍ��ݏ���
/// </summary>
/// <param name="tag">:�^�O</param>
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

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
void Furniture::Update(float deltaTime)
{
    //�����蔻��X�V
    ColUpdate();
}

/// <summary>
/// �`�揈��
/// </summary>
void Furniture::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}