#include "LightBase.h"

// �R���X�g���N�^ //

LightBase::LightBase()
    :ObjBase(ObjectTag::Light)
    , lightHandle(-1)
    , lightRange(70.0f)
    , lightAtten2(0.002f)
    , lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
    Load();
}

// �R���X�g���N�^ //

LightBase::LightBase(VECTOR pos)
    :ObjBase(ObjectTag::Light, pos)
    , lightHandle(-1)
    , lightRange(70.0f)
    , lightAtten2(0.002f)
    , lightMatColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f))
{
    Load();
}

// �f�X�g���N�^ //

LightBase::~LightBase()
{
    //���C�g�폜
    DeleteLightHandle(lightHandle);

    //���f���폜
    AssetManager::ReleaseMesh(objHandle);
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