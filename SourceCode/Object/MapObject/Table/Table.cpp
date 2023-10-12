#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<fstream>

#include "Table.h"
#include"../../../Asset/AssetManager/AssetManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="objNum">:�I�u�W�F�N�g�ԍ�</param>
Table::Table(const int objNum)
    :ObjBase(ObjTag::Furniture)
{
    //�t�@�C���ǂݍ���
    std::ifstream ifs("../SourceCode/Object/MapObject/Table/TableData.json");
    rapidjson::Document doc;

    //�t�@�C�����
    if (ifs.good())
    {
        rapidjson::IStreamWrapper isw(ifs);

        doc.ParseStream(isw);
    }
    ifs.close();

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
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / ONE_HALF_PI * DX_PI_F, 0.0f));

    //�����蔻��ݒ�
    colModel = AssetManager::GetMesh("../Assets/Map/Table/ColTable.mv1");
    MV1SetPosition(colModel, objPos);
    MV1SetScale(colModel, VGet(0.1f, 0.1f, 0.1f));
    MV1SetRotationXYZ(colModel, VGet(0.0f, objDir.y / ONE_HALF_PI * DX_PI_F, 0.0f));            //���f���̌����ݒ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Table::~Table()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
void Table::Update(float delataTime)
{
    //�����蔻��X�V
    ColUpdate();
}

/// <summary>
/// �`�揈��
/// </summary>
void Table::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}