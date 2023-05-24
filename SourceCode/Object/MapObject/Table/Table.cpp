#include "Table.h"

// @brief Table�R���X�g���N�^ //

Table::Table(int objNum)
    :ObjectBase(ObjectTag::Furniture)
{
    objPos = posData[objNum];
    objDir.y = dirData[objNum];
    objHandle = AssetManager::GetMesh("../Assets/Map/Table/Table.mv1");
    MV1SetScale(objHandle, objScale);                                                       //���f���̃T�C�Y�ݒ�
    MV1SetPosition(objHandle, objPos);                                                      //���f���̍��W�ݒ�
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / 180.0f * DX_PI_F, 0.0f));            //���f���̌����ݒ�
    
    colModel = AssetManager::GetMesh("../Assets/Map/Table/ColTable.mv1");
    // �\�����f���Ɠ����蔻�胂�f���̈ʒu�������
    MV1SetPosition(colModel, objPos);

    MV1SetupCollInfo(colModel);
}

// @brief Table�f�X�g���N�^ //

Table::~Table()
{
}

// @brief Table�X�V���� //

void Table::Update(float delataTime)
{
}

// @brief Table�`�揈�� //

void Table::Draw()
{
    MV1DrawModel(objHandle);                    //���f���`��
}