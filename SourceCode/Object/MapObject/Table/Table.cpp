#include "Table.h"

#include"../../../Asset/AssetManager/AssetManager.h"

        // �R���X�g���N�^ //

Table::Table(int objNum)
    :ObjBase(ObjectTag::Furniture)
{
    objPos = posData[objNum];
    objDir.y = dirData[objNum];

    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Map/Table/Table.mv1");
    MV1SetScale(objHandle, objScale);
    MV1SetPosition(objHandle, objPos);
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));

    //�����蔻��ݒ�
    colModel = AssetManager::GetMesh("../Assets/Map/Table/ColTable.mv1");
    MV1SetPosition(colModel, objPos);
    MV1SetScale(colModel, VGet(0.1f, 0.1f, 0.1f));
    MV1SetRotationXYZ(colModel, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //���f���̌����ݒ�
}

// �f�X�g���N�^ //

Table::~Table()
{

}

// �X�V���� //

void Table::Update(float delataTime)
{
    //�����蔻��X�V
    ColUpdate();
}

// �`�揈�� //

void Table::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}