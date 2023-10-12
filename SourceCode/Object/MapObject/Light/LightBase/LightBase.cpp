#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<fstream>

#include "LightBase.h"

#include"../../../../Scene/PauseScene/PauseMenu/PauseMenu.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
LightBase::LightBase()
    :ObjBase(ObjTag::Light)
    , lightHandle(-1)
    , lightAtten2(0.004f)
    , lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
    //���C�g�ݒ�
    lightHandle = CreatePointLightHandle(objPos, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2);

    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");
    MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">:�V�[����</param>
/// <param name="num">:�I�u�W�F�N�g�ԍ�</param>
LightBase::LightBase(std::string scene,std::string num)
    :ObjBase(ObjTag::Light)
    , lightHandle(-1)
    , lightAtten2(0.008f)
    , lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
    //�t�@�C���ǂݍ���
    std::ifstream ifs("../SourceCode/Object/MapObject/Light/LightBase/LightData.json");
    rapidjson::Document doc;

    //�t�@�C�����
    if (ifs.good())
    {
        rapidjson::IStreamWrapper isw(ifs);

        doc.ParseStream(isw);
    }
    ifs.close();

    //�f�[�^��ǂݎ���č��W�ɑ��
    auto& data = doc[scene.c_str()][num.c_str()];
    objPos.x = data["pos"].GetArray()[0].GetFloat();
    objPos.y = LIGHT_POS_Y;
    objPos.z = data["pos"].GetArray()[1].GetFloat();

    //���C�g�ݒ�
    lightHandle = CreatePointLightHandle(objPos, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2);

    //���f���ݒ�
    objPos.y = LIGHTMODEL_POS_Y;
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");
    MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LightBase::~LightBase()
{
    //���C�g�폜
    DeleteLightHandle(lightHandle);
}

/// <summary>
/// �p�����[�^�ɂ�鋗������
/// </summary>
void LightBase::AttenByParam()
{
    float param = MIN_ATTEN_PARAM - (static_cast<float>(PauseMenu::Parameter("Brightness")) / 10000.0f);
    if (lightAtten2 != param)
    {
        lightAtten2 = param;
        SetLightRangeAttenHandle(lightHandle, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2);
    }
}