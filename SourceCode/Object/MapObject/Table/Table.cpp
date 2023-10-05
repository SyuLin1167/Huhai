#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<fstream>

#include "Table.h"

#include"../../../Asset/AssetManager/AssetManager.h"

// �R���X�g���N�^ //

Table::Table(const int objNum)
    :ObjBase(ObjectTag::Furniture)
{
    //�t�@�C���ǂݍ���
    LoadJsonFile("TableData.json");

    //�f�[�^��ǂݎ���č��W�E�����ɑ��
    const std::string key = std::to_string(objNum);
    auto& data = doc["data"][key.c_str()];

    objPos.x = data["pos"].GetArray()[0].GetFloat();
    objPos.y = data["pos"].GetArray()[1].GetFloat();
    objPos.z = data["pos"].GetArray()[2].GetFloat();
    objDir.y = data["dir"].GetFloat();

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