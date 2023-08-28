#include "LightBase.h"

#include"../../../../Scene/PauseMenu/PauseMenu.h"

// �R���X�g���N�^ //

LightBase::LightBase()
    :ObjBase(ObjectTag::Light)
    , lightHandle(-1)
    , lightRange(70.0f)
    , lightAtten2(0.004f)
    , lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
    Load();
}

// �R���X�g���N�^ //

LightBase::LightBase(VECTOR pos)
    :ObjBase(ObjectTag::Light, pos)
    , lightHandle(-1)
    , lightRange(70.0f)
    , lightAtten2(0.004f)
    , lightMatColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f))
{
    Load();
}

// �f�X�g���N�^ //

LightBase::~LightBase()
{
    //���C�g�폜
    DeleteLightHandle(lightHandle);
}

// �ǂݍ��ݏ��� //

void LightBase::Load()
{
    //���C�g�ݒ�
    lightHandle = CreatePointLightHandle(objPos + VGet(0.0f, 2.5f, 0.0f) , lightRange, 0.0f, 0.0f, lightAtten2 * 2.0f);

    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
}

// �p�����[�^�ɂ�鋗������ //

void LightBase::AttenByParam()
{
    float param = 0.01f - (static_cast<float>(PauseMenu::Parameter("Brightness")) / 10000.0f);
    if (lightAtten2 != param)
    {
        lightAtten2 = param;
        SetLightRangeAttenHandle(lightHandle, lightRange, 0.0f, 0.0f, lightAtten2);
    }
}